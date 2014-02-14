#include "HomeMenuLayer.h"
#include "MainScene.h"

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
		"image/icon_menu.png",
		"image/icon_menu_selected.png",
		this,
		menu_selector(CHomeMenuLayer::homeMenuCallback)
		);

	pMenuIcon->setPosition(ccp(visibleSize.width-100.0f, visibleSize.height/2) );

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pMenuIcon, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	
	m_backLayer = CCSprite::create("image/menu_background.png");
	m_backLayer->setVisible(false);
	m_backLayer->setPosition(ccp(origin.x + visibleSize.width/2,origin.y + visibleSize.height/2));
	this->addChild(m_backLayer,2);

	CCSize popUpSize = m_backLayer->getContentSize();

	// 팝업 창 아이콘들
	CCMenuItemImage *pResumeIcon = CCMenuItemImage::create(
		"image/icon_menu_resume.png",
		"image/icon_menu_resume_selected.png",
		this,
		menu_selector(CHomeMenuLayer::ResumeIconCallback)
		);
	m_iconResume = CCMenu::create(pResumeIcon,NULL);
	m_iconResume->setPosition(popUpSize.width/4,popUpSize.height/2);

	CCMenuItemImage *pHomeIcon = CCMenuItemImage::create(
		"image/icon_menu_home.png",
		"image/icon_menu_home_selected.png",
		this,
		menu_selector(CHomeMenuLayer::homeIconCallback)
		);
	m_iconHome = CCMenu::create(pHomeIcon,NULL);
	m_iconHome->setPosition(popUpSize.width/2,popUpSize.height/2);


	CCMenuItemImage *pOptionIcon = CCMenuItemImage::create(
		"image/icon_menu_option.png",
		"image/icon_menu_option_selected.png",
		this,
		menu_selector(CHomeMenuLayer::OptionIconCallback)
		);
	m_iconOption = CCMenu::create(pOptionIcon,NULL);
	m_iconOption->setPosition(popUpSize.width/2+popUpSize.width/4,popUpSize.height/2);

	m_backLayer->addChild(m_iconResume,1);
	m_backLayer->addChild(m_iconHome,1);
	m_backLayer->addChild(m_iconOption,1);

	

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

void CHomeMenuLayer::homeIconCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	//home menu popup
	m_backLayer->setVisible(true);
	CCDirector::sharedDirector()->resume();
	CCDirector::sharedDirector()->replaceScene(CMainScene::create());
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
void CHomeMenuLayer::OptionIconCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	//home menu popup
	m_backLayer->setVisible(true);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}