# -*- coding: utf-8 -*-
import json
import redis
from flask import Flask,url_for, session, escape, request, redirect
import dataStructure
import threading
import time
import sys
import random

reload(sys)
sys.setdefaultencoding('utf-8')

global watingList
global timerThreadList
global cleanupTimer

#################################################
#				matching thread 관련				#
#################################################
# 대기 리스트를 하나 만든다 (공유자원 - 동기화 기능을 지원하는 자료구조이어야 함)
# 리스트는 redis안에 저장된 player data에 접근하는 key value를 가지고 있다
# 리스트의 값들은 추가된 순서를 유지한다

def createAvailableChannel(playerPool, playerNumber, playerData, tokenId):
	if playerData.getPlayerNumber(playerNumber) == 1:
		playerPool.append(tokenId)

		if len(playerPool) == playerNumber:
			# channel id 생성하는 로직 구현 필요 
			channelId = getNewChannelId

			gameData = dataStructure.GameData()
			gameData.initData(channelId)

			# 플레이어 추가 
			for player in playerPool:
				print 'player number ' + str(playerNumber) + ' : ' + player
				playerData = getPlayerData(player)
				gameData.addPlayer(playerData)
				watingList.remove(player)

				print playerData.data[3]

				# player data 저장
				gRedis.set(player, json.dumps(playerData.data) )

			# 생성한 게임 데이터 redis에 저장 
			jsonData = json.dumps(gameData.data)
			gRedis.set(channelId, jsonData)

			return True

	return False


def playerMatching():
	# matching thread는 서버가 시작되면 같이 실행된다.
	# 리스트에 있는 사람들이 바뀔 때마다 현재 리스트에 있는 사람들을 가지고 게임 채널 생성하고 채널 테이블을 레디스에 생성

	player_2 = []
	player_3 = []
	player_4 = []

	# channel id 생성하는 로직 구현 필요 
	channelId = 0

	# while True:
	# 	각 참여 인원에 대한 가상의 풀을 만든다
	# 	대기 시간이 긴 플레이어부터 선택한 참여 인원의 풀에 추가
	#	추가와 함께 해당하는 참여인원이 모두 모이면 추가된 플레이어들로 채널 생성
	#	앞에서 생성된 채널에 추가된 플레이어는 리스트에서 삭제하고 다시 작업을 반복
	#	대기 시간은 1초에서 2초 정도 준다
	while True:
		for each in watingList:
			playerData = getPlayerData(each)

			if createAvailableChannel(player_2, 2, playerData, each):
				break
			
			if createAvailableChannel(player_3, 3, playerData, each):
				break

			if createAvailableChannel(player_4, 4, playerData, each):
				break

		del player_2[0:len(player_2)]
		del player_3[0:len(player_3)]
		del player_4[0:len(player_4)]

		# 슬립 1초가 있으면 아무리 사람이 많아도 1초에 채널 1개씩밖에 생성 안 된다
		time.sleep(1)

def getNewChannelId():
	newChannelId = 0

	while True:
		newChannelId = random.randint(1, 1024)
		
		if gRedis.get(newChannelId) == None:
			return newChannelId



#################################################
#				cleanup thread 관련				#
#################################################
# 주기적으로 실행돼서 오랫동안 응답이 없는 플레이어는 redis 안에서 삭제
def cleanup():
	print '***START CLEANUP***'
	
	# redis에서 key목록 가져오기
	keys = gRedis.keys('*')

	for key in keys:
		keyType = redis.type(key)
		if keyType == KV:
			if not type(key) is int:
				# key가 key-value의 형식이고 그 자료형이 int가 아니면 플레이어 데이터에 대한 접근 키
				data = json.loads(gRedis.get(key) )

				# getPlayerData에서 자동으로 timestamp값을 업데이트 하므로 여기서는 사용할 수 없음
				# PD_TIMESTAMP = 7
				if time.time() - data[7] > 600:
					# 응답시간이 600 이상이면 삭제
					gRedis.delete(key)

	# 다음 cleanup을 위해서 스레드 새로 시작 
	startCleanupTimer()



#################################################
#				timer thread 관련				#
#################################################
# game channel id를 가지고 있다
# 시작되면 21초를 기다리고, 21초가 지나면 해당 하는 채널의 게임 데이터를 불러온다
# 불러온 게임 데이터에 랜덤 라인을 그린다
# 새로운 타이머 스레드 생성
# 타이머 관리 풀에 game channel id에 해당하는 스레드를 새로 생성한 스레드로 교체
# 새로 생성한 스레드 시작
# 종료
def randomTimer(gameChannelId):
	# 처음엔 없으니까 리스트 안에 값 있는지 확인 필요
	if gameChannelId in timerThreadList:
		del timerThreadList[gameChannelId]

	gameData = getGameData(channelId)
	randomIdx = gameData.makeRandomLine()
	if gameData.drawLine(randomIdx[0], randomIdx[1]):
		timerThreadList[gameChannelId] = threading.Timer(21, randomTimer, args=[gameChannelId])
		timerThreadList[gameChannelId].start()


def startCleanupTimer():
	# 처음엔 없으니까 리스트 안에 값 있는지 확인 필요
	cleanupTimer = threading.Timer(600, cleanup,)
	cleanupTimer.start()



#################################################
#				gameLogic 관련					#
#################################################

# game logic은 게임의 인풋이 도착하면 redis에 있는 데이터를 가져와서 업데이트 시키고 다시 저장한다
# 모든 인풋은 유효성 검사가 필수
def getPlayerData(tokenId):
	playerData = dataStructure.PlayerData()
	playerData.insertData(json.loads(gRedis.get(tokenId)))

	# timestamp 기능 (응답없는 플레이어 정보를 주기적으로 없애기 위해서)
	playerData.setTimestamp(time.time())
	jsonData = json.dumps(playerData.data)
	gRedis.set(tokenId, jsonData)

	return playerData


def getGameData(channelId):
	gameData = dataStructure.GameData()
	gameData.insertData(json.loads(gRedis.get(channelId)))

	return gameData


def SCSelectCharacter(tokenId, characterId):
	# 인자로 받은 game channel의 playerId에 해당하는 유저의 선택 character를 업데이트
	playerData = getPlayerData(tokenId)

	channelId = playerData.getPlayerGameChannel()
	playerId = playerData.getPlayerId()

	# update 적용하기 위한 타겟 game data 불러오기 
	gameData = getGameData(channelId)

	if gameData.selectCharacter(playerId, characterId):
		# 캐릭터 선택 성공 - 결과를 다시 redis에 저장
		# request를 보낸 클라이언트는 바로 응답을 받으므로 update flag를 false로 바꿔준다
		gameData.setPlayerUpdateFlag(playerId, False)
		jsonData = json.dumps(gameData.data)
		gRedis.set(channelId, jsonData)
	else:
		# 캐릭터 선택 실패 - 지금 상태 유지 
		jsonData = 'not updated'

	print jsonData

	return jsonData


def SCSelctMap(tokenId, mapId):
	# 인자로 받은 game channel의 map 정보를 업데이트
	playerData = getPlayerData(tokenId)

	channelId = playerData.getPlayerGameChannel()
	playerId = playerData.getPlayerId()

	# update 적용하기 위한 타겟 game data 불러오기 
	gameData = getGameData(channelId)

	if gameData.isChannelMaster(playerId) == 1:
		# 요청한 유저가 방장이므로 맵 크기를 설정한다. 
		gameData.setMapSize(mapId)

		# request를 보낸 클라이언트는 바로 응답을 받으므로 update flag를 false로 바꿔준다
		gameData.setPlayerUpdateFlag(playerId, False)

		jsonData = json.dumps(gameData.data)
		gRedis.set(channelId, jsonData)

	else:
		jsonData = 'not updated'

	return jsonData


def SCReady(tokenId):
	# 인자로 받은 player의 대기 상태 업데이트
	playerData = getPlayerData(tokenId)

	channelId = playerData.getPlayerGameChannel()
	playerId = playerData.getPlayerId()

	# update 적용하기 위한 타겟 game data 불러오기 
	gameData = getGameData(channelId)

	# 일단 레디 상태 변경 
	gameData.changeReadyFlag(playerId)

	# 모두 레디 상태이면 다음씬으로 전환(play scene)
	if gameData.isAllReady():
		gameData.startGame()

		# 타이머 시작
		timerThreadList[gameChannelId] = threading.Timer(21, randomTimer, arg=[gameChannelId])
		timerThreadList[gameChannelId].start()

	# request를 보낸 클라이언트는 바로 응답을 받으므로 update flag를 false로 바꿔준다
	gameData.setPlayerUpdateFlag(playerId, False)

	jsonData = json.dumps(gameData.data)
	gRedis.set(channelId, jsonData)

	return jsonData

def PCReady(tokenId):
	# 인자로 받은 player의 대기 상태 업데이트
	playerData = getPlayerData(tokenId)

	channelId = playerData.getPlayerGameChannel()
	playerId = playerData.getPlayerId()

	# update 적용하기 위한 타겟 game data 불러오기 
	gameData = getGameData(channelId)

	# 일단 레디 상태 변경 
	gameData.changeReadyFlag(playerId)

	# 모두 레디 상태이면 다음 턴 시작
	if gameData.isAllReady():
		gameData.startTurn()

		# 타이머 시작
		timerThreadList[gameChannelId] = threading.Timer(21, randomTimer, arg=[gameChannelId])
		timerThreadList[gameChannelId].start()

	# request를 보낸 클라이언트는 바로 응답을 받으므로 update flag를 false로 바꿔준다
	gameData.setPlayerUpdateFlag(playerId, False)

	jsonData = json.dumps(gameData.data)
	gRedis.set(channelId, jsonData)

	return jsonData

def PCDrawLine(tokenId, lineIdx):
	# 인자로 받은 game channel의 map 정보를 업데이트
	playerData = getPlayerData(tokenId)

	channelId = playerData.getPlayerGameChannel()
	playerId = playerData.getPlayerId()

	# update 적용하기 위한 타겟 game data 불러오기 
	gameData = getGameData(channelId)

	if gameData.getCurrentTurnId == playerId:
		if gameData.drawLine(lineIdx[0], lineIdx[1]):
			# request를 보낸 클라이언트는 바로 응답을 받으므로 update flag를 false로 바꿔준다
			gameData.setPlayerUpdateFlag(playerId, False)

			jsonData = json.dumps(gameData.data)
			gRedis.set(channelId, jsonData)

			# 기존 타이머 삭제 
			if gameChannelId in timerThreadList:
				del timerThreadList[gameChannelId]

			# 타이머 스레드 생성 및 시작
			# timerThreadList에 저장 
			timerThreadList[gameChannelId] = threading.Timer(21, randomTimer, args=[gameChannelId])
			timerThreadList[gameChannelId].start()

			return jsonData

	return 'not updated'


def PCUpdateGameResult(gameChannelId):
	# 인자로 받은 game channel의 데이터를 기반으로 결과 계산
	return #gameData


#################################################
#					redis 관련 					#
#################################################
global gRedis

def connect_redis():
	return redis.StrictRedis(host='localhost', port=6379, db=0)



#################################################
#					flask 관련 					#
#################################################
app = Flask(__name__)

@app.route('/login', methods=['POST','GET'])
def login():
	try : 
		if request.method  == "POST":  
			if not gRedis.get(tokenId) == None:
				# 이미 중복된 키가 있을 경우에 대한 처리가 필요하면 추가할 것
				pass

			tokenId = request.form['tokenId']
			name = request.form['name']

			two = int(request.form['two'])
			three = int(request.form['three'])
			four = int(request.form['four'])

			# 플레이어 데이터 생성 (생성 전에 이미 redis안에 중복 데이터 있는지 확인)
			playerData = dataStructure.PlayerData()
			playerData.initData(tokenId, name)
			playerData.setPlayerNumber(two, three, four)

			# 생성한 데이터 redis에 저장 
			jsonData = json.dumps(playerData.data)
			gRedis.set(tokenId, jsonData)

			# 대기열에 추가
			watingList.append(tokenId)
			print tokenId
			
			return 'login' 

	except KeyError, err:
		print 'error  ->  : ' ,err 
		return '서버에서 알 수 없는 요청데이터가 있습니다.(잘못된 요청일 수도 있고요)\n'


@app.route('/logout', methods=['POST','GET'])
def logout():
	try : 
		if request.method  == "POST":
			tokenId = request.form['tokenId']

			playerData = getPlayerData(tokenId)
			channelId = playerData.getPlayerGameChannel()

			if channelId == -1:
				# 게임 중 아니면 대기 리스트에서 삭제
				watingList.remove(tokenId)
			else:
				# 게임 중이면 게임 채널에서 삭제
				gameData = getGameData(channelId)
				gameData.removePlayer(playerData.getPlayerId())

				if gameData.getCurrentPlayerNumber() == 0:
					# 채널이 비었으면 관련 스레드 삭제
					if gameChannelId in timerThreadList:
						del timerThreadList[gameChannelId]

					# redis에서 채널 삭제 
					gRedis.delete(channelId)

			# redis에서 플레이 삭제
			gRedis.delete(tokenId)
			
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
			tokenId = request.form['tokenId']

			# player data 불러오기 
			playerData = getPlayerData(tokenId)

			playerId = playerData.getPlayerId()

			print tokenId
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
			tokenId = request.form['tokenId']

			playerData = getPlayerData(tokenId)
			playerId = playerData.getPlayerId()
			channelId = playerData.getPlayerGameChannel()

			print channelId + 1
			print gRedis.get(channelId)

			gameData = getGameData(channelId)

			# flag 상태 변경 
			gameData.setPlayerUpdateFlag(playerId, False)

			jsonData = json.dumps(gameData.data)
			gRedis.set(channelId, jsonData)

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
			tokenId = request.form['tokenId']
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

			tokenId = request.form['tokenId']
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
			tokenId = request.form['tokenId']

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
			tokenId = request.form['tokenId']

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
			tokenId = request.form['tokenId']

			playerData = getPlayerData(tokenId)
			playerId = playerData.getPlayerId()
			channelId = playerData.getPlayerGameChannel()

			gameData = getGameData(channelId)

			# client가 확인해야 하는 업데이트 내용이 있는지 확인 
			if gameData.getPlayerUpdateFlag(playerId):
				gameData.setPlayerUpdateFlag(playerId, False)

				jsonData = json.dumps(gameData.data)
				gRedis.set(channelId, jsonData)

				print jsonData

				return jsonData

			return 'not updated'

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
			tokenId = request.form['tokenId']
			posI = int(request.form['posI'])
			posJ = int(request.form['posJ'])

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
			tokenId = request.form['tokenId']

			playerData = getPlayerData(tokenId)
			channelId = playerData.getPlayerGameChannel()

			# 게임 채널에서 삭제
			gameData = getGameData(channelId)
			gameData.removePlayer(playerData.getPlayerId())

			if gameData.getCurrentPlayerNumber() == 0:
				# 채널이 비었으면 관련 타이머 스레드 삭제
				if gameChannelId in timerThreadList:
					del timerThreadList[gameChannelId]

				# redis에서 채널 삭제 
				gRedis.delete(channelId)

			# redis에서 플레이어 삭제
			gRedis.delete(tokenId)
			return

	except KeyError, err:	#parameter name을 잘못 인식한 경우에 
		print 'error  ->  : ' ,err 
		return 'error code'


if __name__ == '__main__':
	gRedis = connect_redis()

	watingList = []
	timerThreadList = {}

	matchingThread = threading.Thread(target=playerMatching)
	matchingThread.start()

	startCleanupTimer()

	app.debug = True
	app.secret_key = '\xab\x11\xcb\xdb\xf2\xb9\x0e\xd9N\xbd\x17$\x07\xc9H\x19\x96h\x8a\xf2<`-A'
	app.run(host='0.0.0.0')