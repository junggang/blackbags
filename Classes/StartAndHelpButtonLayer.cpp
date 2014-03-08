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
			GAME_SETTING_READY_BTN_UNSELECT.c_str(),
			GAME_SETTING_READY_BTN_SELECT.c_str(),
			this,
			menu_selector(CStartAndHelpButtonLayer::ReadyButtonCallBack)
			);
		m_StartButton->setTag(READY_BUTTON_TAG);
	}
	else
	{
		m_StartButton = CCMenuItemImage::create(
            GAME_SETTING_READY_BTN_UNSELECT.c_str(),
            GAME_SETTING_READY_BTN_SELECT.c_str(),
			this,
			menu_selector(CStartAndHelpButtonLayer::StartButtonCallBack)
			);
		m_StartButton->setTag(START_BUTTON_TAG);
	}
	
	// at init, Start button is disabled
	m_StartButton->setEnabled(false);
    m_StartButton->selected();

    // create StartButtonMenu
	CCMenu	*StartButtonMenu = CCMenu::create(m_StartButton, NULL);
    StartButtonMenu->setPosition(CCPoint(GAME_SETTING_READY_BTN_POS));
    StartButtonMenu->setAnchorPoint(ccp(0, 0));
    
	// add StartButtonMenu to Layer
	this->addChild(StartButtonMenu);
    
    // button Position & readyAnchorPoint (0, 0)
    m_StartButton->setPosition(ccp(0, 0));
    m_StartButton->setAnchorPoint(ccp(0, 0));

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
	// 서버로 레디 신호를 보낸다.
	CGameManager::GetInstance()->StartGame();
	// Scene Change는 GetCurrentScene 을 통해서 비교 / Online 에서는 임의로 Scene을 바꾸지 않는다.
	
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
        // game master
		if ( CGameManager::GetInstance()->IsChannelMaster() )
		{
			if (CGameManager::GetInstance()->IsAllReady() )
			{
				m_StartButton->setEnabled(true);
			}
			else
			{
				m_StartButton->setEnabled(false);
			}
		}
        // just player
		else
		{
			if ( CGameManager::GetInstance()->IsReady() )
			{
				m_StartButton->selected();
			}
			else
			{
				m_StartButton->unselected();
			}

			if (CGameManager::GetInstance()->GetCharacterIdByPlayerId( CGameManager::GetInstance()->GetMyPlayerId() ) != -1 )
			{
				m_StartButton->setEnabled(true);
			}
			else
			{
				m_StartButton->setEnabled(false);
			}
		}
	}

	// Single :: StartButton Condition
	else
	{
		if ( CGameManager::GetInstance()->GetCurrentPlayerNumber() == CGameManager::GetInstance()->GetPlayerNumberOfThisGame() )
		{
			m_StartButton->setEnabled(true);
            m_StartButton->selected();
		}
		else
		{
			m_StartButton->setEnabled(false);
            m_StartButton->unselected();
		}
	}
}