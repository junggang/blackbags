#pragma once
#include "cocos2d.h"

class CGameEndLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	void gameEndCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(CGameEndLayer);
};

