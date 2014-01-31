# -*- coding: utf-8 -*-
import Queue

# player data index
PD_TOKEN_ID = 0
PD_GAME_CHANNEL_ID = 1
PD_NAME = 2
PD_PLAYER_ID = 3

# game data index
GD_CURRENT_SCENE = 0
GD_CHANNEL_ID = 1
GD_MAP_ID = 2
GD_CURRENT_TURN_ID = 3
GD_TURN_LIST = 4
GD_TURN_START_FLAG = 5
GD_RECENTLY_CONNECTED_LINE = 6
GD_VOID_TILE_COUNT = 7
GD_PLAYER_NUMBER = 8
GD_PLAYER_LIST = 9
GD_MAP_SIZE = 10
GD_MAP = 11

# scene name index
SC_OPENING = 0
SC_MAIN = 1
SC_GAME_SETTING = 2
SC_PLAY = 3
SC_RESULT = 4
SC_CREDIT = 5
SC_SETTING = 6
SC_TUTORIAL = 7
SC_NOSCENE = 8

# game data - player data index
GDP_NAME = 0
GDP_MASKTER_FLAG = 1
GDP_CONNECTED_FLAG = 2
GDP_READY = 3
GDP_CHARACTER_ID = 4
GDP_TURN = 5
GDP_TILE_COUNT = 6
GDP_GOLD_COUNT = 7
GDP_TRASH_COUNT = 8
GDP_SCORE = 9

# map data index
GDM_TYPE = 0
GDM_OWNER = 1
GDM_ITEM = 2
GDM_CHECKED_FLAG = 3
GDM_ANIMATION_TURN = 4
GDM_DIRECTION = 5

# map type index
MO_SENTINEL = 0
MO_DOT = 10
MO_LINE_UNCONNECTED = 20
MO_LINE_CONNECTED = 21
MO_LINE_HIDDEN = 22
MO_TILE = 30

# map owner index
OWNER_NOBODY = -1
OWNER_PLAYER_0 = 0
OWNER_PLAYER_1 = 1
OWNER_PLAYER_2 = 2
OWNER_PLAYER_3 = 3

# map item index
ITEM_NOTHING = 0
ITEM_GOLD = 1
ITEM_TRASH = 2

# direction index
DI_UP = 0
DI_RIGHT = 1
DI_DOWN = 2
DI_LEFT = 3

# player data 관련 함수들
class PlayerData:

	def __init__(self, tokenId, name):
		self.data = [
			tokenId, 
			-1, 
			name, 
			-1
		]

	def setChannelId(self, channelId):
		self.data[PD_TOKEN_ID] = channelId

	def getPlayerName(self):
		return self.data[PD_NAME]

	def getPlayerGameChannel(self):
		return self.data[PD_PLAYER_ID]

# game data 관련 함수들
class GameData:
	closedTile = []

	def __init__(self, gameChannelId):
		# make structure
		self.data = [
			SC_NOSCENE,
			gameChannelId,
			-1,
			-1,
			[],
			False,
			[0, 0],
			-1,
			0,
			[],
			[0, 0],
			[]
		]

		# add players data
		for i in range(4):
			self.data[GD_PLAYER_LIST].append([])

			self.data[GD_PLAYER_LIST][i].append('no_name')
			self.data[GD_PLAYER_LIST][i].append(False)
			self.data[GD_PLAYER_LIST][i].append(False)
			self.data[GD_PLAYER_LIST][i].append(False)
			self.data[GD_PLAYER_LIST][i].append(-1)
			self.data[GD_PLAYER_LIST][i].append(-1)
			self.data[GD_PLAYER_LIST][i].append(0)
			self.data[GD_PLAYER_LIST][i].append(0)
			self.data[GD_PLAYER_LIST][i].append(0)
			self.data[GD_PLAYER_LIST][i].append(0)

		# add map data
		for i in range(23):
			self.data[GD_MAP].append([])

			for j in range(23):
				self.data[GD_MAP][i].append([])

				self.data[GD_MAP][i][j].append(MO_SENTINEL)
				self.data[GD_MAP][i][j].append(OWNER_NOBODY)
				self.data[GD_MAP][i][j].append(ITEM_NOTHING)
				self.data[GD_MAP][i][j].append(False)
				self.data[GD_MAP][i][j].append(0)
				self.data[GD_MAP][i][j].append(DI_UP)

	def setMapSize(self, width, height):
		self.data[GD_VOID_TILE_COUNT] = width * height
		self.data[GD_MAP_SIZE][0] = width
		self.data[GD_MAP_SIZE][1] = height

		# map init code
		for i in range(1, (self.data[GD_MAP_SIZE][1] + 1) * 2):
			for j in range(1, (self.data[GD_MAP_SIZE][0] + 1) * 2):
				if i % 2 == 0:
					if j % 2 == 0:
						self.data[GD_MAP][i][j][GDM_TYPE] = MO_TILE
					else:
						self.data[GD_MAP][i][j][GDM_TYPE] = MO_LINE_UNCONNECTED
				else:
					if j % 2 == 0:
						self.data[GD_MAP][i][j][GDM_TYPE] = MO_LINE_UNCONNECTED
					else:
						self.data[GD_MAP][i][j][GDM_TYPE] = MO_DOT

	def addPlayer(self, playerData):
		for idx in range(4):
			if self.data[GD_PLAYER_LIST][idx][GDP_CONNECTED_FLAG] == False:
				playerData.setChannelId(self.data[GD_CHANNEL_ID])
				self.data[GD_PLAYER_NUMBER] += 1
				
				self.data[GD_PLAYER_LIST][idx][GDP_NAME] = playerData.getPlayerName()
				self.data[GD_PLAYER_LIST][idx][GDP_CONNECTED_FLAG] = True

				return True

		return False
	
	def selectCharacter(self, playerId, characterId):
		if self.data[GD_PLAYER_LIST][idx][GDP_CHARACTER_ID] == characterId:
			self.data[GD_PLAYER_LIST][idx][GDP_CHARACTER_ID] = -1
		else:
			for idx in range(4):
				if self.data[GD_PLAYER_LIST][idx][GDP_CHARACTER_ID] == characterId:
					return False

			self.data[GD_PLAYER_LIST][idx][GDP_CHARACTER_ID] = characterId

		return True

	def isEnd(self):
		return self.data[GD_VOID_TILE_COUNT]  == 0

	def isPossible(self, i, j):
		# 일단 hidden line은 없이 구현
		if self.data[GD_MAP][i][j][GDM_TYPE] == MO_LINE_UNCONNECTED:
			voidTileCount = 0

			if self.data[GD_MAP][i + 1][j][GDM_OWNER] == OWNER_NOBODY:
				voidTileCount += 1

			if self.data[GD_MAP][i - 1][j][GDM_OWNER] == OWNER_NOBODY:
				voidTileCount += 1
			
			if self.data[GD_MAP][i][j + 1][GDM_OWNER] == OWNER_NOBODY:
				voidTileCount += 1

			if self.data[GD_MAP][i][j - 1][GDM_OWNER] == OWNER_NOBODY:
				voidTileCount += 1

			if voidTileCount == 4:
				return True
		else:
			return False

	def setAnimationState(self, currentTile, animationTurn, direction):
		self.data[GD_MAP][currentTile[0]][currentTile[1]][GDM_ANIMATION_TURN] = animationTurn
		self.data[GD_MAP][currentTile[0]][currentTile[1]][GDM_DIRECTION] = direction

	# del a[0:len(a)]
	def collectClosedTile(self, i, j, direction):
		searchTile = Queue.Queue()

		currentTile = [i, j]

		if direction == DI_UP:
			currentTile[0] -= 1
		elif direction == DI_RIGHT:
			currentTile[1] += 1
		elif direction == DI_DOWN:
			currentTile[0] += 1
		elif direction == DI_LEFT:
			currentTile[1] -= 1

		if self.data[GD_MAP][currentTile[0]][currentTile[1]][GDM_TYPE] == MO_TILE:
			animationTurn = 1;
			self.setAnimationState(currentTile, animationTurn, direction)

			searchTile.put(currentTile)
			self.closedTile.append(currentTile)
			self.data[GD_MAP][currentTile[0]][currentTile[1]][GDM_CHECKED_FLAG] = True

			while not searchTile.empty():
				currentTile = searchTile.get()

				if self.data[GD_MAP][currentTile[0]][currentTile[1]][GDM_TYPE] == MO_SENTINEL:
					# current tile은 sentinel이므로 초기화 작업 안 함 

					# init closed tiles
					for each in self.closedTile:
						self.data[GD_MAP][each[0]][each[1]][GDM_CHECKED_FLAG] = False
						self.data[GD_MAP][each[0]][each[1]][GDM_ANIMATION_TURN] = 0
						self.data[GD_MAP][each[0]][each[1]][GDM_DIRECTION] = DI_UP

					del self.closedTile[0:len(self.closedTile)]

					print self.closedTile
					# init checked tiles 
					'''
					while not searchTile.empty():
						tile = searchTile.get()
						self.data['game channel map'][tile[0]][tile[1]]['checked flag'] = False
						self.data['game channel map'][tile[0]][tile[1]]['animation turn'] = 0
						self.data['game channel map'][tile[0]][tile[1]]['direction'] = 'UP'
					'''
					break

				if self.data[GD_MAP][currentTile[0] - 1][currentTile[1]][GDM_TYPE] == MO_LINE_UNCONNECTED:
					nextTile = [0, 0]
					nextTile[0] = currentTile[0] - 2
					nextTile[1] = currentTile[1]

					if not self.data[GD_MAP][nextTile[0]][nextTile[1]][GDM_CHECKED_FLAG]:
						searchTile.put(nextTile)
						self.closedTile.append(nextTile)
						self.data[GD_MAP][nextTile[0]][nextTile[1]][GDM_CHECKED_FLAG] = True

						animationTurn = self.data[GD_MAP][currentTile[0]][currentTile[1]][GDM_ANIMATION_TURN] + 1
						self.setAnimationState(nextTile, animationTurn, DI_UP)

				if self.data[GD_MAP][currentTile[0]][currentTile[1] + 1][GDM_TYPE] == MO_LINE_UNCONNECTED:
					nextTile = [0, 0]
					nextTile[0] = currentTile[0]
					nextTile[1] = currentTile[1] + 2

					if not self.data[GD_MAP][nextTile[0]][nextTile[1]][GDM_CHECKED_FLAG]:
						searchTile.put(nextTile)
						self.closedTile.append(nextTile)
						self.data[GD_MAP][nextTile[0]][nextTile[1]][GDM_CHECKED_FLAG] = True

						animationTurn = self.data[GD_MAP][currentTile[0]][currentTile[1]][GDM_ANIMATION_TURN] + 1
						self.setAnimationState(nextTile, animationTurn, DI_RIGHT)

				if self.data[GD_MAP][currentTile[0] + 1][currentTile[1]][GDM_TYPE] == MO_LINE_UNCONNECTED:
					nextTile = [0, 0]
					nextTile[0] = currentTile[0] + 2
					nextTile[1] = currentTile[1]

					if not self.data[GD_MAP][nextTile[0]][nextTile[1]][GDM_CHECKED_FLAG]:
						searchTile.put(nextTile)
						self.closedTile.append(nextTile)
						self.data[GD_MAP][nextTile[0]][nextTile[1]][GDM_CHECKED_FLAG] = True

						animationTurn = self.data[GD_MAP][currentTile[0]][currentTile[1]][GDM_ANIMATION_TURN] + 1
						self.setAnimationState(nextTile, animationTurn, DI_DOWN)

				if self.data[GD_MAP][currentTile[0]][currentTile[1] - 1][GDM_TYPE] == MO_LINE_UNCONNECTED:
					nextTile = [0, 0]
					nextTile[0] = currentTile[0]
					nextTile[1] = currentTile[1] - 2

					if not self.data[GD_MAP][nextTile[0]][nextTile[1]][GDM_CHECKED_FLAG]:
						searchTile.put(nextTile)
						self.closedTile.append(nextTile)
						self.data[GD_MAP][nextTile[0]][nextTile[1]][GDM_CHECKED_FLAG] = True

						animationTurn = self.data[GD_MAP][currentTile[0]][currentTile[1]][GDM_ANIMATION_TURN] + 1
						self.setAnimationState(nextTile, animationTurn, DI_LEFT)

			# setAnimationTurnNumber(animationTurn)

	def isClosed(self, i, j):
		self.collectClosedTile(i, j, DI_UP)
		if not self.closedTile == []: # tile list is not empty:
			return True

		self.collectClosedTile(i, j, DI_RIGHT)
		if not self.closedTile == []: # tile list is not empty:
			return True

		self.collectClosedTile(i, j, DI_DOWN)
		if not self.closedTile == []: # tile list is not empty:
			return True

		self.collectClosedTile(i, j, DI_LEFT)
		if not self.closedTile == []: # tile list is not empty:
			return True

		return False

	def drawLine(self, idxI, idxJ):
		if not self.isPossible(idxI, idxJ):
			return False

		self.data[GD_MAP][idxI][idxJ][GDM_TYPE] = MO_LINE_CONNECTED

		if self.isClosed(idxI, idxJ):
			for each in self.closedTile:
				self.data[GD_MAP][each[0]][each[1]][GDM_OWNER] = self.data[GD_CURRENT_TURN_ID]

		self.data[GD_CURRENT_TURN_ID] += 1

		return True

	# for debug
	def renderMap(self):
		# tempMapType

		for i in range(23):
			thisLine = ''
			for j in range(23):
				tempMapType = self.data[GD_MAP][i][j][GDM_TYPE]

				if tempMapType == MO_DOT:
					thisLine += '*'

				elif tempMapType == MO_LINE_UNCONNECTED:
					if i % 2 == 0:
						thisLine += '|'
					else:
						thisLine += '-'

				elif tempMapType == MO_LINE_CONNECTED:
					thisLine += '#'

				elif tempMapType == MO_TILE:
					if self.data[GD_MAP][i][j][GDM_OWNER] == OWNER_NOBODY:
						thisLine += ' '
					else:
						thisLine += str(self.data[GD_MAP][i][j][GDM_OWNER])

			if not thisLine == '':
				print thisLine

		print '>>> current map'

	def getPlayerName(self, idx):
		return self.data[GD_PLAYER_LIST][idx][GDP_NAME]

	def getPlayerScore(self, idx):
		return self.data[GD_PLAYER_LIST][idx][GDP_SCORE]

	def getPlayerConnection(self, idx):
		return self.data[GD_PLAYER_LIST][idx][GDP_CONNECTED_FLAG]

if __name__ == '__main__':
	# test : player creation
	player_moon = PlayerData(29, 'prof. moon')
	player_jg = PlayerData(67, 'JUNGGANG')
	player_wooq = PlayerData(80, 'wooq')

    # test : game data creation
	testGameData = GameData(4)

	#insert player to game channel
	result = testGameData.addPlayer(player_moon)

	if result:
		result = testGameData.addPlayer(player_jg)

	if result:
		result = testGameData.addPlayer(player_wooq)

	for each in range(4):
		if testGameData.getPlayerConnection(each):
			print "name : %s / score : %d" % (testGameData.getPlayerName(each), testGameData.getPlayerScore(each))
	testGameData.setMapSize(6, 5)

	testGameData.renderMap()
	print testGameData.data

	while not testGameData.isEnd():
		userInput = raw_input('input : ')
		tempInput = userInput.split()

		indexedPosition = []

		for each in tempInput:
			indexedPosition.append(int(each))

		if testGameData.drawLine(indexedPosition[0], indexedPosition[1]):
			print 'succes'
		else:
			print 'fail'
		testGameData.renderMap()