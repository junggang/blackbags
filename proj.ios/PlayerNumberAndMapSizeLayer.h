#pragma once
#include "cocos2d.h"
#include "config.h"

class CPlayerNumberAndMapSizeLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	void CreateMapSelectMenu(cocos2d::CCSize visibleSize);
	void CreateNumberOfPlayerMenu(cocos2d::CCSize visibleSize);
	void CreateNextButtonMenu(cocos2d::CCSize visibleSize);

	void SelectMapCallBack(cocos2d::CCObject* pSender);
	void NumberOfPlayerCallBack(cocos2d::CCObject* pSender);
	void NextButtonCallBack(cocos2d::CCObject* pSender);

	virtual void update(float dt);

	bool IsSettingCompleted();

	// implement the "static node()" method manually
    CREATE_FUNC(CPlayerNumberAndMapSizeLayer);

private:
	// Check Image
	cocos2d::CCSprite*		pCheck;
	
	// Map Select
	cocos2d::CCMenuItemImage *pMapSelect1;
	cocos2d::CCMenuItemImage *pMapSelect2;

	// Next Button
	cocos2d::CCMenuItemImage *pNextButton;
};
