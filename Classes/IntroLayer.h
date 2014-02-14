#pragma once
#include "cocos2d.h"

class CIntroLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	void endIntro(float dt);

	// implement the "static node()" method manually
    CREATE_FUNC(CIntroLayer);
};

