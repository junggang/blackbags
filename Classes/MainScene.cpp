#include "MainScene.h"
#include "BackgroundLayer.h"
#include "MainTitleLayer.h"
#include "MainMenuLayer.h"
#include "GameManager.h"
#include "BackgroundAnimation.h"

USING_NS_CC;

bool CMainScene::init(void)
{
	//////////////////////////////
    // 1. super init first
	if ( !CCScene::init() )
    {
        return false;
    }
    
    CGameManager::GetInstance()->init();

	/////////////////////////////
    // 2. add layers
	CCLayer* BackgroundLayer = CBackgroundLayer::create();

	this->addChild(BackgroundLayer, 0);

	CCLayer* BackgroundAnimation = CBackgroundAnimation::create();
	
	this->addChild(BackgroundAnimation,1);

	CCLayer* titleLayer = CMainTitleLayer::create();

	this->addChild(titleLayer, 2);

	CCLayer* mainMenuLayer = CMainMenuLayer::create();

	this->addChild(mainMenuLayer, 2);

	CGameManager::GetInstance()->init();

	return true;
}