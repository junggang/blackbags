#include "HomeMenuLayer.h"
#include "MainScene.h"
#include "config.h"
#include "HelpScene.h"
#include "GameSettingScene.h"
#include "HomeMenuPopUp.h"

USING_NS_CC;

bool CHomeMenuLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	/////////////////////////////
	// 2. add a background image
	CCMenu* pMenu = nullptr;

	CCMenuItemImage *pMenuIcon = CCMenuItemImage::create(
		SHARED_BTN_HOME.c_str(),
		SHARED_BTN_HOME.c_str(),
		this,
		menu_selector(CHomeMenuLayer::homeMenuCallback)
		);

	pMenuIcon->setPosition(CCPoint(SHARED_BTN_HOME_POS) );

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pMenuIcon, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
	return true;
}

void CHomeMenuLayer::homeMenuCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->pause();
	CCLayer* popUp = CHomeMenuPopUp::create();
	addChild(popUp,1);
}