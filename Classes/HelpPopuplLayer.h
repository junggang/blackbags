#pragma once
#include "cocos2d.h"

/*	게임 플레이 방법과 점수 계산 방법이 나오는 레이어	*/
class CHelpPopupLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent* event);

	// implement the "static node()" method manually
	CREATE_FUNC(CHelpPopupLayer);
};
