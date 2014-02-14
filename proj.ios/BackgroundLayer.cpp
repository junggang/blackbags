#include "BackgroundLayer.h"

USING_NS_CC;

bool CBackgroundLayer::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
    // 2. add a background image
	CCSprite* pBackground = CCSprite::create("image/background.png");

	pBackground->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(pBackground, 0);
    
    return true;
}