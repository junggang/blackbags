# -*- coding: utf-8 -*-

# player data 관련 함수들
class PlayerData:
	
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
				self.data['game channel map'][i][j]['checkedFlag'] = False
				self.data['game channel map'][i][j]['animation turn'] = 0
				self.data['game channel map'][i][j]['direction'] = 'UP'

	def setMapSize(self, width, height):
		self.data['game channel void tile'] = width * height
		self.data['game channel map size'][0] = width
		self.data['game channel map size'][0] = height

		# map init code
		for i in range(1, height * 2 + 2):
			for j in range(1, width * 2 + 2):
				if i % 2 == 0:
					if j % 2 == 0:
						self.data['game channel map'][i][j]['type'] = 'tile'
					else:
						self.data['game channel map'][i][j]['type'] = 'line'
				else:
					if j % 2 == 0:
						self.data['game channel map'][i][j]['type'] = 'line'
					else:
						self.data['game channel map'][i][j]['type'] = 'dot'

	def addPlayer(self, playerData):
		for idx in range(4):
			if self.data['game channel player list'][idx]['player connection flag'] == False:
				playerData.setChannelId(self.data['game channel id'])
				++self.data['game channel player number']
				
				self.data['game channel player list'][idx]['player name'] = playerData.getPlayerName()
				self.data['game channel player list'][idx]['player connection flag'] = True

				return True

		return False
	
	def renderMap(self):
		# for debug
		for i in range(23):
			thisLine = ''
			for j in range(23):
				if self.data['game channel map'][i][j]['type'] == 'dot':
					thisLine += '*'
				elif self.data['game channel map'][i][j]['type'] == 'line':
					if i % 2 == 0:
						thisLine += '|'
					else:
						thisLine += '-'
				elif self.data['game channel map'][i][j]['type'] == 'tile':
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