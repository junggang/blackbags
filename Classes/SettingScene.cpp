#include "SettingScene.h"
#include "BackgroundLayer.h"
#include "GameManager.h"
#include "AudioManager.h"
#include "AdMobObjectCPP.h"

USING_NS_CC;

bool CSettingScene::init(void)
{
	//////////////////////////////
    // 1. super init first
	if ( !CCScene::init() )
    {
        return false;
    }

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    // 광고 켜기
    gene::AdMobObjectCPP * admob = new gene::AdMobObjectCPP();
    admob->showAdMob();
    
	/////////////////////////////
    // 2. add layers
	CCLayer* BackgroundLayer = CBackgroundLayer::create();

	this->addChild(BackgroundLayer, 0);

	//add Setting Title
	CCSprite* pTitle = CCSprite::create(SETTING_TITLE.c_str());
	pTitle->setPosition(ccp(visibleSize.width/2,SETTING_TITLE_POS));
	addChild(pTitle,1);


	m_SettingMenuLayer = CSettingMenuLayer::create();

	this->addChild(m_SettingMenuLayer, 1);

	//add custom backBtn
	CCMenuItemImage *pBackToMainButton = CCMenuItemImage::create(
		SHARED_BTN_BACK.c_str(),
		SHARED_BTN_BACK.c_str(),
		this,
		menu_selector(CSettingScene::MainSceneCallback)
		);

	pBackToMainButton->setAnchorPoint(ccp(0,0));
	CCMenu* pMenu = CCMenu::create(pBackToMainButton, NULL);
	pMenu->setPosition(SHARED_BTN_BACK_POS);
	addChild(pMenu, 1);



	/////////////////////////////
	// 3. active schedule
	this->scheduleUpdate();

	// 5. initial update
	CGameManager::GetInstance()->SetUpdateFlag(true);

	return true;
}

void CSettingScene::update( float dt )
{
	if ( !CGameManager::GetInstance()->IsUpdated() )
	{
		return;
	}

	m_SettingMenuLayer->update(dt);

	CGameManager::GetInstance()->SetUpdateFlag(false);
}

void CSettingScene::StopBackgroundMusic()
{
	CAudioManager::GetInstance()->StopBGM();
}

void CSettingScene::MainSceneCallback(CCObject* pSender)
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
