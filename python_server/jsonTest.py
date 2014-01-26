import json
import redis

global gRedis
gameData = {'player number':4, 'name list':['Hi', 'Hello', 'world', 'cake'], 'map size':[6,5]}

def connect_redis():
	return redis.StrictRedis(host='localhost', port=6379, db=0)

if __name__ == '__main__':
	gRedis = connect_redis()

	print gameData
	print gameData['name list'][1]

	jsonData = json.dumps(gameData)
	gRedis.set('channel id 0', jsonData)

	#print gRedis.get('channel id 0')
	result = json.loads(gRedis.get('channel id 0'))

	print result['name list'][1]