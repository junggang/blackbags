#pragma once
#include "cocos2d.h"

/*	���� �÷��� ����� ���� ��� ����� ������ ���̾�	*/
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
