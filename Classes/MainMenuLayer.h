#pragma once
#include "cocos2d.h"

class CMainMenuLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	// a selector callback
	void newgameCallback(CCObject* pSender);
	void multiplayCallback(CCObject* pSender);
	void settingCallback(CCObject* pSender);
	void creditCallback(CCObject* pSender);
    void exitCallback(CCObject* pSender);

	// implement the "static node()" method manually
    CREATE_FUNC(CMainMenuLayer);
};

