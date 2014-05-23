#include "HomeMenuPopUp.h"
#include "MainScene.h"
#include "config.h"
#include "HelpScene.h"
#include "SettingScene.h"
#include "HelpPopuplLayer.h"

USING_NS_CC;

bool CHomeMenuPopUp::init()
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
	m_backLayer = CCSprite::create(SHARED_POPUP_BG.c_str());
	m_backLayer->setAnchorPoint(ccp(0,0));
	m_backLayer->setPosition(CCPoint(SHARED_POPUP_BG_POS));
	addChild(m_backLayer,0);

	float centerX =visibleSize.width/2;
	float bottomMargin = SHARED_POPUP_BOTTOM_MARGIN;

	CCSprite* pTitle = CCSprite::create(SHARED_POPUP_TITLE.c_str());
	pTitle->setPosition(ccp(centerX,SHARED_POPUP_TITLE_POS));
	addChild(pTitle);


	// 팝업 창 아이콘들

	CCMenuItemImage *pQuitIcon = CCMenuItemImage::create(
		SHARED_POPUP_QUIT.c_str(),
		SHARED_POPUP_QUIT.c_str(),
		this,
		menu_selector(CHomeMenuPopUp::QuitIconCallback)
		);
	m_iconQuit = CCMenu::create(pQuitIcon,NULL);
	m_iconQuit->setPosition(ccp(centerX,bottomMargin));

	bottomMargin += SHARED_POPUP_MENU_MARGIN;

	CCMenuItemImage *pSetting = CCMenuItemImage::create(
		SHARED_POPUP_SETTING.c_str(),
		SHARED_POPUP_SETTING.c_str(),
		this,
		menu_selector(CHomeMenuPopUp::SettingIconCallback)
		);
	m_iconSetting = CCMenu::create(pSetting,NULL);
	m_iconSetting->setPosition(ccp(centerX,bottomMargin));

	bottomMargin += SHARED_POPUP_MENU_MARGIN;

	CCMenuItemImage *pHelpIcon = CCMenuItemImage::create(
		SHARED_POPUP_HELP.c_str(),
		SHARED_POPUP_HELP.c_str(),
		this,
		menu_selector(CHomeMenuPopUp::HelpIconCallback)
		);
	m_iconHelp = CCMenu::create(pHelpIcon,NULL);
	m_iconHelp->setPosition(ccp(centerX,bottomMargin));

	bottomMargin += SHARED_POPUP_MENU_MARGIN;

	CCMenuItemImage *pResume = CCMenuItemImage::create(
		SHARED_POPUP_RESUME.c_str(),
		SHARED_POPUP_RESUME.c_str(),
		this,
		menu_selector(CHomeMenuPopUp::ResumeIconCallback)
		);
	m_iconResume = CCMenu::create(pResume,NULL);
	m_iconResume->setPosition(ccp(centerX,bottomMargin));

	addChild(m_iconResume,1);
	addChild(m_iconHelp,1);
	addChild(m_iconSetting,1);
	addChild(m_iconQuit,1);
	
	return true;
}

void CHomeMenuPopUp::HelpIconCallback(CCObject* pSender)
{
	//help 창으로 간다
	//CCScene* newScene = CHelpScene::create();
	//CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5, newScene) );
    
    CCLayer* helpLayer = CHelpPopupLayer::create();
    helpLayer->setTag(0);
    addChild(helpLayer, 2);
}

void CHomeMenuPopUp::ResumeIconCallback(CCObject* pSender)
{
	//home menu popup
	CCDirector::sharedDirector()->resume();
	removeAllChildrenWithCleanup(true);
}

void CHomeMenuPopUp::SettingIconCallback(CCObject* pSender)
{
//  	CCScene* newScene = CSettingScene::create();
//  	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5, newScene) );
	
	//그냥 팝업안에서 넘어가도록 하고 싶은데..?
 	CCLayer* settingPopUp = CSettingMenuLayer::create();
	settingPopUp->setTag(0);
 	addChild(settingPopUp,2);

	CCMenuItemImage *pBackToMainButton = CCMenuItemImage::create(
		SHARED_BTN_BACK.c_str(),
		SHARED_BTN_BACK.c_str(),
		this,
		menu_selector(CHomeMenuPopUp::BackToPopUp)
		);

	//이거보단 X버튼이 낫겠따. X버튼을 만들도록 하겠어요~
	pBackToMainButton->setAnchorPoint(ccp(0,0));
	CCMenu* pMenu = CCMenu::create(pBackToMainButton, NULL);
	pMenu->setPosition(SHARED_BTN_BACK_POS);
	pMenu->setTag(1);
	addChild(pMenu, 2);

}

void CHomeMenuPopUp::QuitIconCallback( CCObject* pSender )
{
	//메인으로 돌아갈꺼야
	CCScene* newScene = CMainScene::create();
	CCDirector::sharedDirector()->resume();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
}

void CHomeMenuPopUp::BackToPopUp( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	removeChildByTag(0);
	removeChildByTag(1);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}
