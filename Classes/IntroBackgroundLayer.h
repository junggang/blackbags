#pragma once
#include "cocos2d.h"

class CIntroBackgroundLayer : public cocos2d::CCLayerColor
{
public:
	virtual bool init();

	// implement the "static node()" method manually
	CREATE_FUNC(CIntroBackgroundLayer);
};

