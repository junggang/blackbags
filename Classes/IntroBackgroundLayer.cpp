#include "IntroBackgroundLayer.h"
#include "config.h"

USING_NS_CC;

bool CIntroBackgroundLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayerColor::initWithColor( ccc4(INTRO_BACKGROUND_COLOR)) )
	{
		return false;
	}

	/////////////////////////////
	// 2. add a background image

	

	return true;
}