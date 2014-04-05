#include "BackgroundAnimation.h"
#include "config.h"

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
	
	
	return true;
}