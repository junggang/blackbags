#ifndef MonsterScramble_MapObject
#define MonsterScramble_MapObject

#pragma once
#include "cocos2d.h"
#include "config.h"


class CMapObject : public cocos2d::CCSprite
{
public:
	CMapObject();
	~CMapObject();

protected:
	static CMapObject* create(const char* pszFileName, const cocos2d::CCRect& rect);

public:
	//게임데이터에서 가져온 m_map의 m_Type를 받아와서 오브젝트를 생성한다.
	//targetRow : Line이 vertical인지, horizontal인지 확인하는 인자.
	static CMapObject* Create(MO_TYPE type,int targetRow);

	int GetMapType();
	void SetMapType(MO_TYPE type);

private:
	MO_TYPE m_type;
};

#endif

