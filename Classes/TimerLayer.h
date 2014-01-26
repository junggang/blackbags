#pragma once
#include "cocos2d.h"

class CTimerLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	virtual void update(float dt);

	// implement the "static node()" method manually
	CREATE_FUNC(CTimerLayer);

private:
	cocos2d::CCSize m_VisibleSize;
	cocos2d::CCProgressTimer* m_progressTimeBar;
};

