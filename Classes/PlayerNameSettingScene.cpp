#include "PlayerNameSettingScene.h"
#include "BackgroundLayer.h"

USING_NS_CC;

bool CPlayerNameSettingScene::init(void)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCScene::init() )
	{
		return false;
	}

	/////////////////////////////
	// 2. add layers

	// background layer
	CCLayer* BackgroundLayer = CBackgroundLayer::create();
	this->addChild(BackgroundLayer, 0);

	// title layer
	CCLayer* PlayerNameSettingLayer = CPlayerNameSettingLayer::create();
	this->addChild(PlayerNameSettingLayer, 1);

	return true;
}