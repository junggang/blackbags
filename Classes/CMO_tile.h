#pragma once
#include "cocos2d.h"
#include "config.h"
#include "CMO_item.h"

class CMO_tile : public cocos2d::CCSprite
{
	/*
public:
	CMO_tile();
	~CMO_tile();

protected:
	static CMO_tile* create(const char* pszFileName, const cocos2d::CCRect& rect);
	*/
public:
	virtual bool init();
	virtual void update(float delta);

	void setImage(IndexedPosition indexedPosition);
	
	CREATE_FUNC(CMO_tile);

private:
	void changeImage();
	IndexedPosition		m_Index;
	cocos2d::CCSprite*	pTile;
	MO_OWNER			m_Owner;
};

