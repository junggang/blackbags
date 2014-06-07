#include "MainMenuLayer.h"
#include "SettingScene.h"
#include "CreditScene.h"
#include "GameManager.h"
#include "GameSettingScene.h"
#include "LoginScene.h"
//for test
#include "NetworkLogic.h"
#include "config.h"
#include <array>

USING_NS_CC;

bool CMainMenuLayer::init()
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

	CCMenuItemImage *pOnTable = CCMenuItemImage::create(
										SHARED_MENU1_UNSELECTED.c_str(),
										SHARED_MENU1_SELECTED.c_str(),
										this,
										menu_selector(CMainMenuLayer::newgameCallback)
										);
    
	CCSprite* pMenuImg01 = CCSprite::create(MAIN_MENU1_IMG.c_str());
	pMenuImg01->setPosition(CCPoint(MAIN_MENU1_IMG_POS));
	pMenuImg01->setAnchorPoint(ccp(0,0));
	addChild(pMenuImg01,3);

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
	addChild(pMenuImg02,3);

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
	addChild(pMenuImg03,3);

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
    
    drawAnimation();
    
    
    return true;
}

void CMainMenuLayer::newgameCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
   //newgame load
    CGameManager::GetInstance()->SetOnlineMode(false);
    
	CCScene* newScene = CGameSettingScene::create();
	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5, newScene) );
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
    CGameManager::GetInstance()->SetConnectionStatus(true);

    CCScene* newScene = CLoginScene::create();
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
    CCScene* newScene = CSettingScene::create();
	CCDirector::sharedDirector()->pushScene( newScene );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
#endif
}

void CMainMenuLayer::drawAnimation()
{
    
    CCSpriteBatchNode* spritebatch = CCSpriteBatchNode::create(MAIN_MENU1_ANI.c_str());
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile(MAIN_MENU1_ANI_PLIST.c_str());
    
    
    CCArray* animFrames1 = CCArray::createWithCapacity(40);
    
    char str[100] = {0};
    
    for(int i = 1; i < 41; i++)
    {
        sprintf(str, "manin_menu1_000%02d.png", i);
        
        CCSpriteFrame* frame = cache->spriteFrameByName( str );
        animFrames1->addObject(frame);
    }
    
    CCSprite*pElement1 = CCSprite::createWithSpriteFrameName("manin_menu1_00001.png");
    pElement1->setAnchorPoint(ccp(0,0));
    
    spritebatch->addChild(pElement1);
    addChild(spritebatch,2);
    spritebatch->setTag(0);
    
    CCAnimation* animation1 = CCAnimation::createWithSpriteFrames(animFrames1,0.05f);
    CCRepeatForever* repeatAction1 = CCRepeatForever::create(CCAnimate::create(animation1));
    pElement1->runAction(repeatAction1);
    pElement1->setPosition(CCPoint(MAIN_MENU1_IMG_POS));
     
    
    //menu2
    spritebatch = CCSpriteBatchNode::create(MAIN_MENU2_ANI.c_str());
    //cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile(MAIN_MENU2_ANI_PLIST.c_str());
    
    
    CCArray* animFrames2 = CCArray::createWithCapacity(4);
    
    for(int i = 0; i < 4; i++)
    {
        sprintf(str, "main_img2_ani%d.PNG", i);
        
        CCSpriteFrame* frame = cache->spriteFrameByName( str );
        animFrames2->addObject(frame);
    }
    
    CCSprite*pElement2 = CCSprite::createWithSpriteFrameName("main_img2_ani0.PNG");
    pElement2->setAnchorPoint(ccp(0,0));
    
    spritebatch->addChild(pElement2);
    addChild(spritebatch,4);
    spritebatch->setTag(0);
    
    CCAnimation* animation2 = CCAnimation::createWithSpriteFrames(animFrames2,0.1f);
    CCRepeatForever* repeatAction2 = CCRepeatForever::create(CCAnimate::create(animation2));
    pElement2->runAction(repeatAction2);
    pElement2->setPosition(CCPoint(MAIN_MENU2_IMG_POS));
    
    //menu3
    spritebatch = CCSpriteBatchNode::create(MAIN_MENU3_ANI.c_str());
    //cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile(MAIN_MENU3_ANI_PLIST.c_str());
    
    
    CCArray* animFrames3 = CCArray::createWithCapacity(4);
    
    for(int i = 0; i < 4; i++)
    {
        sprintf(str, "main_img3_ani%d.PNG", i);
        
        CCSpriteFrame* frame = cache->spriteFrameByName( str );
        animFrames3->addObject(frame);
    }
    
    CCSprite*pElement3 = CCSprite::createWithSpriteFrameName("main_img3_ani0.PNG");
    pElement3->setAnchorPoint(ccp(0,0));
    
    spritebatch->addChild(pElement3);
    addChild(spritebatch,4);
    spritebatch->setTag(0);
    
    CCAnimation* animation3 = CCAnimation::createWithSpriteFrames(animFrames3,0.1f);
    CCRepeatForever* repeatAction3 = CCRepeatForever::create(CCAnimate::create(animation3));
    pElement3->runAction(repeatAction3);
    pElement3->setPosition(CCPoint(MAIN_MENU3_IMG_POS));

}