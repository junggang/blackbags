#include "MainMenuLayer.h"

//for test
#include "ResultScene.h"
#include "GameSettingScene.h"

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

	CCMenuItemImage *pNewgame = CCMenuItemImage::create(
										"image/MAIN_newgame.png",
										"image/MAIN_newgame_selected.png",
										this,
										menu_selector(CMainMenuLayer::newgameCallback)
										);
    
	tempYPos = visibleSize.height/2 - pNewgame->getContentSize().height/2;

	pNewgame->setPosition(ccp(origin.x + visibleSize.width/2, tempYPos) );

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pNewgame, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	CCMenuItemImage *pMultiplay = CCMenuItemImage::create(
										"image/MAIN_multiplay.png",
										"image/MAIN_multiplay_selected.png",
										this,
										menu_selector(CMainMenuLayer::multiplayCallback)
										);
    
	tempYPos -= pMultiplay->getContentSize().height;

	pMultiplay->setPosition(ccp(origin.x + visibleSize.width/2, tempYPos) );

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pMultiplay, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	CCMenuItemImage *pCredit = CCMenuItemImage::create(
										"image/MAIN_credit.png",
										"image/MAIN_credit_selected.png",
										this,
										menu_selector(CMainMenuLayer::creditCallback)
										);
    
	tempYPos -= pCredit->getContentSize().height;

	pCredit->setPosition(ccp(origin.x + visibleSize.width/2, tempYPos) );

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pCredit, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	CCMenuItemImage *pExit = CCMenuItemImage::create(
										"image/MAIN_exit.png",
										"image/MAIN_exit_selected.png",
										this,
										menu_selector(CMainMenuLayer::exitCallback)
										);
    
	tempYPos -= pExit->getContentSize().height;

	pExit->setPosition(ccp(origin.x + visibleSize.width/2, tempYPos) );

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pExit, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
    
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
    exit(0);
#endif
#endif
}

void CMainMenuLayer::multiplayCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end(); //multiplay load
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void CMainMenuLayer::creditCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	//for test
	CCScene* newScene = CResultScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void CMainMenuLayer::exitCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}