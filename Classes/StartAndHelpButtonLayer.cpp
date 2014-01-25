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

	// ������! ������ �׳� StartButton ���� ����
	StartButtonMenu->addChild(HelpButton);

	StartButtonMenu->alignItemsHorizontally();
	
	// add StartButtonMenu to Layer
	this->addChild(StartButtonMenu);

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
	// ������! ���� Change Scene ��� �˾� ���̾�� �ٲ�� ��!
	//CCScene* newScene = CHelpScene::create();
	// test : NameSettingScene ��� �׽�Ʈ�� ����
	CCScene* newScene = CPlayerNameSettingScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}