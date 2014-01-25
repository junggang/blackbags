#include "MainScene.h"
#include "BackgroundLayer.h"
#include "MainTitleLayer.h"
#include "MainMenuLayer.h"
#include "GameManager.h"

USING_NS_CC;

bool CMainScene::init(void)
{
	//////////////////////////////
    // 1. super init first
	if ( !CCScene::init() )
    {
        return false;
    }

	/////////////////////////////
    // 2. add layers
	CCLayer* BackgroundLayer = CBackgroundLayer::create();

	this->addChild(BackgroundLayer, 0);

	CCLayer* titleLayer = CMainTitleLayer::create();

	this->addChild(titleLayer, 1);

	CCLayer* mainMenuLayer = CMainMenuLayer::create();

	this->addChild(mainMenuLayer, 1);

	CGameManager::GetInstance()->init();

	return true;
}