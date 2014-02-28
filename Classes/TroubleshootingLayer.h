#pragma once
#include "cocos2d.h"

class CTroubleShootingLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	// a selector callback
    void closeCallback(CCObject* pSender);
	void signupCallback(CCObject* pSender);
	void visitCallback(CCObject* pSender);

	// implement the "static node()" method manually
    CREATE_FUNC(CTroubleShootingLayer);
};

