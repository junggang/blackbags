#include "IntroScene.h"
#include "MainScene.h"
#include "IntroLayer.h"
#include "IntroBackgroundLayer.h"
#include "AdMobObjectCPP.h"

USING_NS_CC;

bool CIntroScene::init(void)
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
	//CCLayer* BackgroundLayer = CBackgroundLayer::create();
	CCLayer* BackgroundLayer = CIntroBackgroundLayer::create();
	this->addChild(BackgroundLayer, 0);

	CCLayer* LogoLayer = CIntroLayer::create();
	this->addChild(LogoLayer, 1);
	
	float delayTime = 1.5;
	// æÛ∏∂ »ƒø° ¿¸º€«œ¥¬ ƒ⁄µÂ ª¿‘!
	CCCallFunc* readyRequestCallback = CCCallFunc::create(this, callfunc_selector(CIntroScene::endIntro) );
	CCDelayTime* delayAction = CCDelayTime::create(delayTime);
	this->runAction(CCSequence::create(delayAction, readyRequestCallback, NULL));
	
	return true;
}

void CIntroScene::endIntro()
{
	CCScene* newScene = CMainScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
}
