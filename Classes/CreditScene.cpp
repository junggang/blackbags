#include "CreditScene.h"
#include "BackgroundLayer.h"
#include "CreditLayer.h"
#include "AdMobObjectCPP.h"

USING_NS_CC;

bool CCreditScene::init(void)
{
	//////////////////////////////
    // 1. super init first
	if ( !CCScene::init() )
    {
        return false;
    }

    // 광고 끄기
    gene::AdMobObjectCPP * admob = new gene::AdMobObjectCPP();
    admob->hideAdMob();
    
	/////////////////////////////
    // 2. add layers
	CCLayer* BackgroundLayer = CBackgroundLayer::create();
	this->addChild(BackgroundLayer, 0);

	CCLayer* CreditLayer = CCreditLayer::create();
	this->addChild(CreditLayer, 1);

	return true;
}