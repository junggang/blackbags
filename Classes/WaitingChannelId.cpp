#include "WaitingChannelId.h"
#include "MainScene.h"
#include "config.h"
#include "GameManager.h"

USING_NS_CC;

bool CWaitingChannelId::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	/////////////////////////////
	// 2. add a background image
	// monster part
	CCSprite* pMonster = CCSprite::create(WAITING_CHANNEL_MONSTER_IMAGE);
	pMonster->setAnchorPoint(ccp(0, 0) );
	pMonster->setPosition(CCPoint(WAITING_CHANNEL_MONSTER_POSITION) );
	addChild(pMonster, 0);

	// magnifier part
	CCSprite* pMagnifier = CCSprite::create(WAITING_CHANNEL_MAGNIFIER_IMAGE);
	pMagnifier->setAnchorPoint(ccp(0, 0) );
	pMagnifier->setPosition(CCPoint(WAITING_CHANNEL_MAGNIFIER_POSITION) );
	addChild(pMagnifier, 1);

	// searching animation
	CCSprite* pTextAnimation = CCSprite::create(WAITING_CHANNEL_TEXT_IMAGE);
	pTextAnimation->setAnchorPoint(ccp(0, 0) );
	pTextAnimation->setPosition(CCPoint(WAITING_CHANNEL_TEXT_POSITION) );
	addChild(pTextAnimation, 2);

	// mainmenu button part
	CCMenuItemImage *pMainScene = CCMenuItemImage::create(
										SHARED_BTN_BACK.c_str(),
										SHARED_BTN_BACK.c_str(),
										this,
										menu_selector(CWaitingChannelId::mainSceneCallback)
										);
	pMainScene->setAnchorPoint(ccp(0.0, 0.0) );
	pMainScene->setPosition(CCPoint(WAITING_CHANNEL_BACK_BUTTON_POSITION) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pMainScene, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	return true;
}

void CWaitingChannelId::mainSceneCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CGameManager::GetInstance()->Logout();
    
	CCScene* newScene = CMainScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
#endif
}