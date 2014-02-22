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
	// 2. add menus
	CCMenuItemImage *pBackToMainButton = CCMenuItemImage::create(
										"image/MAIN_exit.png",
										"image/MAIN_exit_selected.png",
										this,
										menu_selector(CSettingMenuLayer::mainSceneCallback)
										);
    
	CCMenuItemImage *pFacebookLoginButton = CCMenuItemImage::create(
										"image/LOGIN_WITH_FACEBOOK.png",
										"image/LOGIN_WITH_FACEBOOK.png",
										this,
										menu_selector(CSettingMenuLayer::FacebookLoginCallback)
										);

	m_pBGMVolume = extension::CCControlSlider::create("image/BAR_BACKGROUND.png", "image/BAR_PROGRESS.png", "image/BAR_THUMB.png");
	m_pSEVolume = extension::CCControlSlider::create("image/BAR_BACKGROUND.png", "image/BAR_PROGRESS.png", "image/BAR_THUMB.png");

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(NULL, NULL);

	pMenu->addChild(pFacebookLoginButton);

	this->addChild(m_pBGMVolume);
	this->addChild(m_pSEVolume);

	m_pBGMVolume->setPosition( ccp(pMenu->getPositionX(), 100) );
	m_pBGMVolume->setMaximumAllowedValue(100.0);
	m_pSEVolume->setPosition( ccp(pMenu->getPositionX(), 150) );
	m_pSEVolume->setMaximumAllowedValue(100.0);

	pMenu->addChild(pBackToMainButton);

	pMenu->alignItemsVertically();

	this->addChild(pMenu);
    
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

void CSettingMenuLayer::FacebookLoginCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	//Logic

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}