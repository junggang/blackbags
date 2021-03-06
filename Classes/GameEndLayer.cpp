#include "GameEndLayer.h"
#include "ResultScene.h"
#include "config.h"

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
    
    CCMenuItemImage* pEndButton = CCMenuItemImage::create(
                                                  PLAYSCENE_GAMEOVER.c_str(),
                                                  PLAYSCENE_GAMEOVER.c_str(),
                                                  this,
                                                  menu_selector(CGameEndLayer::gameEndCallback)
                                                  );
    
	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pEndButton, NULL);
	pMenu->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(pMenu, 1);
    
    CCSprite *pEndText = CCSprite::create(PLAYSCENE_GAMEOVER_TITLE.c_str());
    pEndText->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
    pEndText->setAnchorPoint(ccp(0.5f,0.5f));
    this->addChild(pEndText,2);
    
    /*
	CCMenuItemImage *pEndButton = CCMenuItemImage::create(
                                        PLAYSCENE_GAMEOVER_TITLE.c_str(),
                                        PLAYSCENE_GAMEOVER_TITLE.c_str(),
										this,
										menu_selector(CGameEndLayer::gameEndCallback)
										);
    
	pEndButton->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pEndButton, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 2);
    */
    
    return true;
}

void CGameEndLayer::gameEndCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCScene* newScene = CResultScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
#endif
}