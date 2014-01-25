#include "HelpScene.h"
#include "BackgroundLayer.h"
#include "HelpTutorialLayer.h"
#include "PlayerNameSettingLayer.h"

USING_NS_CC;

bool CHelpScene::init(void)
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

	CCLayer* HelpTutorialLayer = CHelpTutorialLayer::create();

	this->addChild(HelpTutorialLayer, 1);

	return true;
}