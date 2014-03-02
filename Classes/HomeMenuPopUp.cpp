#include "HomeMenuPopUp.h"
#include "MainScene.h"
#include "config.h"
#include "HelpScene.h"
#include "GameSettingScene.h"

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
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a background image
	float tempYPos = 0.0;
	CCMenu* pMenu = nullptr;

	m_backLayer = CCSprite::create(SHARED_POPUP_BG.c_str());
	m_backLayer->setAnchorPoint(ccp(0,0));
	m_backLayer->setPosition(CCPoint(SHARED_POPUP_BG_POS));
	addChild(m_backLayer,0);

	float centerX =visibleSize.width/2;
	float bottomMargin = SHARED_POPUP_BOTTOM_MARGIN;

	CCSprite* pTitle = CCSprite::create(SHARED_POPUP_TITLE.c_str());
	pTitle->setPosition(ccp(centerX,SHARED_POPUP_TITLE_POS));
	m_backLayer->addChild(pTitle);


	// �˾� â �����ܵ�

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
	//help â���� ����
	CCScene* newScene = CHelpScene::create();
	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5, newScene) );
}

void CHomeMenuPopUp::ResumeIconCallback(CCObject* pSender)
{
	//home menu popup
	CCDirector::sharedDirector()->resume();
	this->setVisible(false);
}

void CHomeMenuPopUp::SettingIconCallback(CCObject* pSender)
{
	CCScene* newScene = CGameSettingScene::create();
	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5, newScene) );
}

void CHomeMenuPopUp::QuitIconCallback( CCObject* pSender )
{
	//�������� ���ư�����
	CCScene* newScene = CMainScene::create();
	CCDirector::sharedDirector()->resume();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
}
