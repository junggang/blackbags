#ifndef MonsterScramble_MapObject
#define MonsterScramble_MapObject

#pragma once
#include "cocos2d.h"
#include "config.h"


class CMO_item : public cocos2d::CCSprite
{
public:
	CMO_item();
	~CMO_item();

protected:
	static CMO_item* create(const char* pszFileName, const cocos2d::CCRect& rect);

public:
	static CMO_item* Create(IndexedPosition indexedPosition);
	void update(float delta);


private:

};

#endif

