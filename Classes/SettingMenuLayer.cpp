#include "SettingMenuLayer.h"
#include "MainScene.h"

USING_NS_CC;

bool CSettingMenuLayer::init()
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
	CCMenuItemImage *pMain = CCMenuItemImage::create(
										"image/MAIN_exit.png",
										"image/MAIN_exit_selected.png",
										this,
										menu_selector(CSettingMenuLayer::mainSceneCallback)
										);
    
	pMain->setPosition(ccp(visibleSize.width/2, visibleSize.height/2) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pMain, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
    
	return true;
}

void CSettingMenuLayer::mainSceneCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->popScene();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
#endif
}
