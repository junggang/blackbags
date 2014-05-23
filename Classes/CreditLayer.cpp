#include "CreditLayer.h"
#include "MainScene.h"
#include "config.h"

USING_NS_CC;

bool CCreditLayer::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	/////////////////////////////
	// 2. add a background image
	// title part
	CCSprite* pTitle = CCSprite::create(CREDIT_TITLE_IMAGE);
	pTitle->setAnchorPoint(ccp(0, 0) );
	pTitle->setPosition(CCPoint(CREDIT_TITLE_POSITION) );
	addChild(pTitle, 1);

	// searching animation
	CCSprite* pTextAnimation = CCSprite::create(CREDIT_MEMBER_IMAGE);
	pTextAnimation->setAnchorPoint(ccp(0, 0) );
	pTextAnimation->setPosition(CCPoint(CREDIT_MEMBER_POSITION) );
	addChild(pTextAnimation, 0);

	// mainmenu button part
	CCMenuItemImage *pMainScene = CCMenuItemImage::create(
										SHARED_BTN_BACK.c_str(),
										SHARED_BTN_BACK.c_str(),
										this,
										menu_selector(CCreditLayer::SettingSceneCallback)
										);
	pMainScene->setAnchorPoint(ccp(0.0, 0.0) );
	pMainScene->setPosition(CCPoint(CREDIT_BACK_BUTTON_POSITION) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pMainScene, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
    
	return true;
}

void CCreditLayer::SettingSceneCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}