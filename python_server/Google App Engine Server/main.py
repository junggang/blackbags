# -*- coding: utf-8 -*-
"""`main` is the top level module for your Flask application."""

import json
import threading
import time
import sys
import random

# import game data structure src
import dataStructure

# Import the Flask Framework
from flask import Flask, redirect, request

# import the google app engine api
from google.appengine.api import users, memcache


app = Flask(__name__)
# Note: We don't need to call run() since our application is embedded within
# the App Engine WSGI application server.


reload(sys)
sys.setdefaultencoding('utf-8')

global waitingList

waitingList = []
gameDataTTL = 60
playerDataTTL = 10
playerTableTTL = 600
waitingChannelTTL = 60

#################################################
#				matching thread 관련				#
#################################################
# 대기 리스트를 하나 만든다 (공유자원 - 동기화 기능을 지원하는 자료구조이어야 함)
# 리스트는 redis안에 저장된 player data에 접근하는 key value를 가지고 있다
# 리스트의 값들은 추가된 순서를 유지한다

def createChannel(playerPool, playerNumber, playerData, tokenId):
	if playerData.getPlayerNumber(playerNumber) == 1:
		playerPool.append(tokenId)

		if len(playerPool) == playerNumber:
			channelId = getNewChannelId()

			gameData = dataStructure.GameData()
			gameData.initData(channelId, time.time() )

			# 플레이어 추가 
			for player in playerPool:
				print 'player number ' + str(playerNumber) + ' : ' + player
				playerData = getPlayerDataNoTTLReset(player)
				gameData.addPlayer(playerData)
				waitingList.remove(player)

				# print playerData.data[3]

				# player data 저장
				memcache.set(player, json.dumps(playerData.data), playerDataTTL)

			if playerNumber == 2:
				gameData.setMapSize(1) # MS_5X5
			elif playerNumber == 3:
				gameData.setMapSize(2) # MS_6X6
			else:
				gameData.setMapSize(3) # MS_7X7

			# 생성한 게임 데이터 redis에 저장 
			jsonData = json.dumps(gameData.data)
			if memcache.get(channelId) == None:
				memcache.add(channelId, jsonData, gameDataTTL)
			else:
				memcache.set(channelId, jsonData, gameDataTTL)

			# 게임 데이터에서 플레이어 데이터에 접근할 수 있게 테이블 생성
			tableName = channelId + ' table'
			jsonData = json.dumps(playerPool)

			if memcache.get(tableName) == None:
				memcache.add(tableName, jsonData, playerTableTTL)
			else:
				memcache.set(tableName, jsonData, playerTableTTL)

			return True

	return False


def playerMatching():
	# 누군가 로그인하면 불려진다
	# 리스트에 있는 사람들이 바뀔 때마다 현재 리스트에 있는 사람들을 가지고 게임 채널 생성하고 채널 테이블을 레디스에 생성

	# 	각 참여 인원에 대한 가상의 풀을 만든다
	# 	대기 시간이 긴 플레이어부터 선택한 참여 인원의 풀에 추가
	#	추가와 함께 해당하는 참여인원이 모두 모이면 추가된 플레이어들로 채널 생성
	#	앞에서 생성된 채널에 추가된 플레이어는 리스트에서 삭제
	waitingListData = memcache.get("waiting_list")
	
	if waitingListData == None:
		return

	waitingList = json.loads(waitingListData)

	player_2 = []
	player_3 = []
	player_4 = []

	for each in waitingList:
		playerData = getPlayerDataNoTTLReset(each)

		if playerData == None:
			# 로그인 되어있지 않음 
			waitingList.remove(each)
			continue

		if createChannel(player_2, 2, playerData, each):
			break

		if createChannel(player_3, 3, playerData, each):
			break

		if createChannel(player_4, 4, playerData, each):
			break

	# 변경된 데이터 저장
	memcache.set("waiting_list", json.dumps(waitingList))


def getNewChannelId():
	newChannelId = ''

	while True:
		newChannelId = str( random.randint(1, 4294967295) )
		
		if memcache.get(newChannelId) == None:
			return newChannelId



#################################################
#				gameLogic 관련					#
#################################################

# game logic은 게임의 인풋이 도착하면 redis에 있는 데이터를 가져와서 업데이트 시키고 다시 저장한다
# 모든 인풋은 유효성 검사가 필수
def getPlayerData(tokenId):
	playerData = dataStructure.PlayerData()
	tempData = memcache.get(tokenId)

	if tempData is not None:
		playerData.insertData(json.loads(tempData))

		jsonData = json.dumps(playerData.data)
		memcache.set(tokenId, jsonData, playerDataTTL)

		return playerData

	return None


def getPlayerDataNoTTLReset(tokenId):
	playerData = dataStructure.PlayerData()
	tempData = memcache.get(tokenId)

	if tempData is not None:
		playerData.insertData(json.loads(tempData))

		return playerData

	return None


def getGameData(channelId):
	gameData = dataStructure.GameData()
	tempData = memcache.get(channelId)

	if tempData is not None:
		gameData.insertData(json.loads(tempData))

		return gameData

	return None


def checkPlayerConnection(channelId, gameData):
	tableName = channelId + ' table'
	jsonData = memcache.get(tableName)

	if jsonData is not None: 
		playerTable = json.loads(jsonData)

	idx = 0
	for each in playerTable:
		if memcache.get(each) == None:
			if not gameData.removePlayer(idx):
				memcache.delete(channelId, 0)
				memcache.delete(tableName, 0)
				return False

		idx += 1

	return True


def SCSelectCharacter(tokenId, characterId):
	# 인자로 받은 game channel의 playerId에 해당하는 유저의 선택 character를 업데이트
	playerData = getPlayerData(tokenId)

	if playerData is None:
		return 'disconnected'

	# timestamp 갱신
	playerData.setTimestamp(time.time() )

	channelId = playerData.getPlayerGameChannel()
	playerId = playerData.getPlayerId()

	# update 적용하기 위한 타겟 game data 불러오기 
	gameData = getGameData(channelId)
	if gameData is None:
		return 'disconnected'

	if gameData.selectCharacter(playerId, characterId):
		# 캐릭터 선택 성공 - 결과를 다시 redis에 저장
		# request를 보낸 클라이언트는 바로 응답을 받으므로 update flag를 false로 바꿔준다
		gameData.setPlayerUpdateFlag(playerId, False)
		jsonData = json.dumps(gameData.data)
		memcache.set(channelId, jsonData, gameDataTTL)
	else:
		# 캐릭터 선택 실패 - 지금 상태 유지 
		jsonData = 'not updated'

	print jsonData

	return jsonData


def SCSelctMap(tokenId, mapId):
	# 인자로 받은 game channel의 map 정보를 업데이트
	playerData = getPlayerData(tokenId)

	if playerData is None:
		return 'disconnected'

	# timestamp 갱신
	playerData.setTimestamp(time.time() )

	channelId = playerData.getPlayerGameChannel()
	playerId = playerData.getPlayerId()

	# update 적용하기 위한 타겟 game data 불러오기 
	gameData = getGameData(channelId)
	if gameData is None:
		return 'disconnected'

	if gameData.isChannelMaster(playerId) == 1:
		# 요청한 유저가 방장이므로 맵 크기를 설정한다. 
		gameData.setMapSize(mapId)

		# request를 보낸 클라이언트는 바로 응답을 받으므로 update flag를 false로 바꿔준다
		gameData.setPlayerUpdateFlag(playerId, False)

		jsonData = json.dumps(gameData.data)
		memcache.set(channelId, jsonData, gameDataTTL)

	else:
		jsonData = 'not updated'

	return jsonData


def SCReady(tokenId):
	# 인자로 받은 player의 대기 상태 업데이트
	playerData = getPlayerData(tokenId)

	if playerData is None:
		return 'disconnected'

	# timestamp 갱신
	playerData.setTimestamp(time.time() )

	channelId = playerData.getPlayerGameChannel()
	playerId = playerData.getPlayerId()

	# update 적용하기 위한 타겟 game data 불러오기 
	gameData = getGameData(channelId)
	if gameData is None:
		return 'disconnected'

	# 일단 레디 상태 변경 
	gameData.changeReadyFlag(playerId)

	# 모두 레디 상태이면 다음씬으로 전환(play scene)
	if gameData.isAllReady():
		gameData.startGame()

	# request를 보낸 클라이언트는 바로 응답을 받으므로 update flag를 false로 바꿔준다
	gameData.setUpdateFlag()
	gameData.setPlayerUpdateFlag(playerId, False)

	jsonData = json.dumps(gameData.data)
	memcache.set(channelId, jsonData, gameDataTTL)

	return jsonData

def PCReady(tokenId):
	# 인자로 받은 player의 대기 상태 업데이트
	playerData = getPlayerData(tokenId)

	if playerData is None:
		return 'disconnected'

	# timestamp 갱신
	playerData.setTimestamp(time.time() )

	channelId = playerData.getPlayerGameChannel()
	playerId = playerData.getPlayerId()

	# update 적용하기 위한 타겟 game data 불러오기 
	gameData = getGameData(channelId)
	if gameData is None:
		return 'disconnected'

	# 일단 레디 상태 변경 
	gameData.changeReadyFlag(playerId)

	if gameData.getWaitingReadyFlag():
		# 모두 레디 상태이면 다음 턴 시작
		if gameData.isAllReady():
			gameData.startTurn()

	# request를 보낸 클라이언트는 바로 응답을 받으므로 update flag를 false로 바꿔준다
	gameData.setUpdateFlag()
	gameData.setPlayerUpdateFlag(playerId, False)

	jsonData = json.dumps(gameData.data)
	memcache.set(channelId, jsonData, gameDataTTL)

	return 'ready'

def PCDrawLine(tokenId, lineIdx):
	playerData = getPlayerData(tokenId)

	if playerData is None:
		return 'disconnected'

	# timestamp 갱신
	playerData.setTimestamp(time.time() )

	channelId = playerData.getPlayerGameChannel()
	playerId = playerData.getPlayerId()

	# update 적용하기 위한 타겟 game data 불러오기 
	gameData = getGameData(channelId)
	if gameData is None:
		return 'disconnected'

	if gameData.getWaitingReadyFlag():
		return 'not updated'

	# 이번에 그을 플레이어가 맞는지 턴 확인
	if gameData.getCurrentTurnId() == playerId:
		# 입력한 좌표로 긋기
		if gameData.drawLine(lineIdx[0], lineIdx[1]):
			print 'it\'s possible'
			# request를 보낸 클라이언트는 바로 응답을 받으므로 update flag를 false로 바꿔준다
			gameData.setPlayerUpdateFlag(playerId, False)

			jsonData = json.dumps(gameData.data)
			memcache.set(channelId, jsonData, gameDataTTL)

			return jsonData

		return 'not updated'

	return 'not updated'

def PCPlayUpdate(tokenId):
	playerData = getPlayerData(tokenId)

	if playerData is None:
		return 'disconnected'

	# timestamp 갱신
	# playerData.setTimestamp(time.time() )

	playerId = playerData.getPlayerId()
	channelId = playerData.getPlayerGameChannel()

	gameData = getGameData(channelId)
	if gameData is None:
		return 'disconnected'

	# 그냥 혼자 남으면 무조건 방폭 시키자 
	if not checkPlayerConnection(channelId, gameData):
		return 'disconnected'

	# 만약 지금이 플레이 씬이라면 아래 조건 수행 
	if gameData.getScene() == 3: # SC_PLAY
		currentTime = time.time()
		if (time.time() - gameData.getTurnStartTime() ) > 21:
			# 여기에 안 들어 온다!!!!

			# 랜덤으로 긋기
			randomIdx = gameData.makeRandomLine()
			if gameData.drawLine(randomIdx[0], randomIdx[1]):
				gameData.setPlayerUpdateFlag(playerId, False)

				jsonData = json.dumps(gameData.data)
				memcache.set(channelId, jsonData, gameDataTTL)

				return jsonData
				
	# client가 확인해야 하는 업데이트 내용이 있는지 확인 
	if gameData.getPlayerUpdateFlag(playerId):
		gameData.setPlayerUpdateFlag(playerId, False)

		jsonData = json.dumps(gameData.data)
		memcache.set(channelId, jsonData, gameDataTTL)

		return jsonData

	return 'not updated'


def PCUpdateGameResult(gameChannelId):
	# 인자로 받은 game channel의 데이터를 기반으로 결과 계산
	return #gameData



#################################################
#					flask 관련 					#
#################################################

# game server
@app.route('/authentication')
def authentication():
    """Return a friendly HTTP greeting."""

    user = users.get_current_user()

    if user:
    	return 'game start!'
    else:
    	return redirect(users.create_login_url(request.url) )


@app.route('/authentication_check')
def authenticationCheck():
    """Return a friendly HTTP greeting."""

    user = users.get_current_user()

    if user:
    	return 'ok'
    else:
    	return 'fail'


@app.route('/login', methods=['POST','GET'])
def login():
	try : 
		if request.method  == "POST":  
			user = users.get_current_user()

			if not user:
				return 'disconnected'

			tokenId = user.user_id()
			name = user.nickname()

			two = int(request.form['two'])
			three = int(request.form['three'])
			four = int(request.form['four'])

			# 플레이어 데이터 생성
			playerData = dataStructure.PlayerData()
			playerData.initData(tokenId, name)
			playerData.setPlayerNumber(two, three, four)

			# timestamp 갱신
			playerData.setTimestamp(time.time() )

			# 생성한 데이터 redis에 저장 
			jsonData = json.dumps(playerData.data)
			if memcache.get(tokenId) == None:
				memcache.add(tokenId, jsonData, waitingChannelTTL)
			else:
				memcache.set(tokenId, jsonData, waitingChannelTTL)

			# 대기열에 추가 및 바뀐 대기열 상태로 매칭 시도
			if memcache.get("waiting_list") == None:
				waitingList = [tokenId]
				waitingListData = json.dumps(waitingList)
				memcache.add("waiting_list", waitingListData)
			else:
				waitingList = json.loads(memcache.get("waiting_list"))
				if not tokenId in waitingList:
					waitingList.append(tokenId)
					memcache.set("waiting_list", json.dumps(waitingList))

			playerMatching()

			# print tokenId
			
			return 'login' 

	except KeyError, err:
		print 'error  ->  : ' ,err 
		return '서버에서 알 수 없는 요청데이터가 있습니다.(잘못된 요청일 수도 있고요)\n'


@app.route('/logout', methods=['POST','GET'])
def logout():
	try : 
		if request.method  == "POST":
			user = users.get_current_user()

			if not user:
				return 'disconnected'

			tokenId = user.user_id()

			playerData = getPlayerData(tokenId)

			if playerData is None:
				return 'disconnected'

			channelId = playerData.getPlayerGameChannel()

			if channelId == 'no channel':
				# 게임 중 아니면 대기 리스트에서 삭제
				waitingListData = memcache.get("waiting_list")
				waitingList = json.loads(waitingListData)
				waitingList.remove(tokenId)
				memcache.set("waiting_list", json.dumps(waitingList))
			else:
				# 게임 중이면 게임 채널에서 삭제
				gameData = getGameData(channelId)
				if gameData is None:
					return 'disconnected'

				if not gameData.removePlayer(playerData.getPlayerId()):
					# 유저들도 삭제해야 되는데
					# 그냥 냅두고 유저들의 요청을 받아서 해당하는 채널데이터가 없으면 디스커넥 시킴
					# 그럼 TTL설정에 의해서 알아서 삭제됨
					# redis에서 채널 삭제 
					memcache.delete(channelId, 0)
					tableName = channelId + ' table'
					memcache.delete(tableName, 0)

			# redis에서 플레이 삭제
			memcache.delete(tokenId, 0)
			
			return 'logout' 

	except KeyError, err:
		print 'error  ->  : ' ,err 
		return '서버에서 알 수 없는 요청데이터가 있습니다.(잘못된 요청일 수도 있고요)\n'


@app.route('/join_update', methods=['POST','GET'])
def joinUpdate():
	# 보낸 유저의 session 정보를 바탕으로 redis안에서 현재 유저의 정보를 확인한다.
	# 만약 속한 game channel이 있다면 현재 배정받은 player id를 전송한다.
	# id를 전송받은 클라이언트는 그 id 값을 저장하고, game data를 요청한다.
	# 만약 아직 속한 game channel에 없다면 유저는 대기 화면을 보는 상태 유지하면서 1초 후에 다시 확인 시도
	try : 
		if request.method  == "POST":  
			user = users.get_current_user()

			if not user:
				return 'disconnected'

			tokenId = user.user_id()

			# player data 불러오기 
			playerData = getPlayerDataNoTTLReset(tokenId)

			# time out : 적합한 상대를 못 찾음
			if playerData is None:
				return 'channel not found'

			# 일단 스탬프는 갱신
			playerData.setTimestamp(time.time() )

			playerId = playerData.getPlayerId()

			if playerId is not -1:
				# 채널 할당 받았으므로 id를 memcache에 업데이트
				# 그렇지 않을 때 업데이트 하지 않는 이유는 TTL 초기화 안 하려고
				# 채널 대기 시간 지나면 타임아웃해야 되므로 여기서 계속 초기화하면 안 끝남
				jsonData = json.dumps(playerData.data)
				memcache.set(tokenId, jsonData, playerDataTTL)

			# print playerId
			return str(playerId)

	except KeyError, err:
		print 'error  ->  : ' ,err 
		return '서버에서 알 수 없는 요청데이터가 있습니다.(잘못된 요청일 수도 있고요)\n'


@app.route('/get_initialized_gamedata', methods=['POST','GET'])
def getInitializedGameData():
	# 채널을 할당 받아서 게임 세팅으로 넘어 가기 전에 초기 게임 데이터를 요청한다.
	# 요청한 클라이언트의 tokenId를 이용해서 해당 game channel을 찾아서 그 데이터를 전송한다.
	# 이때 요청한 클라이언트의 update flag는 false로 바꿔준다.
	try : 
		if request.method  == "POST":  
			user = users.get_current_user()

			if not user:
				return 'disconnected'

			tokenId = user.user_id()

			playerData = getPlayerData(tokenId)

			if playerData is None:
				return 'disconnected'

			# timestamp 갱신
			playerData.setTimestamp(time.time() )

			playerId = playerData.getPlayerId()
			channelId = playerData.getPlayerGameChannel()

			# print channelId
			# print memcache.get(channelId)

			gameData = getGameData(channelId)
			if gameData is None:
				return 'disconnected'

			# flag 상태 변경 
			gameData.setPlayerUpdateFlag(playerId, False)

			jsonData = json.dumps(gameData.data)
			memcache.set(channelId, jsonData, gameDataTTL)

			return jsonData

	except KeyError, err:
		print 'error  ->  : ' ,err 
		return '서버에서 알 수 없는 요청데이터가 있습니다.(잘못된 요청일 수도 있고요)\n'


@app.route('/select_character', methods=['POST','GET'])
def selectCharacter():
	# 보낸 유저의 session 정보를 바탕으로 어떤 game channel에 반영할 지 판단(redis 안에 저장된 user 정보 참조)
	# 해당 game channel의 데이터를 불러와서 게임 데이터에서 플레이어의 캐릭터id 정보를 업데이트한다.
	# 업데이트 결과를 redis에 저장하고, 요청을 보낸 유저에게는 변경된 게임 데이터를 바로 전송한다.
	try : 
		if request.method  == "POST":  
			# parsing
			user = users.get_current_user()

			if not user:
				return 'disconnected'

			tokenId = user.user_id()
			characterId = int(request.form['characterId'])

			return SCSelectCharacter(tokenId, characterId)

	except KeyError, err:
		print 'error  ->  : ' ,err 
		return 'error code'


@app.route('/select_map', methods=['POST','GET'])
def selectMap():
	# 보낸 유저의 session 정보를 바탕으로 어떤 game channel에 반영할 지 판단(redis 안에 저장된 user 정보 참조)
	# 해당 game channel의 데이터를 불러와서 현재 선택된 맵 정보를 업데이트한다.
	# 업데이트 결과를 redis에 저장하고, 요청을 보낸 유저에게는 변경된 게임 데이터를 바로 전송한다.
	try : 
		if request.method  == "POST": 
			user = users.get_current_user()

			if not user:
				return 'disconnected'

			tokenId = user.user_id()
			mapId = int(request.form['mapId'])

			return SCSelctMap(tokenId, mapId)

	except KeyError, err:	#parameter name을 잘못 인식한 경우에 
		print 'error  ->  : ' ,err 
		return 'error code'


@app.route('/setting_ready', methods=['POST','GET'])
def settingReady():
	# 보낸 유저의 session 정보를 바탕으로 어떤 game channel에 반영할 지 판단(redis 안에 저장된 user 정보 참조)
	# 해당 game channel의 데이터를 불러와서 플레이어의 setting scene 관련 레디 정보를 입력한다.
	# (game logic에서는 만약 현재 game channel에 접속 중인 플레이어 모두 레디 상태이면 게임을 시작한다)
	# 업데이트 결과를 redis에 저장하고, 요청을 보낸 유저에게는 변경된 게임 데이터를 바로 전송한다.
	try : 
		if request.method  == "POST":  
			user = users.get_current_user()

			if not user:
				return 'disconnected'

			tokenId = user.user_id()

			print "*** READY ***"

			return SCReady(tokenId)

	except KeyError, err:	#parameter name을 잘못 인식한 경우에 
		print 'error  ->  : ' ,err 
		return 'error code'


@app.route('/play_ready', methods=['POST','GET'])
def playReady():
	# 보낸 유저의 session 정보를 바탕으로 어떤 game channel에 반영할 지 판단(redis 안에 저장된 user 정보 참조)
	# 해당 game channel의 데이터를 불러와서 플레이어의 play scene에 관련된 ready 상태를 변경한다.
	# (만약 모든 유저가 ready 사인을 보냈다면 logic은 다음 턴을 시작한다.)
	# 업데이트 결과를 redis에 저장하고, 요청을 보낸 유저에게는 변경된 게임 데이터를 바로 전송한다.
	try : 
		if request.method  == "POST":  
			user = users.get_current_user()

			if not user:
				return 'disconnected'

			tokenId = user.user_id()

			return PCReady(tokenId)

	except KeyError, err:	#parameter name을 잘못 인식한 경우에 
		print 'error  ->  : ' ,err 
		return 'error code'


@app.route('/play_update', methods=['POST','GET'])
def playUpdate():
	# 보낸 유저의 session 정보를 바탕으로 어떤 game channel에 반영할 지 판단(redis 안에 저장된 user 정보 참조)
	# 해당 game channel의 데이터를 불러와서 바로 전송한다.
	try : 
		if request.method  == "POST":  
			user = users.get_current_user()

			if not user:
				return 'disconnected'

			tokenId = user.user_id()

			return PCPlayUpdate(tokenId)

	except KeyError, err:	#parameter name을 잘못 인식한 경우에 
		print 'error  ->  : ' ,err 
		return 'error code'


@app.route('/draw_line', methods=['POST','GET'])
def drawLine():
	# 보낸 유저의 session 정보를 바탕으로 어떤 game channel에 반영할 지 판단(redis 안에 저장된 user 정보 참조)
	# 해당 game channel의 데이터를 불러와서 선을 그린다.
	# 업데이트 결과를 redis에 저장하고, 요청을 보낸 유저에게는 변경된 게임 데이터를 바로 전송한다.
	# (만약 게임이 종료되었다면 종료 메시지와 함께 게임 결과 데이터를 전송한다.)
	try : 
		if request.method  == "POST":  
			user = users.get_current_user()

			if not user:
				return 'disconnected'

			tokenId = user.user_id()
			posI = int(request.form['posI'])
			posJ = int(request.form['posJ'])

			# print(str(tokenId) + ' : ' + str(posI) + ' / ' + str(posJ))

			return PCDrawLine(tokenId, [posI, posJ])

	except KeyError, err:	#parameter name을 잘못 인식한 경우에 
		print 'error  ->  : ' ,err 
		return 'error code'


@app.route('/game_end', methods=['POST','GET'])
def gameEnd():
	# 보낸 유저의 session 정보를 바탕으로 어떤 game channel에 반영할 지 판단(redis 안에 저장된 user 정보 참조)
	# 해당 game channel의 데이터를 불러와서 플레이어의 game end 상태를 변경한다.
	# 이 메시지를 보낸 유저는 로그인 정보에서 삭제한다.
	# 만약 game channel 내의 모든 유저가 이 메시지를 전송하면 game channel 정보를 DB에 저장하고 redis에서 삭제한다.
	try : 
		if request.method  == "POST":  
			user = users.get_current_user()

			if not user:
				return 'disconnected'

			tokenId = user.user_id()

			playerData = getPlayerData(tokenId)

			if playerData is None:
				return 'disconnected'

			# timestamp 갱신
			playerData.setTimestamp(time.time() )

			channelId = playerData.getPlayerGameChannel()

			jsonData = json.dumps(playerData.data)
			memcache.set(tokenId, jsonData, playerDataTTL)

			gameData = getGameData(channelId)
			if gameData is not None:
				# 게임 채널에서 삭제
				gameData.removePlayer(playerData.getPlayerId())

				# redis에서 플레이어 삭제
				memcache.delete(tokenId, 0)

				if gameData.getCurrentPlayerNumber() == 0:
					# redis에서 채널 삭제 
					memcache.delete(channelId, 0)

			return 'end'

	except KeyError, err:	#parameter name을 잘못 인식한 경우에 
		print 'error  ->  : ' ,err 
		return 'error code'
		

@app.route('/get_google_nick', methods=['POST','GET'])
def getGoogleNick():
	try : 
		if request.method  == "GET":  
			user = users.get_current_user()

			if not user:
				return 'disconnected'

			name = user.nickname()
			
			return name

	except KeyError, err:
		print 'error  ->  : ' ,err 
		return '서버에서 알 수 없는 요청데이터가 있습니다.(잘못된 요청일 수도 있고요)\n'


@app.errorhandler(404)
def page_not_found(e):
    """Return a custom 404 error."""
    return 'Sorry, Nothing at this URL.', 404