//
//  DisconnectedLayer.cpp
//  MonsterScramble
//
//  Created by Gyeongwook on 2014. 3. 6..
//
//

#include "DisconnectedLayer.h"
#include "MainScene.h"
#include "config.h"

USING_NS_CC;

bool CDisconnectedLayer::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	/////////////////////////////
	// 2. add a background image
    
	// disconnected message - 나중에 이미지 바꿔
	CCSprite* pTextAnimation = CCSprite::create(CREDIT_MEMBER_IMAGE);
	pTextAnimation->setAnchorPoint(ccp(0, 0) );
	pTextAnimation->setPosition(CCPoint(CREDIT_MEMBER_POSITION) );
	addChild(pTextAnimation, 0);
    
	// mainmenu button part
	CCMenuItemImage *pMainScene = CCMenuItemImage::create(
                                                          SHARED_BTN_BACK.c_str(),
                                                          SHARED_BTN_BACK.c_str(),
                                                          this,
                                                          menu_selector(CDisconnectedLayer::mainSceneCallback)
                                                          );
	pMainScene->setAnchorPoint(ccp(0.0, 0.0) );
	pMainScene->setPosition(CCPoint(CREDIT_BACK_BUTTON_POSITION) );
    
	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pMainScene, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
    
	return true;
}

void CDisconnectedLayer::mainSceneCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	//ºº∆√√¢¿∏∑Œ ∞°æﬂâ“~
	CCScene* newScene = CMainScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
#endif
}