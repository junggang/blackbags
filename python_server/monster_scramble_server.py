# -*- coding: utf-8 -*-
import redis
import json
from flask import Flask,url_for, session, escape, request, redirect
import dataStructure
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

#################################################
#				matching thread 관련				#
#################################################

# matching thread는 서버가 시작되면 같이 실행된다.
# 리스트에 있는 사람들이 바뀔 때마다 현재 리스트에 있는 사람들을 가지고 게임 채널 생성하고 채널 테이블을 레디스에 생성



#################################################
#				gameLogic 관련					#
#################################################

# game logic은 게임의 인풋이 도착하면 redis에 있는 데이터를 가져와서 업데이트 시키고 다시 저장한다
# 모든 인풋은 유효성 검사가 필수
def getPlayerData(tokenId):
	playerData = dataStructure.PlayerData()
	playerData.insertData(json.loads(redis.get(tokenId)))

	return playerData


def getGameData(channelId):
	gameData = dataStructure.GameData()
	gameData.insertData(json.loads(redis.get(channelId)))

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
		redis.set(channelId, jsonData)
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
		redis.set(channelId, jsonData)

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
			redis.set(channelId, jsonData)
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
	return redis.StrictRedis(host=REDIS_ADDRESS, port=REDIS_PORT, db=0)



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
			
			playerData = dataStructure.PlayerData(tokenId, name)
			jsonData = json.dumps(playerData)

			redis.set(tokenId, jsonData)

			# userTable 구조 추가 생성 필요 - thread 만들면서 같이 만들자 

			return # 

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
			playerData = json.loads(redis.get(tokenId))

			playerId = playerData[PD_PLAYER_ID]
			if playerId != -1:
				# 할당 된 player id가 있으면 그 값을 전송 
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

			channelId = (json.loads(redis.get(playerSession)))[PD_GAME_CHANNEL_ID]
			return redis.get(channelId)

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

    app.debug = True
    app.secret_key = '\xab\x11\xcb\xdb\xf2\xb9\x0e\xd9N\xbd\x17$\x07\xc9H\x19\x96h\x8a\xf2<`-A'
    app.run()