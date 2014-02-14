#include "SettingScene.h"
#include "BackgroundLayer.h"
#include "SettingMenuLayer.h"

USING_NS_CC;

bool CSettingScene::init(void)
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

	CCLayer* SettingMenuLayer = CSettingMenuLayer::create();

	this->addChild(SettingMenuLayer, 1);

	return true;
}
