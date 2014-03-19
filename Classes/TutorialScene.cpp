#include "TutorialScene.h"
#include "BackgroundLayer.h"
#include "GameManager.h"
USING_NS_CC;

bool CTutorialScene::init(void)
{
	//////////////////////////////
    // 1. super init first
	if ( !CCScene::init() )
    {
        return false;
    }
    
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCLayer* BackgroundLayer = CBackgroundLayer::create();
    
	this->addChild(BackgroundLayer, 0);
    
    
    return true;
}

void CTutorialScene::update(float dt)
{
    
}

void CTutorialScene::SettingSceneCallback(CCObject* pSender)
{
    
}
