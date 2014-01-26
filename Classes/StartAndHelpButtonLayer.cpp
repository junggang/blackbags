#include "StartAndHelpButtonLayer.h"
#include "PlayScene.h"
#include "HelpScene.h"
#include "GameManager.h"
#include "PlayerNameSettingScene.h"

USING_NS_CC;

bool CStartAndHelpButtonLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// get Windows Size
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	// start Button
	CCMenuItemImage *StartButton = CCMenuItemImage::create(
		"image/SETTING_start.png",
		"image/SETTING_start.png",
		this,
		menu_selector(CStartAndHelpButtonLayer::StartButtonCallBack)
		);

	CCMenu	*StartButtonMenu = CCMenu::create(StartButton, NULL);

	StartButtonMenu->setPosition(visibleSize.width/2, visibleSize.height/2 + 200);

	// Help Button
	CCMenuItemImage *HelpButton = CCMenuItemImage::create(
		"image/icon_help.png",
		"image/icon_help.png",
		this,
		menu_selector(CStartAndHelpButtonLayer::HelpButtonCallBack)
		);

	// 조심해! 지금은 그냥 StartButton 옆에 띄운다
	StartButtonMenu->addChild(HelpButton);

	StartButtonMenu->alignItemsHorizontally();
	
	// add StartButtonMenu to Layer
	this->addChild(StartButtonMenu);

	return true;
}

void CStartAndHelpButtonLayer::StartButtonCallBack( CCObject* pSender )
{
	CGameManager::GetInstance()->StartGame();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCScene* newScene = CPlayScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

void CStartAndHelpButtonLayer::HelpButtonCallBack( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// 조심해! 여기 Change Scene 대신 팝업 레이어로 바꿔야 해!
	//CCScene* newScene = CHelpScene::create();
	// test : NameSettingScene 기능 테스트를 위해
	CCScene* newScene = CPlayerNameSettingScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}