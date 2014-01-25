#pragma once
#include "cocos2d.h"

class CBackgroundLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	// implement the "static node()" method manually
    CREATE_FUNC(CBackgroundLayer);
};

