#include "IntroScene.h"
#include "BackgroundLayer.h"
#include "MainScene.h"
#include "IntroLayer.h"
#include "IntroBackgroundLayer.h"

USING_NS_CC;

bool CIntroScene::init(void)
{
	//////////////////////////////
    // 1. super init first
	if ( !CCScene::init() )
    {
        return false;
    }

	/////////////////////////////
    // 2. add layers
	//CCLayer* BackgroundLayer = CBackgroundLayer::create();
	CCLayer* BackgroundLayer = CIntroBackgroundLayer::create();
	this->addChild(BackgroundLayer, 0);

	CCLayer* LogoLayer = CIntroLayer::create();
	this->addChild(LogoLayer, 1);

	return true;
}

