#include "MainScene.h"
#include "BackgroundLayer.h"
#include "MainTitleLayer.h"
#include "MainMenuLayer.h"
#include "GameManager.h"
#include "BackgroundAnimation.h"
#include "AudioManager.h"
#include "AdMobObjectCPP.h"

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
    
    // 광고 켜기
    gene::AdMobObjectCPP * admob = new gene::AdMobObjectCPP();
    admob->showAdMob();
    
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

    /////////////////////////////
	// 4. play music
    CAudioManager::GetInstance()->StopBGM();
    
	CAudioManager::GetInstance()->ChangeMusic(BGM_MAIN);
	CAudioManager::GetInstance()->PlayBGM();

	return true;
}