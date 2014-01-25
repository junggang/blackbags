#pragma once
#include "cocos2d.h"

/*	게임 플레이 방법과 점수 계산 방법이 나오는 레이어	*/
class CHelpTutorialLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	// implement the "static node()" method manually
	CREATE_FUNC(CHelpTutorialLayer);
};

