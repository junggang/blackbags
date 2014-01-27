#pragma once
#include "cocos2d.h"

class CHomeMenuLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	// a selector callback
	void homeMenuCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(CHomeMenuLayer);
};

