#pragma once
#include "cocos2d.h"
#include "config.h"

class CPlayerNumberAndMapSizeLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	
	void CreateTitle();
	void CreateNumberOfPlayerMenu(cocos2d::CCSize visibleSize);
	void CreateNextButtonMenu(cocos2d::CCSize visibleSize);
	void CreateBackButtonMenu(cocos2d::CCSize visibleSize);

	void NumberOfPlayerCallBack(cocos2d::CCObject* pSender);
	void NextButtonCallBack(cocos2d::CCObject* pSender);
	void MainSceneCallback(cocos2d::CCObject* pSender);


	virtual void update(float dt);

	bool IsSettingCompleted();

	// implement the "static node()" method manually
    CREATE_FUNC(CPlayerNumberAndMapSizeLayer);
	
private:
	// Next Button
	cocos2d::CCMenuItemImage *pNextButton;
};
