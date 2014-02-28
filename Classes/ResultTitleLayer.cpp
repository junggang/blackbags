#include "ResultTitleLayer.h"
#include "MainScene.h"
#include "config.h"

USING_NS_CC;

bool CResultTitleLayer::init()
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
	// 2. add a background image *** 일단 레이아웃은 임의로 잡습니다 ***
	//title part
    CCSprite* pTitle = CCSprite::create(RESULT_TITLE.c_str() );
	pTitle->setAnchorPoint(ccp(0.5, 0.5) );
	pTitle->setPosition(CCPoint(RESULT_TITLE_POSITION) );
	this->addChild(pTitle, 0);
 
	return true;
}