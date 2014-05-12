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
    
    CCSpriteBatchNode* spritebatch = CCSpriteBatchNode::create(WAITING_CHANNEL_MAGNIFIER_IMAGE.c_str());
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile(WAITING_CHANNEL_MAGNIFIER_IMAGE_PLIST.c_str());
    
    
    CCArray* animFrames1 = CCArray::createWithCapacity(32);
    
    char str[100] = {0};
    
    for(int i = 1; i < 33; i++)
    {
        sprintf(str, "searching_eye_ani_000%02d.png", i);
        
        CCSpriteFrame* frame = cache->spriteFrameByName( str );
        animFrames1->addObject(frame);
    }
    
    CCSprite*pElement1 = CCSprite::createWithSpriteFrameName("searching_eye_ani_00001.png");
    pElement1->setAnchorPoint(ccp(0,0));
    
    spritebatch->addChild(pElement1);
    addChild(spritebatch,1);
    spritebatch->setTag(0);
    
    CCAnimation* animation1 = CCAnimation::createWithSpriteFrames(animFrames1,0.05f);
    CCRepeatForever* repeatAction1 = CCRepeatForever::create(CCAnimate::create(animation1));
    pElement1->runAction(repeatAction1);
    pElement1->setPosition(CCPoint(WAITING_CHANNEL_MAGNIFIER_POSITION));
    // searching animation
    spritebatch = CCSpriteBatchNode::create(WAITING_CHANNEL_TEXT_IMAGE.c_str());
    //cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile(WAITING_CHANNEL_TEXT_IMAGE_PLIST.c_str());
    
    
    CCArray* animFrames2 = CCArray::createWithCapacity(4);
    
    for(int i = 1; i < 5; i++)
    {
        sprintf(str, "searching_text0%d.png", i);
        
        CCSpriteFrame* frame = cache->spriteFrameByName( str );
        animFrames2->addObject(frame);
    }
    
    CCSprite*pElement2 = CCSprite::createWithSpriteFrameName("searching_text01.png");
    pElement2->setAnchorPoint(ccp(0,0));
    
    spritebatch->addChild(pElement2);
    addChild(spritebatch,4);
    spritebatch->setTag(0);
    
    CCAnimation* animation2 = CCAnimation::createWithSpriteFrames(animFrames2,0.1f);
    CCRepeatForever* repeatAction2 = CCRepeatForever::create(CCAnimate::create(animation2));
    pElement2->runAction(repeatAction2);
    pElement2->setPosition(CCPoint(WAITING_CHANNEL_TEXT_POSITION));


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