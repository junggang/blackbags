#include "HomeMenuLayer.h"
#include "MainScene.h"
#include "config.h"

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

	CCMenuItemImage *pMenuIcon = CCMenuItemImage::create(
		SHARED_BTN_HOME.c_str(),
		SHARED_BTN_HOME.c_str(),
		this,
		menu_selector(CHomeMenuLayer::homeMenuCallback)
		);

	pMenuIcon->setPosition(CCPoint(SHARED_BTN_HOME_POS) );

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pMenuIcon, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	m_backLayer = CCSprite::create(SHARED_POPUP_BG.c_str());
	m_backLayer->setVisible(false);
	m_backLayer->setAnchorPoint(ccp(0,0));
	m_backLayer->setPosition(CCPoint(SHARED_POPUP_BG_POS));
	this->addChild(m_backLayer,2);

	float centerX = m_backLayer->getContentSize().width/2;
	float bottomMargin = SHARED_POPUP_BOTTOM_MARGIN;

	CCSprite* pTitle = CCSprite::create(SHARED_POPUP_TITLE.c_str());
	pTitle->setPosition(ccp(centerX,SHARED_POPUP_TITLE_POS));
	m_backLayer->addChild(pTitle);


	// 팝업 창 아이콘들

	CCMenuItemImage *pQuitIcon = CCMenuItemImage::create(
		SHARED_POPUP_QUIT.c_str(),
		SHARED_POPUP_QUIT.c_str(),
		this,
		menu_selector(CHomeMenuLayer::ResumeIconCallback)
		);
	m_iconQuit = CCMenu::create(pQuitIcon,NULL);
	m_iconQuit->setPosition(ccp(centerX,bottomMargin));

	bottomMargin += SHARED_POPUP_MENU_MARGIN;

	CCMenuItemImage *pSetting = CCMenuItemImage::create(
		SHARED_POPUP_SETTING.c_str(),
		SHARED_POPUP_SETTING.c_str(),
		this,
		menu_selector(CHomeMenuLayer::ResumeIconCallback)
		);
	m_iconSetting = CCMenu::create(pSetting,NULL);
	m_iconSetting->setPosition(ccp(centerX,bottomMargin));

	bottomMargin += SHARED_POPUP_MENU_MARGIN;

	CCMenuItemImage *pHelpIcon = CCMenuItemImage::create(
		SHARED_POPUP_HELP.c_str(),
		SHARED_POPUP_HELP.c_str(),
		this,
		menu_selector(CHomeMenuLayer::HelpIconCallback)
		);
	m_iconHelp = CCMenu::create(pHelpIcon,NULL);
	m_iconHelp->setPosition(ccp(centerX,bottomMargin));

	bottomMargin += SHARED_POPUP_MENU_MARGIN;

	CCMenuItemImage *pResume = CCMenuItemImage::create(
		SHARED_POPUP_RESUME.c_str(),
		SHARED_POPUP_RESUME.c_str(),
		this,
		menu_selector(CHomeMenuLayer::SettingIconCallback)
		);
	m_iconResume = CCMenu::create(pResume,NULL);
	m_iconResume->setPosition(ccp(centerX,bottomMargin));

	m_backLayer->addChild(m_iconResume,1);
	m_backLayer->addChild(m_iconHelp,1);
	m_backLayer->addChild(m_iconSetting,1);
	m_backLayer->addChild(m_iconQuit,1);


	return true;
}

void CHomeMenuLayer::homeMenuCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	//home menu popup
	m_backLayer->setVisible(true);
	CCDirector::sharedDirector()->pause();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}

void CHomeMenuLayer::HelpIconCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	//help 창으로 간다

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}

void CHomeMenuLayer::ResumeIconCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	//home menu popup
	m_backLayer->setVisible(false);
	CCDirector::sharedDirector()->resume();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}

void CHomeMenuLayer::SettingIconCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	//셋팅 창으로 간다.

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}

void CHomeMenuLayer::QuitIconCallback( CCObject* pSender )
{
	//메인으로 돌아갈꺼야
}
