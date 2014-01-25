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
	//���ӵ����Ϳ��� ������ m_map�� m_Type�� �޾ƿͼ� ������Ʈ�� �����Ѵ�.
	//targetRow : Line�� vertical����, horizontal���� Ȯ���ϴ� ����.
	static CMapObject* Create(MO_TYPE type,int targetRow);

	int GetMapType();
	void SetMapType(MO_TYPE type);

private:
	MO_TYPE m_type;
};

#endif

