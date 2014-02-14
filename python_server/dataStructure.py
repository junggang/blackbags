# -*- coding: utf-8 -*-
import Queue
import random

# player data index
PD_TOKEN_ID = 0
PD_GAME_CHANNEL_ID = 1
PD_NAME = 2
PD_PLAYER_ID = 3
PD_PLAYER_2 = 4
PD_PLAYER_3 = 5
PD_PLAYER_4 = 6

# game data index
GD_CURRENT_SCENE = 0
GD_CHANNEL_ID = 1
GD_MAP_ID = 2
GD_CURRENT_TURN_IDX = 3
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
GDP_MASTER_FLAG = 1
GDP_CONNECTED_FLAG = 2
GDP_READY = 3
GDP_CHARACTER_ID = 4
GDP_TURN = 5
GDP_TILE_COUNT = 6
GDP_GOLD_COUNT = 7
GDP_TRASH_COUNT = 8
GDP_SCORE = 9
GDP_PLAYER_IDX = 10

# game data - map id
MS_NOT_SELECTED = 0
MS_6X5 = 1
MS_8X7 = 2

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

	# insertData나 initData로 초기화 필요 
	def __init__(self):
		self.data = []

	# 외부에서 player data를 받아서 사용 
	def insertData(self, playerData):
		self.data = playerData

	# 멤버 변수를 기본값으로 초기화된 player data 생성 
	def initData(self, tokenId, name):
		self.data = [
			tokenId, 	# PD_TOKEN_ID
			-1, 		# PD_GAME_CHANNEL_ID
			name, 		# PD_NAME
			-1,			# PD_PLAYER_ID
			0,			# PD_PLAYER_2
			0,			# PD_PLAYER_3
			0 			# PD_PLAYER_4
		]

	# get / set functions
	def setChannelId(self, channelId):
		self.data[PD_TOKEN_ID] = channelId

	def getPlayerName(self):
		return self.data[PD_NAME]

	def getPlayerGameChannel(self):
		return self.data[PD_GAME_CHANNEL_ID]

	def getPlayerId(self):
		return self.data[PD_PLAYER_ID]

	def setPlayerId(self, playerId):
		self.data[PD_PLAYER_ID] = playerId

	# 참여하고 싶은 game channel의 플레이 인원을 get / set
	def setPlayerNumber(self, two, three, four):
		self.data[PD_PLAYER_2] = two
		self.data[PD_PLAYER_3] = three
		self.data[PD_PLAYER_4] = four

	def getPlayerNumber(self, number):
		if number == 2:
			return self.data[PD_PLAYER_2]
		elif number == 3:
			return self.data[PD_PLAYER_3]
		elif number == 4:
			return self.data[PD_PLAYER_4]

# game data 관련 함수들
class GameData:

	# insertData나 initData로 초기화 필요 
	def __init__(self):
		self.closedTile = []
		self.data = []

	# 외부에서 game data를 받아서 사용 
	def insertData(self, gameData):
		self.data = gameData

	# 멤버 변수를 기본값으로 초기화된 game data 생성 
	def initData(self, gameChannelId):
		# make structure
		self.data = [
			SC_SETTING,		# D_CURRENT_SCENE
			gameChannelId,	# GD_CHANNEL_ID
			MS_NOT_SELECTED,# GD_MAP_ID
			-1,				# GD_CURRENT_TURN_IDX
			[],				# GD_TURN_LIST
			False,			# GD_TURN_START_FLAG
			[0, 0],			# GD_RECENTLY_CONNECTED_LINE
			-1,				# GD_VOID_TILE_COUNT
			0,				# GD_PLAYER_NUMBER
			[],				# GD_PLAYER_LIST
			[0, 0],			# GD_MAP_SIZE
			[]				# GD_MAP
		]

		# add players data
		for i in range(4):
			self.data[GD_PLAYER_LIST].append([])

			self.data[GD_PLAYER_LIST][i].append('no_name')	# GDP_NAME
			self.data[GD_PLAYER_LIST][i].append(False)		# GDP_MASTER_FLAG
			self.data[GD_PLAYER_LIST][i].append(False)		# GDP_CONNECTED_FLAG
			self.data[GD_PLAYER_LIST][i].append(False)		# GDP_READY
			self.data[GD_PLAYER_LIST][i].append(-1)			# GDP_CHARACTER_ID
			self.data[GD_PLAYER_LIST][i].append(-1)			# GDP_TURN
			self.data[GD_PLAYER_LIST][i].append(0)			# GDP_TILE_COUNT
			self.data[GD_PLAYER_LIST][i].append(0)			# GDP_GOLD_COUNT
			self.data[GD_PLAYER_LIST][i].append(0)			# GDP_TRASH_COUNT
			self.data[GD_PLAYER_LIST][i].append(0)			# GDP_SCORE
			self.data[GD_PLAYER_LIST][i].append(-1)			# GDP_PLAYER_IDX

	# game data의 현재 scene을 설정 
	def setScene(self, nextScene):
		self.data[GD_CURRENT_SCENE] = nextScene

	# 플레이어가 선택한 맵 종료에 따른 크기 설정 (가로 / 세로)
	def setMapSize(self, mapId):
		if mapId == MS_6X5:
			width = 6
			height = 5
		elif mapId == MS_8X7:
			width = 8
			height = 7

		self.data[GD_MAP_ID] = mapId
		self.data[GD_VOID_TILE_COUNT] = width * height
		self.data[GD_MAP_SIZE][0] = width
		self.data[GD_MAP_SIZE][1] = height

	# 해당 id의 player가 channel master인지 반환 
	def isChannelMaster(self, playerId):
		return self.data[GD_PLAYER_LIST][playerId][GDP_MASTER_FLAG]

	# player 관련 get functions
	def getPlayerName(self, idx):
		return self.data[GD_PLAYER_LIST][idx][GDP_NAME]

	def getPlayerScore(self, idx):
		return self.data[GD_PLAYER_LIST][idx][GDP_SCORE]

	def getPlayerConnection(self, idx):
		return self.data[GD_PLAYER_LIST][idx][GDP_CONNECTED_FLAG]

	# game channel에 player 추가 
	def addPlayer(self, playerData):
		for idx in range(4):
			if self.data[GD_PLAYER_LIST][idx][GDP_CONNECTED_FLAG] == False:
				# 추가되었으므로 player에게 player id와 channel id를 부여 
				playerData.setChannelId(self.data[GD_CHANNEL_ID])
				playerData.setPlayerId(idx)

				# 참여 인원 1명 증가 
				self.data[GD_PLAYER_NUMBER] += 1
				
				# game data내부에 있는 player 정보(name, connection flag, id) 업데이트
				self.data[GD_PLAYER_LIST][idx][GDP_NAME] = playerData.getPlayerName()
				self.data[GD_PLAYER_LIST][idx][GDP_CONNECTED_FLAG] = True
				self.data[GD_PLAYER_LIST][idx][GDP_PLAYER_IDX] = idx

				# 방장 설정 - addPlayer는 최초 방 생성에만 사용하므로 idx값이 0이면 그냥 방장으로 설정
				if idx == 0:
					self.data[GD_PLAYER_LIST][idx][GDP_MASTER_FLAG] = True

				return idx

		return -1
	
	# 각각의 플레이어가 game data의 업데이트된 내용을 수신했음을 확인하는 flag설정 
	# 조심해!! - 둘로 분리하는 것이 나을 듯
	def changeReadyFlag(self, playerId):
		if self.data[GD_PLAYER_LIST][playerId][GDP_READY] == 1:
			self.data[GD_PLAYER_LIST][playerId][GDP_READY] = 0
		else:
			self.data[GD_PLAYER_LIST][playerId][GDP_READY] = 1

	# game data에서 업데이트가 발생하면 ready flag를 초기화해서 다시 수신 확인을 받을 수 있도록 설정 
	def resetReadyFlag(self):
		for each in self.data[GD_TURN_LIST]:
			self.data[GD_PLAYER_LIST][each][GDP_READY] = 0

	# 캐릭터 선택 및 취소에 대한 입력 업데이트 
	def selectCharacter(self, playerId, characterId):
		if self.data[GD_PLAYER_LIST][idx][GDP_CHARACTER_ID] == characterId:
			self.data[GD_PLAYER_LIST][idx][GDP_CHARACTER_ID] = -1
		else:
			for idx in range(4):
				if self.data[GD_PLAYER_LIST][idx][GDP_CHARACTER_ID] == characterId:
					return False

			self.data[GD_PLAYER_LIST][idx][GDP_CHARACTER_ID] = characterId

		return True

	# 현재 game channel에 참여중인 모든 플레이어가 다름 게임 진행을 할 준비가 되었는지 확인 
	def isAllReady(self):
		count = 0

		for each in self.data[GD_PLAYER_LIST]:
			if each[GDP_READY] == 1:
				count += 1

		if count == self.data[GD_PLAYER_NUMBER]:
			return True
		else:
			return False

	# 게임을 시작할 때 플레이어들 순서를 섞어요
	def makeRandomTurn(self):
		for each in self.data[GD_PLAYER_LIST]:
			if each[GDP_CONNECTED_FLAG]:
				self.data[GD_TURN_LIST].append(each[GDP_PLAYER_IDX])

		random.shuffle(self.data[GD_TURN_LIST])

	# 게임을 시작할 때 맵을 생성 
	# 조심해!! - 현재 울타리와 아이템 배치 코드 없음 
	def makeRandomMap(self):
		# generate map data
		for i in range(self.data[GD_MAP_SIZE][1] * 2 + 3):
			self.data[GD_MAP].append([])

			for j in range(self.data[GD_MAP_SIZE][0] * 2 + 3):
				self.data[GD_MAP][i].append([])

				self.data[GD_MAP][i][j].append(MO_SENTINEL)		# GDM_TYPE
				self.data[GD_MAP][i][j].append(OWNER_NOBODY)	# GDM_OWNER
				self.data[GD_MAP][i][j].append(ITEM_NOTHING)	# GDM_ITEM
				self.data[GD_MAP][i][j].append(False)			# GDM_CHECKED_FLAG
				self.data[GD_MAP][i][j].append(0)				# GDM_ANIMATION_TURN
				self.data[GD_MAP][i][j].append(DI_UP)			# GDM_DIRECTION

		# map init code
		for i in range(1, self.data[GD_MAP_SIZE][1] * 2 + 2):
			for j in range(1, self.data[GD_MAP_SIZE][0] * 2 + 2):
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

		# set random object's count
		if self.data[GD_MAP_SIZE][1] == 5:
			startLineNumber = 13;
			startGoldNumber = 5;
			startTrashNumber = 4;
		elif self.data[GD_MAP_SIZE][1] == 7:
			startLineNumber = 27;
			startGoldNumber = 8;
			startTrashNumber = 7;

		# generate random objects
		while startLineNumber > 0:
			randomPosition = self.makeRandomLine()

			# 일단 선을 긋자
			self.data[GD_MAP][randomPosition[0]][randomPosition[1]][GDM_TYPE] = MO_LINE_CONNECTED

			if self.isClosed(randomPosition[0], randomPosition[1]):
				# 확인하는 동안 닫힌 도형으로 판정된 타일들을 초기화한다.
				for each in self.closedTile:
					self.data[GD_MAP][each[0]][each[1]][GDM_DIRECTION] = DI_UP
					self.data[GD_MAP][each[0]][each[1]][GDM_CHECKED_FLAG] = False
					self.data[GD_MAP][each[0]][each[1]][GDM_ANIMATION_TURN] = 0

				# closedTile은 비운다
				del self.closedTile[0:len(self.closedTile)]

				# 방금 그었던 선을 지운다
				self.data[GD_MAP][randomPosition[0]][randomPosition[1]][GDM_TYPE] = MO_LINE_UNCONNECTED
			else:
				# 안 닫혔으니까 랜덤 라인 수 하나 감소 시키자
				startLineNumber -= 1

		# 아이템 배치
		for each in range(startGoldNumber):
			 self.setRandomItem(ITEM_GOLD)

		for each in range(startTrashNumber):
			self.setRandomItem(ITEM_TRASH)

	# 게임을 시작합니다
	def startGame(self):
		self.setScene(SC_PLAY)
		self.makeRandomTurn()

		self.data[GD_CURRENT_TURN_IDX] = 0
		self.resetReadyFlag()

	# play scene에서 새로운 턴을 시작 
	def startTurn(self):
		self.resetReadyFlag()

		if not self.isEnd():
			pass
			# 타이머 시작

	# 지금 선을 그을 차례인 플레이어의 idx값 반환 
	def getCurrentTurnId(self):
		return self.data[GD_TURN_LIST][self.data[GD_CURRENT_TURN_IDX]]

	# 게임 종료?
	def isEnd(self):
		return self.data[GD_VOID_TILE_COUNT]  == 0

	# 그 자리에 선 그을 수 있어?
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

	# 해당 타일에 애니메이션 상태 설정 
	def setAnimationState(self, currentTile, animationTurn, direction):
		self.data[GD_MAP][currentTile[0]][currentTile[1]][GDM_ANIMATION_TURN] = animationTurn
		self.data[GD_MAP][currentTile[0]][currentTile[1]][GDM_DIRECTION] = direction

	# 닫힌 도형을 모아서 gaem data의 closedTile에 담는다 
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

		# 만약 sentinel을 만나면 열린 도형이므로 종료 
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

					# init tiles in closedTile
					for each in self.closedTile:
						self.data[GD_MAP][each[0]][each[1]][GDM_CHECKED_FLAG] = False
						self.data[GD_MAP][each[0]][each[1]][GDM_ANIMATION_TURN] = 0
						self.data[GD_MAP][each[0]][each[1]][GDM_DIRECTION] = DI_UP

					# closedTile 비우기 
					del self.closedTile[0:len(self.closedTile)]

					# searchTile은 closedTile과 중복되므로 초기화 안 함
					break

				# 현재 타일이 sentinel이 아니면 주위 네 방향의 선의 연결 상태를 확인하고
				# 그 너머에 있는 타일의 체크 여부를 확인해서 closedTile과 searchTile에 추가 
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

	# 이 선 그으면 닫히나?
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

	# 선 그리고 턴은 다음 턴으로 넘긴다.
	def drawLine(self, idxI, idxJ):
		if not self.isPossible(idxI, idxJ):
			return False

		self.data[GD_RECENTLY_CONNECTED_LINE][0] = idxI
		self.data[GD_RECENTLY_CONNECTED_LINE][1] = idxJ

		self.data[GD_MAP][idxI][idxJ][GDM_TYPE] = MO_LINE_CONNECTED

		if self.isClosed(idxI, idxJ):
			for each in self.closedTile:
				self.data[GD_MAP][each[0]][each[1]][GDM_OWNER] = self.data[GD_TURN_LIST][self.data[GD_CURRENT_TURN_IDX]]

			# 닫혀진 타일들 상태 업데이트 완료 했으니 closedTile은 비운다
			del self.closedTile[0:len(self.closedTile)]

		# 종료여부 확인해서 결과 계산을 하거나 턴을 넘긴다
		if self.isEnd():
			self.updateResult()
		else:
			self.data[GD_CURRENT_TURN_IDX] += 1
			self.data[GD_CURRENT_TURN_IDX] %= self.data[GD_PLAYER_NUMBER]

		return True

	# 그을 수 있는 임의선을 선택
	def makeRandomLine(self):
		while True:
			randomIdxI = random.randint(1, self.data[GD_MAP_SIZE][1]) * 2 + 1

			if randomIdxI % 2 == 0:
				randomIdxJ = random.randint(0, self.data[GD_MAP_SIZE][0]) * 2 + 1
			else:
				randomIdxJ = random.randint(0, self.data[GD_MAP_SIZE][0]) * 2

			print 'random line'
			print randomIdxI
			print randomIdxJ

			if self.isPossible(randomIdxI, randomIdxJ):
				return [randomIdxI, randomIdxJ]

	# 지정한 아이템을 임의의 타일 위치에 배치
	def setRandomItem(self, item):
		while True:
			randomIdxI = random.randint(1, self.data[GD_MAP_SIZE][0]) * 2
			randomIdxJ = random.randint(1, self.data[GD_MAP_SIZE][1]) * 2

			if self.data[GD_MAP][randomIdxI][randomIdxJ][GDM_TYPE] == MO_TILE and self.data[GD_MAP][randomIdxI][randomIdxJ][GDM_ITEM] == ITEM_NOTHING:
				self.data[GD_MAP][randomIdxI][randomIdxJ][GDM_ITEM] = item
				return

	# 결과 계산
	def updateResult():
		self.setScene(SC_RESULT)

		for each in self.data[GD_PLAYER_LIST]:
			each[GDP_SCORE] = each[GDP_TILE_COUNT] * 2 + each[GDP_GOLD_COUNT] * 5 - each[GDP_TRASH_COUNT] * 10

	# for debug
	# console에 현재 맵 상황 표시
	def renderMap(self):
		for i in range(self.data[GD_MAP_SIZE][1] * 2 + 3):
			thisLine = ''
			for j in range(self.data[GD_MAP_SIZE][0] * 2 + 3):
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
						if self.data[GD_MAP][i][j][GDM_ITEM] == ITEM_NOTHING:
							thisLine += ' '
						elif self.data[GD_MAP][i][j][GDM_ITEM] == ITEM_TRASH:
							thisLine += 'T'
						elif self.data[GD_MAP][i][j][GDM_ITEM] == ITEM_GOLD:
							thisLine += 'G'
					else:
						thisLine += str(self.data[GD_MAP][i][j][GDM_OWNER])
						

			if not thisLine == '':
				print thisLine

		print '>>> current map'


if __name__ == '__main__':
	# test : player creation
	player_moon = PlayerData()
	player_moon.initData(29, 'prof. moon')
	player_jg = PlayerData()
	player_jg.initData(67, 'JUNGGANG')
	player_wooq = PlayerData()
	player_wooq.initData(80, 'wooq')

    # test : game data creation
	testGameData = GameData()
	testGameData.initData(4)

	#insert player to game channel
	result = testGameData.addPlayer(player_moon)

	if result != -1:
		result = testGameData.addPlayer(player_jg)

	if result != -1:
		result = testGameData.addPlayer(player_wooq)

	for each in range(4):
		if testGameData.getPlayerConnection(each):
			print "name : %s / score : %d" % (testGameData.getPlayerName(each), testGameData.getPlayerScore(each))
	testGameData.setMapSize(MS_8X7)

	testGameData.makeRandomTurn()
	testGameData.makeRandomMap()

	testGameData.renderMap()

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