#include "StartAndHelpButtonLayer.h"
#include "HelpPopuplLayer.h"
#include "PlayScene.h"
#include "HelpScene.h"
#include "GameManager.h"

USING_NS_CC;

const int HelpPopupLayerId = 1000;

bool CStartAndHelpButtonLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// get Windows Size
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//// start Button
	//// ������!! ���� ���� �������� �ƴ��� ���θ� ���� Ȯ���ؾ� ��!
	if ( CGameManager::GetInstance()->IsOnlineMode() && !CGameManager::GetInstance()->IsChannelMaster() )
	{
		m_StartButton = CCMenuItemImage::create(
			"image/SETTING_ready_unselected.png",
			"image/SETTING_ready_selected.png",
			this,
			menu_selector(CStartAndHelpButtonLayer::StartButtonCallBack)
			);
	}
	else
	{
		m_StartButton = CCMenuItemImage::create(
			"image/SETTING_start.png",
			"image/SETTING_start.png",
			this,
			menu_selector(CStartAndHelpButtonLayer::StartButtonCallBack)
			);
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
	CCScene* newScene = CPlayScene::create();
	CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(0.5, newScene) );
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
		newLayer->setTag(HelpPopupLayerId);
		this->addChild(newLayer);
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}

void CStartAndHelpButtonLayer::update()
{
	// Online :: StartButton Condition
	if ( CGameManager::GetInstance()->IsOnlineMode() )
	{
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