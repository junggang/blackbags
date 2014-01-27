#include "HomeMenuLayer.h"

USING_NS_CC;

bool CHomeMenuLayer::init()
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
	float tempYPos = 0.0;
	CCMenu* pMenu = nullptr;

	CCMenuItemImage *pHomeIcon = CCMenuItemImage::create(
		"image/icon_menu.png",
		"image/icon_menu_selected.png",
		this,
		menu_selector(CHomeMenuLayer::homeMenuCallback)
		);


	pHomeIcon->setPosition(ccp(origin.x + visibleSize.width/2, visibleSize.height-50.0f) );

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pHomeIcon, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	return true;
}

void CHomeMenuLayer::homeMenuCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	//home menu popup


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}
