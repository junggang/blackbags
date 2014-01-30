# -*- coding: utf-8 -*-
import Queue

# player data 관련 함수들
class PlayerData:
	closedTile = []

	def __init__(self, tokenId, name):
		self.data = {
			'player token id' : tokenId,
			'player game channel id' : -1,
			'player name' : name,
			'player id' : -1
		}

	def setChannelId(self, channelId):
		self.data['player game channel id'] = channelId

	def getPlayerName(self):
		return self.data['player name']

	def getPlayerGameChannel(self):
		return self.data['player game channel id']

# game data 관련 함수들
class GameData:

	def __init__(self, gameChannelId):
		# make structure
		self.data = {
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
			self.data['game channel player list'].append({})

			self.data['game channel player list'][i]['player name'] = 'nothing'
			self.data['game channel player list'][i]['player master flag'] = False
			self.data['game channel player list'][i]['player connection flag'] = False
			self.data['game channel player list'][i]['player ready'] = False
			self.data['game channel player list'][i]['character id'] = -1
			self.data['game channel player list'][i]['turn'] = -1
			self.data['game channel player list'][i]['tile number'] = 0
			self.data['game channel player list'][i]['gold number'] = 0
			self.data['game channel player list'][i]['trash number'] = 0
			self.data['game channel player list'][i]['score'] = 0

		# add map data
		for i in range(23):
			self.data['game channel map'].append([])

			for j in range(23):
				self.data['game channel map'][i].append({})

				self.data['game channel map'][i][j]['type'] = 'SENTINEL'
				self.data['game channel map'][i][j]['owner'] = 'NOBODY'
				self.data['game channel map'][i][j]['item'] = 'NOTHING'
				self.data['game channel map'][i][j]['checked flag'] = False
				self.data['game channel map'][i][j]['animation turn'] = 0
				self.data['game channel map'][i][j]['animation flag'] = False
				self.data['game channel map'][i][j]['direction'] = 'UP'

	def setMapSize(self, width, height):
		self.data['game channel void tile'] = width * height
		self.data['game channel map size'][0] = width
		self.data['game channel map size'][1] = height

		# map init code
		for i in range(1, (self.data['game channel map size'][1] + 1) * 2):
			for j in range(1, (self.data['game channel map size'][0] + 1) * 2):
				if i % 2 == 0:
					if j % 2 == 0:
						self.data['game channel map'][i][j]['type'] = 'TILE'
					else:
						self.data['game channel map'][i][j]['type'] = 'LINE_UNCONNECTED'
				else:
					if j % 2 == 0:
						self.data['game channel map'][i][j]['type'] = 'LINE_UNCONNECTED'
					else:
						self.data['game channel map'][i][j]['type'] = 'DOT'

	def addPlayer(self, playerData):
		for idx in range(4):
			if self.data['game channel player list'][idx]['player connection flag'] == False:
				playerData.setChannelId(self.data['game channel id'])
				++self.data['game channel player number']
				
				self.data['game channel player list'][idx]['player name'] = playerData.getPlayerName()
				self.data['game channel player list'][idx]['player connection flag'] = True

				return True

		return False
	
	def selectCharacter(self, playerId, characterId):
		if self.data['game channel player list'][idx]['character id'] == characterId:
			self.data['game channel player list'][idx]['character id'] = -1
		else:
			for idx in range(4):
				if self.data['game channel player list'][idx]['character id'] == characterId:
					return False

			self.data['game channel player list'][idx]['character id'] = characterId

		return True

	def isPossible(self, i, j):
		# 일단 hidden line은 없이 구현
		if self.data['game channel map'][i][j]['type'] == 'LINE_UNCONNECTED':
			voidTileCount = 0

			if self.data['game channel map'][i + 1][j]['owner'] == 'NOBODY':
				++voidTileCount
			if self.data['game channel map'][i - 1][j]['owner'] == 'NOBODY':
				++voidTileCount
			if self.data['game channel map'][i][j + 1]['owner'] == 'NOBODY':
				++voidTileCount
			if self.data['game channel map'][i][j - 1]['owner'] == 'NOBODY':
				++voidTileCount

			if voidTileCount == 4:
				return True
		else:
			return False

	def setAnimationState(self, currentTile, animationTurn, direction):
		self.data['game channel map'][currentTile[0]][currentTile[1]]['animation flag'] = True
		self.data['game channel map'][currentTile[0]][currentTile[1]]['animation turn'] = animationTurn
		self.data['game channel map'][currentTile[0]][currentTile[1]]['direction'] = direction

	# del a[0:len(a)]
	def collectClosedTile(self, i, j, direction):
		searchTile = Queue.Queue()

		currentTile = [0, 0]
		nextTile = [0, 0]

		if direction == 'UP':
			currentTile[0] = i - 1
			currentTile[1] = j
		elif direction == 'RIGHT':
			currentTile[0] = i
			currentTile[1] = j + 1
		elif direction == 'DOWN':
			currentTile[0] = i + 1
			currentTile[1] = j + 1
		elif direction == 'LEFT':
			currentTile[0] = i
			currentTile[1] = j - 1

		if self.data['game channel map'][i][j]['type'] != 'DOT':
			animationTurn = 1;
			setAnimationState(currentTile, animationTurn, direction)

			i = 0

			searchTile.put(currentTile)
			self.closedTile.append(currentTile)
			self.data['game channel map'][currentTile[0]][currentTile[1]]['checked flag'] = True

			while not searchTile.empty():
				currentTile = searchTile.get()

				if self.data['game channel map'][currentTile[0]][currentTile[1]]['type'] != 'SENTINEL':
					# current tile은 sentinel이므로 초기화 작업 안 함 

					# init closed tiles
					for each in closedTile:
						self.data['game channel map'][each[0]][each[1]]['checked flag'] = False
						self.data['game channel map'][each[0]][each[1]]['animation flag'] = False
						self.data['game channel map'][each[0]][each[1]]['animation turn'] = 0
						self.data['game channel map'][each[0]][each[1]]['direction'] = 'UP'

					del self.closedTile[0:len(closedTile)]

					# init checked tiles 
					'''
					while not searchTile.empty():
						tile = searchTile.get()
						self.data['game channel map'][tile[0]][tile[1]]['checked flag'] = False
						self.data['game channel map'][tile[0]][tile[1]]['animation flag'] = False
						self.data['game channel map'][tile[0]][tile[1]]['animation turn'] = 0
						self.data['game channel map'][tile[0]][tile[1]]['direction'] = 'UP'
					'''

					break

				if self.data['game channel map'][currentTile[0] - 1][currentTile[1]]['type'] == 'LINE_UNCONNECTED':
					nextTile[0] = currentTile[0] - 2
					nextTile[1] = currentTile[1]

					if not self.data['game channel map'][nextTile[0]][nextTile[1]]['checked flag']:
						searchTile.put(nextTile)
						self.closedTile.append(nextTile)
						self.data['game channel map'][nextTile[0]][nextTile[1]]['checked flag'] = True

						animationTurn = self.data['game channel map'][currentTile[0]][currentTile[1]]['animation turn']
						setAnimationState(nextTile, animationTurn, 'UP')

				if self.data['game channel map'][currentTile[0]][currentTile[1] + 1]['type'] == 'LINE_UNCONNECTED':
					nextTile[0] = currentTile[0]
					nextTile[1] = currentTile[1] + 2

					if not self.data['game channel map'][nextTile[0]][nextTile[1]]['checked flag']:
						searchTile.put(nextTile)
						self.closedTile.append(nextTile)
						self.data['game channel map'][nextTile[0]][nextTile[1]]['checked flag'] = True

						animationTurn = self.data['game channel map'][currentTile[0]][currentTile[1]]['animation turn']
						setAnimationState(nextTile, animationTurn, 'RIGHT')
				
				if self.data['game channel map'][currentTile[0] + 1][currentTile[1]]['type'] == 'LINE_UNCONNECTED':
					nextTile[0] = currentTile[0] + 2
					nextTile[1] = currentTile[1]

					if not self.data['game channel map'][nextTile[0]][nextTile[1]]['checked flag']:
						searchTile.put(nextTile)
						self.closedTile.append(nextTile)
						self.data['game channel map'][nextTile[0]][nextTile[1]]['checked flag'] = True

						animationTurn = self.data['game channel map'][currentTile[0]][currentTile[1]]['animation turn']
						setAnimationState(nextTile, animationTurn, 'DOWN')
				
				if self.data['game channel map'][currentTile[0]][currentTile[1] - 1]['type'] == 'LINE_UNCONNECTED':
					nextTile[0] = currentTile[0]
					nextTile[1] = currentTile[1] - 2

					if not self.data['game channel map'][nextTile[0]][nextTile[1]]['checked flag']:
						searchTile.put(nextTile)
						self.closedTile.append(nextTile)
						self.data['game channel map'][nextTile[0]][nextTile[1]]['checked flag'] = True

						animationTurn = self.data['game channel map'][currentTile[0]][currentTile[1]]['animation turn']
						setAnimationState(nextTile, animationTurn, 'LEFT')
				
			# setAnimationTurnNumber(animationTurn)

	def isClosed(self, i, j):
		self.collectClosedTile(i, j, 'UP')
		if not self.closedTile == []: # tile list is not empty:
			return True

		self.collectClosedTile(i, j, 'RIGHT')
		if not self.closedTile == []: # tile list is not empty:
			return True

		self.collectClosedTile(i, j, 'DOWN')
		if not self.closedTile == []: # tile list is not empty:
			return True

		self.collectClosedTile(i, j, 'LEFT')
		if not self.closedTile == []: # tile list is not empty:
			return True

		return False

	def drawLine(self, idxI, idxJ):
		if not self.isPossible(idxI, idxJ):
			return False

		self.data['game channel map'][i][j]['type'] == 'LINE_CONNECTED'

		if self.isClosed(idxI, idxJ):
			for each in closedTile:
				self.data['game channel map'][each[0]][each[1]]['owner'] = ++self.data['game channel current turn id']

		return True

	# for debug
	def renderMap(self):
		for i in range(23):
			thisLine = ''
			for j in range(23):
				if self.data['game channel map'][i][j]['type'] == 'DOT':
					thisLine += '*'
				elif self.data['game channel map'][i][j]['type'] == 'LINE_UNCONNECTED':
					if i % 2 == 0:
						thisLine += '|'
					else:
						thisLine += '-'
				elif self.data['game channel map'][i][j]['type'] == 'LINE_CONNECTED':
					thisLine += '#'
				elif self.data['game channel map'][i][j]['type'] == 'TILE':
					thisLine += ' '
			if not thisLine == '':
				print thisLine

		print '>>> current map'

	def getPlayerName(self, idx):
		return self.data['game channel player list'][idx]['player name']

	def getPlayerScore(self, idx):
		return self.data['game channel player list'][idx]['score']

	def getPlayerConnection(self, idx):
		return self.data['game channel player list'][idx]['player connection flag']

if __name__ == '__main__':
	# test : player creation
	player_moon = PlayerData(29, 'prof. moon')
	player_jg = PlayerData(67, 'JUNGGANG')
	player_wooq = PlayerData(80, 'wooq')

    # test : game data creation
	testGameData = GameData(4)

	#insert player to game channel
	result = testGameData.addPlayer(player_moon)

	if result == True:
		result = testGameData.addPlayer(player_jg)

	if result == True:
		result = testGameData.addPlayer(player_wooq)

	for each in range(4):
		if testGameData.getPlayerConnection(each) == True:
			print "name : %s / score : %d" % (testGameData.getPlayerName(each), testGameData.getPlayerScore(each))
	testGameData.setMapSize(6, 5)

	testGameData.renderMap()