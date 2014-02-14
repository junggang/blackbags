#pragma once
#include "cocos2d.h"

class CHelpWindowLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	// implement the "static node()" method manually
	CREATE_FUNC(CHelpWindowLayer);
};

