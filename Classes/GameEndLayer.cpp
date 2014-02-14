#include "GameEndLayer.h"
#include "ResultScene.h"

USING_NS_CC;

bool CGameEndLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCMenuItemImage *pEndButton = CCMenuItemImage::create(
										"image/NAMESETTING_next.png",
										"image/NAMESETTING_next_selected.png",
										this,
										menu_selector(CGameEndLayer::gameEndCallback)
										);
    
	pEndButton->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pEndButton, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
}

void CGameEndLayer::gameEndCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCScene* newScene = CResultScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}