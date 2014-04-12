#include "ResultScene.h"
#include "BackgroundLayer.h"
#include "ResultScoreLayer.h"
#include "ResultTitleLayer.h"
#include "ResultButtonLayer.h"
#include "AudioManager.h"
#include "AdMobObjectCPP.h"

USING_NS_CC;

bool CResultScene::init(void)
{
	//////////////////////////////
    // 1. super init first
	if ( !CCScene::init() )
    {
        return false;
    }

    // 광고 켜기
    gene::AdMobObjectCPP * admob = new gene::AdMobObjectCPP();
    admob->showAdMob();
    
	/////////////////////////////
    // 2. add layers
	CCLayer* BackgroundLayer = CBackgroundLayer::create();
	this->addChild(BackgroundLayer, 0);

	CCLayer* titleLayer = CResultTitleLayer::create();
	this->addChild(titleLayer, 1);

	CCLayer* scoreLayer = CResultScoreLayer::create();
	this->addChild(scoreLayer, 2);

	CCLayer* buttonLayer = CResultButtonLayer::create();
	this->addChild(buttonLayer, 3);

    
    // play music "BGM_RESULT" made by C.Carmack
    CAudioManager::GetInstance()->StopBGM();
    
	CAudioManager::GetInstance()->ChangeMusic(BGM_RESULT);
	CAudioManager::GetInstance()->PlayBGM();
    
	return true;
}