#include "BackgroundAnimation.h"

USING_NS_CC;

bool CBackgroundAnimation::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	/////////////////////////////
	// 2. add a background image
	
	CCSprite* pMovingMonster1 = CCSprite::create("image/MAIN_movingMonster1.png");

	this->addChild(pMovingMonster1);

	pMovingMonster1->setPosition(ccp(-100.0f,visibleSize.height*0.25));
	ccBezierConfig bezier1;
	bezier1.controlPoint_1 = ccp(200.0f,visibleSize.height*0.4);
	bezier1.controlPoint_2 = ccp(visibleSize.width-200.0f,visibleSize.height*0.6);
	bezier1.endPosition = ccp(visibleSize.width+100.0f,visibleSize.height*0.4);

	CCActionInterval*  bezierby1 = CCBezierBy::create(2.0f,bezier1);

	CCAction* repeatAction1 = CCRepeatForever::create(bezierby1);

	pMovingMonster1->runAction(repeatAction1);

	return true;
}