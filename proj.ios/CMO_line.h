#pragma once
#include "cocos2d.h"
#include "config.h"


class CMO_line : public cocos2d::CCSprite
{
	/*
public:
	CMO_line();
	~CMO_line();

protected:
	//static CMO_line* create(const char* pszFileName, const cocos2d::CCRect& rect);
	*/
public:
	//static CMO_line* Create();
	virtual bool init();
	virtual void update(float delta);

	void setImage(IndexedPosition indexedPosition);
	void setLineDirection(Direction lineDirection);

	CREATE_FUNC(CMO_line);

private:
	void setAnchorPoint();
	void changeImage();

	IndexedPosition		m_Index;
	cocos2d::CCSprite*	pLine;
	bool				m_Connected;
	int					m_ImageFileIdx;
	Direction			m_LineDirection;
};


