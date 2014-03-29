#include "MainTitleLayer.h"
#include "config.h"

USING_NS_CC;

bool CMainTitleLayer::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	/////////////////////////////
    // 2. add a background image
	CCSprite* pTitle = CCSprite::create(MAIN_TITLE.c_str());
	pTitle->setAnchorPoint(ccp(0,0));
	pTitle->setPosition(CCPoint(MAIN_TITLE_POS));
    this->addChild(pTitle, 0);
    
    return true;
}

