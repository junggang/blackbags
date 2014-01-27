#include "IntroScene.h"
#include "BackgroundLayer.h"

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
	CCLayer* BackgroundLayer = CBackgroundLayer::create();

	this->addChild(BackgroundLayer, 0);

	return true;
}