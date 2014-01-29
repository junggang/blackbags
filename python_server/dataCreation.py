# -*- coding: utf-8 -*-

# player data 관련 함수들
def makePalyerData(tokenId, name):
	playerData = {
		'player token id' : tokenId,
		'player game channel id' : -1,
		'player name' : name,
		'player id' : -1
	}

	return playerData

def setChannelId(playerData, channelId):
	playerData['plaeyer game channel id'] = channelId


# game data 관련 함수들
def makeGameData(gameChannelId):
	# make structure
	gameData = {
		'game current scene' : 'no scene',
		'game channel id' : gameChannelId,
		'game map id' : -1,
		'game channel current turn id' : -1,
		'game channel turn list' : [],
		'game turn start flag' : False,
		'game recently connected line idx' : [0, 0],
		'game channel void tile' : -1,
		'game channel player number' : 0,
		'game channel player list' : [],
		'game channel map size' : [0, 0],
		'game channel map' : []
	}

	# add players data
	for i in range(4):
		gameData['game channel player list'].append({})

		gameData['game channel player list'][i]['player name'] = 'nothing'
		gameData['game channel player list'][i]['player master flag'] = False
		gameData['game channel player list'][i]['player connection flag'] = False
		gameData['game channel player list'][i]['character id'] = -1
		gameData['game channel player list'][i]['turn'] = -1
		gameData['game channel player list'][i]['tile number'] = 0
		gameData['game channel player list'][i]['gold number'] = 0
		gameData['game channel player list'][i]['trash number'] = 0
		gameData['game channel player list'][i]['score'] = 0

	# add map data
	for i in range(23):
		gameData['game channel map'].append([])

		for j in range(23):
			gameData['game channel map'][i].append({})

			gameData['game channel map'][i][j]['type'] = 'SENTINEL'
			gameData['game channel map'][i][j]['owner'] = 'NOBODY'
			gameData['game channel map'][i][j]['item'] = 'NOTHING'
			gameData['game channel map'][i][j]['checkedFlag'] = False
			gameData['game channel map'][i][j]['animation turn'] = 0
			gameData['game channel map'][i][j]['direction'] = 'UP'

	# return the result data
	return gameData

def setMapSize(gmaeData, width, height):
	gameData['game channel void tile'] = width * height
	gameData['game channel map size'][0] = width
	gameData['game channel map size'][0] = height

	# map init code


def addPlayer(gameData, playerData):
	for idx in range(4):
		if gameData['game channel player list'][idx]['player connection flag'] == False:
			setChannelId(playerData, gameData['game channel id'])
			++gameData['game channel player number']
			
			gameData['game channel player list'][idx]['player name'] = playerData['player name']
			gameData['game channel player list'][idx]['player connection flag'] = True

			return True

	return False
	


if __name__ == '__main__':
	# test : player creation
	player_moon = makePalyerData(29, 'prof. moon')
	player_jg = makePalyerData(67, 'JUNGGANG')
	player_wooq = makePalyerData(80, 'wooq')

    # test : game data creation
	testGameData = makeGameData(4)

	#insert player to game channel
	result = addPlayer(testGameData, player_moon)

	if result == True:
		result = addPlayer(testGameData, player_jg)

	if result == True:
		result = addPlayer(testGameData, player_wooq)

	print testGameData