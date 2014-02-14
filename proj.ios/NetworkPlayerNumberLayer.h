#pragma once
#include "cocos2d.h"
#include "config.h"

class CNetworkPlayerNumberLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	void CreateNumberOfPlayerMenu(cocos2d::CCSize visibleSize);
	void CreateNextButtonMenu(cocos2d::CCSize visibleSize);

	void NumberOfPlayerCallBack(cocos2d::CCObject* pSender);
	void NextButtonCallBack(cocos2d::CCObject* pSender);

	virtual void update(float dt);

	bool IsSettingCompleted();

	// implement the "static node()" method manually
	CREATE_FUNC(CNetworkPlayerNumberLayer);

private:
	// Next Button
	cocos2d::CCMenuItemImage *pNextButton;
};
