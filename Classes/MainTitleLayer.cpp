#include "MainTitleLayer.h"

USING_NS_CC;

bool CMainTitleLayer::init()
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
	CCSprite* pTitle = CCSprite::create("image/MAIN_title1.png");

	pTitle->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + pTitle->getContentSize().height/2) );
    this->addChild(pTitle, 0);
    
    return true;
}

