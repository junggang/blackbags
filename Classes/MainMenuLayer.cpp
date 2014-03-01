#include "MainMenuLayer.h"
#include "SettingScene.h"
#include "CreditScene.h"
#include "GameManager.h"
#include "GameSettingScene.h"
//for test
#include "NetworkLogic.h"

USING_NS_CC;

bool CMainMenuLayer::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a background image
	float tempYPos = 0.0;
	CCMenu* pMenu = nullptr;

	CCMenuItemImage *pOnTable = CCMenuItemImage::create(
										SHARED_MENU1_UNSELECTED.c_str(),
										SHARED_MENU1_SELECTED.c_str(),
										this,
										menu_selector(CMainMenuLayer::newgameCallback)
										);
    
	CCSprite* pMenuImg01 = CCSprite::create(MAIN_MENU1_IMG.c_str());
	pMenuImg01->setPosition(CCPoint(MAIN_MENU1_IMG_POS));
	pMenuImg01->setAnchorPoint(ccp(0,0));
	addChild(pMenuImg01,2);

	pOnTable->setAnchorPoint(ccp(0,0));
	pOnTable->setPosition(CCPoint(MAIN_MENU1_POS) );

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pOnTable, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	CCMenuItemImage *pOnLine = CCMenuItemImage::create(
										SHARED_MENU2_UNSELECTED.c_str(),
										SHARED_MENU2_SELECTED.c_str(),
										this,
										menu_selector(CMainMenuLayer::multiplayCallback)
										);
    
	CCSprite* pMenuImg02 = CCSprite::create(MAIN_MENU2_IMG.c_str());
	pMenuImg02->setPosition(CCPoint(MAIN_MENU2_IMG_POS));
	pMenuImg02->setAnchorPoint(ccp(0,0));
	addChild(pMenuImg02,2);

	pOnLine->setAnchorPoint(ccp(0,0));
	pOnLine->setPosition(CCPoint(MAIN_MENU2_POS));

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pOnLine, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	CCMenuItemImage *pSetting = CCMenuItemImage::create(
										SHARED_MENU3_UNSELECTED.c_str(),
										SHARED_MENU3_SELECTED.c_str(),
										this,
										menu_selector(CMainMenuLayer::settingCallback)
										);

	CCSprite* pMenuImg03 = CCSprite::create(MAIN_MENU3_IMG.c_str());
	pMenuImg03->setPosition(CCPoint(MAIN_MENU3_IMG_POS));
	pMenuImg03->setAnchorPoint(ccp(0,0));
	addChild(pMenuImg03,2);

	pSetting->setAnchorPoint(ccp(0,0));
	pSetting->setPosition(CCPoint(MAIN_MENU3_POS));

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pSetting, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	//create menu title
	CCSprite* pMenuTitle = CCSprite::create(MAIN_MENU_TITLE.c_str());
	pMenuTitle->setPosition(CCPoint(MAIN_MENU_TITLE_POS));
	pMenuTitle->setAnchorPoint(ccp(0,0));
	addChild(pMenuTitle,3);
    
	return true;
}

void CMainMenuLayer::newgameCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	//newgame load
	CCScene* newScene = CGameSettingScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
#endif
}

void CMainMenuLayer::multiplayCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CGameManager::GetInstance()->SetOnlineMode(true);
	CGameManager::GetInstance()->InitNetworkLogic();

	CNetworkLogic::GetInstance()->Authetication();

    CCScene* newScene = CGameSettingScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
#endif
}

void CMainMenuLayer::settingCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	//for test
	CCScene* newScene = CSettingScene::create();
	CCDirector::sharedDirector()->pushScene( newScene );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
#endif
}