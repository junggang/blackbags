#pragma once
#include "cocos2d.h"

class CResultScoreLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	// a selector callback
	void mainSceneCallback(CCObject* pSender);

	// implement the "static node()" method manually
    CREATE_FUNC(CResultScoreLayer);
};

