# -*- coding: utf-8 -*-
import json
import redis
from flask import Flask,url_for, session, escape, request, redirect
import dataStructure
import threading
import time
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

#################################################
#				matching thread 관련				#
#################################################
# 대기 리스트를 하나 만든다 (공유자원 - 동기화 기능을 지원하는 자료구조이어야 함)
# 리스트는 redis안에 저장된 player data에 접근하는 key value를 가지고 있다
# 리스트의 값들은 추가된 순서를 유지한다
global watingList

def playerMatching():
	player_2 = []
	player_3 = []
	player_4 = []

	# channel id 생성하는 로직 구현 필요 
	channelId = 0

	while True:
		print 'try to make game channels'
		print watingList

		for each in watingList:
			playerData = getPlayerData(each)

			if playerData.getPlayerNumber(2) == 1:
				player_2.append(each)

				if len(player_2) == 2:
					# 2명 방 생성
					gameData = dataStructure.GameData()
					gameData.initData(channelId)
					channelId += 1

					# 플레이어 추가 
					for player in player_2:
						print 'player 2 : ' + player
						playderData = getPlayerData(player)
						gameData.addPlayer(playerData)

					# 생성한 게임 데이터 redis에 저장 
					jsonData = json.dumps(gameData.data)
					gRedis.set(channelId, jsonData)

					watingList.remove(each)

					break

			if playerData.getPlayerNumber(3) == 1:
				player_3.append(each)

				if len(player_3) == 3:
					# 3명 방 생성
					gameData = dataStructure.GameData()
					gameData.initData(channelId)
					channelId += 1

					# 플레이어 추가 
					for player in player_3:
						print 'player 3 : ' + player
						playderData = getPlayerData(player)
						gameData.addPlayer(playerData)

					# 생성한 게임 데이터 redis에 저장 
					jsonData = json.dumps(gameData.data)
					gRedis.set(channelId, jsonData)

					watingList.remove(each)

					break

			if playerData.getPlayerNumber(4) == 1:
				player_4.append(each)

				if len(player_4) == 4:
					# 3명 방 생성
					gameData = dataStructure.GameData()
					gameData.initData(channelId)
					channelId += 1

					# 플레이어 추가 
					for player in player_4:
						print 'player 4 : ' + str(player)
						playderData = getPlayerData(player)
						gameData.addPlayer(playerData)

					# 생성한 게임 데이터 redis에 저장 
					jsonData = json.dumps(gameData.data)
					gRedis.set(channelId, jsonData)

					watingList.remove(each)

					break

		del player_2[0:len(player_2)]
		del player_3[0:len(player_3)]
		del player_4[0:len(player_4)]

		time.sleep(1)

# while True:
# 	각 참여 인원에 대한 가상의 풀을 만든다
# 	대기 시간이 긴 플레이어부터 선택한 참여 인원의 풀에 추가
#	추가와 함께 해당하는 참여인원이 모두 모이면 추가된 플레이어들로 채널 생성
#	앞에서 생성된 채널에 추가된 플레이어는 리스트에서 삭제하고 다시 작업을 반복
#	대기 시간은 1초에서 2초 정도 준다

# matching thread는 서버가 시작되면 같이 실행된다.
# 리스트에 있는 사람들이 바뀔 때마다 현재 리스트에 있는 사람들을 가지고 게임 채널 생성하고 채널 테이블을 레디스에 생성



#################################################
#				gameLogic 관련					#
#################################################

# game logic은 게임의 인풋이 도착하면 redis에 있는 데이터를 가져와서 업데이트 시키고 다시 저장한다
# 모든 인풋은 유효성 검사가 필수
def getPlayerData(tokenId):
	playerData = dataStructure.PlayerData()
	playerData.insertData(json.loads(gRedis.get(tokenId)))

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
		jsonData = json.dumps(gameData.data)
		gRedis.set(channelId, jsonData)
	else:
		# 캐릭터 선택 실패 - 지금 상태 유지 
		jsonData = json.dumps(gameData.data)

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
		if mapId == 1:
			gameData.setMapSize(5, 6)
		elif mapId == 2:
			gameData.setMapSize(7, 8)

		jsonData = json.dumps(gameData.data)
		gRedis.set(channelId, jsonData)

	else:
		jsonData = json.dumps(gameData.data)

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

	jsonData = json.dumps(gameData.data)

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

	# 모두 레디 상태이면 다음씬으로 전환(play scene)
	if gameData.isAllReady():
		gameData.startTurn()

	jsonData = json.dumps(gameData.data)

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
			jsonData = json.dumps(gameData.data)
			gRedis.set(channelId, jsonData)
		else:
			jsonData = json.dumps(gameData.data)

		return jsonData

	return json.dumps(gameData.data)


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
			# userTable에 접속한 사람을 추가한다
			tokenId = 'temp'
			name = 'noname'

			two = 1
			three = 1
			four = 1
			
			# 플레이어 데이터 생성 (생성 전에 이미 redis안에 중복 데이터 있는지 확인)
			playerData = dataStructure.PlayerData()
			playerData.initData(tokenId, name)
			playerData.setPlayerNumber(two, three, four)

			# 생성한 데이터 redis에 저장 
			jsonData = json.dumps(playerData.data)
			gRedis.set(tokenId, jsonData)

			# 대기열에 추가
			watingList.append(tokenId)
			
			return True 

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
			tokenId = 'temp'

			# player data 불러오기 
			playerData = getPlayerData(tokenId)

			playerId = playerData.getPlayerId()
			if playerId != -1:
				# 할당 된 channel이 있으면 그 channel 안에서의 player id 값을 전송 
				return playerId
			else:
				return # 

	except KeyError, err:
		print 'error  ->  : ' ,err 
		return '서버에서 알 수 없는 요청데이터가 있습니다.(잘못된 요청일 수도 있고요)\n'


@app.route('/select_character/', methods=['POST','GET'])
def selectCharacter():
	# 보낸 유저의 session 정보를 바탕으로 어떤 game channel에 반영할 지 판단(redis 안에 저장된 user 정보 참조)
	# 해당 game channel의 데이터를 불러와서 게임 데이터에서 플레이어의 캐릭터id 정보를 업데이트한다.
	# 업데이트 결과를 redis에 저장하고, 요청을 보낸 유저에게는 변경된 게임 데이터를 바로 전송한다.
	try : 
		if request.method  == "POST":  
			# parsing
			tokenId = 'temp'
			characterId = 1

			return SCSelectCharacter(tokenId, characterId)

	except KeyError, err:
		print 'error  ->  : ' ,err 
		return 'error code'


@app.route('/select_map/', methods=['POST','GET'])
def selectMap():
	# 보낸 유저의 session 정보를 바탕으로 어떤 game channel에 반영할 지 판단(redis 안에 저장된 user 정보 참조)
	# 해당 game channel의 데이터를 불러와서 현재 선택된 맵 정보를 업데이트한다.
	# 업데이트 결과를 redis에 저장하고, 요청을 보낸 유저에게는 변경된 게임 데이터를 바로 전송한다.
	try : 
		if request.method  == "POST": 

			tokenId = 'temp'
			mapId = 1

			return SCSelctMap(tokenId, mapId)

	except KeyError, err:	#parameter name을 잘못 인식한 경우에 
		print 'error  ->  : ' ,err 
		return 'error code'


@app.route('/setting_ready/', methods=['POST','GET'])
def settingReady():
	# 보낸 유저의 session 정보를 바탕으로 어떤 game channel에 반영할 지 판단(redis 안에 저장된 user 정보 참조)
	# 해당 game channel의 데이터를 불러와서 플레이어의 setting scene 관련 레디 정보를 입력한다.
	# (game logic에서는 만약 현재 game channel에 접속 중인 플레이어 모두 레디 상태이면 게임을 시작한다)
	# 업데이트 결과를 redis에 저장하고, 요청을 보낸 유저에게는 변경된 게임 데이터를 바로 전송한다.
	try : 
		if request.method  == "POST":  
			tokenId = 'temp'

			return SCReady(tokenId)

	except KeyError, err:	#parameter name을 잘못 인식한 경우에 
		print 'error  ->  : ' ,err 
		return 'error code'


@app.route('/play_ready/', methods=['POST','GET'])
def playReady():
	# 보낸 유저의 session 정보를 바탕으로 어떤 game channel에 반영할 지 판단(redis 안에 저장된 user 정보 참조)
	# 해당 game channel의 데이터를 불러와서 플레이어의 play scene에 관련된 ready 상태를 변경한다.
	# (만약 모든 유저가 ready 사인을 보냈다면 logic은 다음 턴을 시작한다.)
	# 업데이트 결과를 redis에 저장하고, 요청을 보낸 유저에게는 변경된 게임 데이터를 바로 전송한다.
	try : 
		if request.method  == "POST":  
			tokenId = 'temp'

			return PCReady(tokenId)

	except KeyError, err:	#parameter name을 잘못 인식한 경우에 
		print 'error  ->  : ' ,err 
		return 'error code'


@app.route('/play_update/', methods=['POST','GET'])
def playUpdate():
	# 보낸 유저의 session 정보를 바탕으로 어떤 game channel에 반영할 지 판단(redis 안에 저장된 user 정보 참조)
	# 해당 game channel의 데이터를 불러와서 바로 전송한다.
	try : 
		if request.method  == "POST":  
			tokenId = 'temp'

			playerData = getPlayerId(tokenId)
			channelId = playerData.getPlayerGameChannel()

			return gRedis.get(channelId)

	except KeyError, err:	#parameter name을 잘못 인식한 경우에 
		print 'error  ->  : ' ,err 
		return 'error code'


@app.route('/draw_line/', methods=['POST','GET'])
def drawLine():
	# 보낸 유저의 session 정보를 바탕으로 어떤 game channel에 반영할 지 판단(redis 안에 저장된 user 정보 참조)
	# 해당 game channel의 데이터를 불러와서 선을 그린다.
	# 업데이트 결과를 redis에 저장하고, 요청을 보낸 유저에게는 변경된 게임 데이터를 바로 전송한다.
	# (만약 게임이 종료되었다면 종료 메시지와 함께 게임 결과 데이터를 전송한다.)
	try : 
		if request.method  == "POST":  
			tokenId = 'temp'
			lineIdx = []

			return PCDrawLine(tokenId, lineIdx)

	except KeyError, err:	#parameter name을 잘못 인식한 경우에 
		print 'error  ->  : ' ,err 
		return 'error code'


@app.route('/game_end/', methods=['POST','GET'])
def gameEnd():
	# 보낸 유저의 session 정보를 바탕으로 어떤 game channel에 반영할 지 판단(redis 안에 저장된 user 정보 참조)
	# 해당 game channel의 데이터를 불러와서 플레이어의 game end 상태를 변경한다.
	# 이 메시지를 보낸 유저는 로그인 정보에서 삭제한다.
	# 만약 game channel 내의 모든 유저가 이 메시지를 전송하면 game channel 정보를 DB에 저장하고 redis에서 삭제한다.
	try : 
		if request.method  == "POST":  
			tokenId = 'temp'

			# session.pop('username', None) # logout!
			return

	except KeyError, err:	#parameter name을 잘못 인식한 경우에 
		print 'error  ->  : ' ,err 
		return 'error code'



if __name__ == '__main__':
	gRedis = connect_redis()

	watingList = []

	# thread.start_new_thread(playerMatching)
	matchingThread = threading.Thread(target=playerMatching)
	matchingThread.start()

	time.sleep(5)
	print 'prof. moon'
	playerData = dataStructure.PlayerData()
	playerData.initData(29, 'prof. moon')
	playerData.setPlayerNumber(0, 1, 1)

	# 생성한 데이터 redis에 저장 
	jsonData = json.dumps(playerData.data)
	gRedis.set(29, jsonData)

	# 대기열에 추가
	watingList.append(29)

	time.sleep(5)
	print 'JUNGGANG'
	playerData = dataStructure.PlayerData()
	playerData.initData(67, 'JUNGGANG')
	playerData.setPlayerNumber(0, 1, 1)

	# 생성한 데이터 redis에 저장 
	jsonData = json.dumps(playerData.data)
	gRedis.set(67, jsonData)

	# 대기열에 추가
	watingList.append(67)

	time.sleep(5)
	print 'wooq'
	playerData = dataStructure.PlayerData()
	playerData.initData(80, 'wooq')
	playerData.setPlayerNumber(0, 1, 1)

	# 생성한 데이터 redis에 저장 
	jsonData = json.dumps(playerData.data)
	gRedis.set(80, jsonData)

	# 대기열에 추가
	watingList.append(80)


	app.debug = True
	app.secret_key = '\xab\x11\xcb\xdb\xf2\xb9\x0e\xd9N\xbd\x17$\x07\xc9H\x19\x96h\x8a\xf2<`-A'
	app.run()