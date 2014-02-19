#include "StartAndHelpButtonLayer.h"
#include "HelpPopuplLayer.h"
#include "PlayScene.h"
#include "HelpScene.h"
#include "GameManager.h"

USING_NS_CC;

const int HELP_POPUPLAYER_TAG = 1000;
const int START_BUTTON_TAG = 2000;
const int READY_BUTTON_TAG = 3000;

bool CStartAndHelpButtonLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// get Windows Size
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//// start Button
	if ( CGameManager::GetInstance()->IsOnlineMode() && !CGameManager::GetInstance()->IsChannelMaster() )
	{
		m_StartButton = CCMenuItemImage::create(
			"image/SETTING_ready_unselected.png",
			"image/SETTING_ready_selected.png",
			this,
			menu_selector(CStartAndHelpButtonLayer::ReadyButtonCallBack)
			);
		m_StartButton->setTag(READY_BUTTON_TAG);
	}
	else
	{
		m_StartButton = CCMenuItemImage::create(
			"image/SETTING_start.png",
			"image/SETTING_start.png",
			this,
			menu_selector(CStartAndHelpButtonLayer::StartButtonCallBack)
			);
		m_StartButton->setTag(START_BUTTON_TAG);
	}
	
	// at init, Start button is disabled
	m_StartButton->setEnabled(false);

	CCMenu	*StartButtonMenu = CCMenu::create(m_StartButton, NULL);

	StartButtonMenu->setPosition(visibleSize.width/2, visibleSize.height/2 + 200);

	// add StartButtonMenu to Layer
	this->addChild(StartButtonMenu);

	/// Help Button
	CCMenuItemImage *HelpButton = CCMenuItemImage::create(
		"image/icon_help.png",
		"image/icon_help.png",
		this,
		menu_selector(CStartAndHelpButtonLayer::HelpButtonCallBack)
		);

	CCMenu	*HelpButtonMenu = CCMenu::create(HelpButton, NULL);

	HelpButtonMenu->setPosition(visibleSize.width - HelpButton->getContentSize().width,
								visibleSize.height - HelpButton->getContentSize().height);

	this->addChild(HelpButtonMenu);

	//// align menu element
	StartButtonMenu->alignItemsHorizontally();

	return true;
}

void CStartAndHelpButtonLayer::StartButtonCallBack( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CGameManager::GetInstance()->StartGame();

	if ( !CGameManager::GetInstance()->IsOnlineMode() )
	{
		CCScene* newScene = CPlayScene::create();
		CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(0.5, newScene) );
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}

void CStartAndHelpButtonLayer::ReadyButtonCallBack( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// ������ ���� ��ȣ�� ������.
	CGameManager::GetInstance()->StartGame();
	// Scene Change�� GetCurrentScene �� ���ؼ� �� / Online ������ ���Ƿ� Scene�� �ٲ��� �ʴ´�.
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}

void CStartAndHelpButtonLayer::HelpButtonCallBack( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// �˾� ���̾� ����
	CHelpPopupLayer* newLayer = CHelpPopupLayer::create();
	
	if (newLayer != NULL)
	{
		newLayer->setTag(HELP_POPUPLAYER_TAG);
		this->addChild(newLayer);
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}

void CStartAndHelpButtonLayer::update()
{
	// Online Condition
	if ( CGameManager::GetInstance()->IsOnlineMode() )
	{
		// 1. Start Button?
		// ���� �����̰� ��ΰ� Ready ���� �� StartButton�� Ȱ��ȭ ��Ų��.
		if ( CGameManager::GetInstance()->IsChannelMaster() && 
			CGameManager::GetInstance()->IsAllReady() )
		{
			m_StartButton->setEnabled(true);
		}
		else
		{
			m_StartButton->setEnabled(false);
		}
		// 2. Ready Button?
		// ���� ������ �ƴϰ� ĳ���͸� ����� �� ReadyButton�� Ȱ��ȭ ��Ų��.
		if ( !CGameManager::GetInstance()->IsChannelMaster() 
			&& CGameManager::GetInstance()->GetCharacterIdByPlayerId( CGameManager::GetInstance()->GetMyPlayerId() ) != -1 )
		{
			m_StartButton->setEnabled(true);
		}
		else
		{
			m_StartButton->setEnabled(false);
		}
		// 3. Scene Change && Game Start??
		// �������� ������ ���ƿ��� Scene Change
	}

	// Single :: StartButton Condition
	else
	{
		if ( CGameManager::GetInstance()->GetCurrentPlayerNumber() == CGameManager::GetInstance()->GetPlayerNumberOfThisGame() )
		{
			m_StartButton->setEnabled(true);
		}
		else
		{
			m_StartButton->setEnabled(false);
		}
	}
}