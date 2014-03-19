#include "TroubleShootingLayer.h"
#include "MainScene.h"
#include "config.h"

USING_NS_CC;

bool CTroubleShootingLayer::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    

	/////////////////////////////
	// 2. add a background image
	// background part
	CCSprite* pBackground = CCSprite::create(TROUBLESHOOTING_BACKGROUND_IMAGE);
	pBackground->setAnchorPoint(ccp(0, 0) );
	pBackground->setPosition(CCPoint(TROUBLESHOOTING_BACKGROUND_POS) );
	addChild(pBackground, 0);

	// signup button
	CCMenuItemImage *pSignup = CCMenuItemImage::create(
										TROUBLESHOOTING_SIGNUP_IMAGE,
										TROUBLESHOOTING_SIGNUP_IMAGE,
										this,
										menu_selector(CTroubleShootingLayer::closeCallback)
										);
	pSignup->setAnchorPoint(ccp(0.0, 0.0) );
	pSignup->setPosition(CCPoint(TROUBLESHOOTING_SIGNUP_POS) );

	CCMenu* pMenuSignup = CCMenu::create(pSignup, NULL);
	pMenuSignup->setPosition(CCPointZero);
	this->addChild(pMenuSignup, 1);

	// visit button
	CCMenuItemImage *pVisit = CCMenuItemImage::create(
										TROUBLESHOOTING_VISIT_IMAGE,
										TROUBLESHOOTING_VISIT_IMAGE,
										this,
										menu_selector(CTroubleShootingLayer::closeCallback)
										);
	pVisit->setAnchorPoint(ccp(0.0, 0.0) );
	pVisit->setPosition(CCPoint(TROUBLESHOOTING_VISIT_POS) );

	CCMenu* pMenuVisit = CCMenu::create(pVisit, NULL);
	pMenuVisit->setPosition(CCPointZero);
	this->addChild(pMenuVisit, 1);

	// close button
	CCMenuItemImage *pClose = CCMenuItemImage::create(
										TROUBLESHOOTING_CLOSE_IMAGE,
										TROUBLESHOOTING_CLOSE_IMAGE,
										this,
										menu_selector(CTroubleShootingLayer::closeCallback)
										);
	pClose->setAnchorPoint(ccp(0.0, 0.0) );
	pClose->setPosition(CCPoint(TROUBLESHOOTING_CLOSE_POS) );
	
	CCMenu* pMenuClose = CCMenu::create(pClose, NULL);
	pMenuClose->setPosition(CCPointZero);
	this->addChild(pMenuClose, 1);
    
	return true;
}

void CTroubleShootingLayer::signupCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// TODO something
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
#endif
}

void CTroubleShootingLayer::visitCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// TODO something
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
#endif
}

void CTroubleShootingLayer::closeCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// TODO something
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
#endif
}