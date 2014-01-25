#include "ResultScene.h"
#include "BackgroundLayer.h"
#include "ResultScoreLayer.h"
#include "ResultTitleLayer.h"

USING_NS_CC;

bool CResultScene::init(void)
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

	CCLayer* titleLayer = CResultTitleLayer::create();

	this->addChild(titleLayer, 1);

	CCLayer* scoreLayer = CResultScoreLayer::create();

	this->addChild(scoreLayer, 1);

	return true;
}