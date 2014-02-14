#include "MainScene.h"
#include "BackgroundLayer.h"
#include "GameSettingScene.h"

#include "SettingTitleLayer.h"
#include "WaitingChannelId.h"
#include "NetworkPlayerNumberLayer.h"
#include "PlayerNumberAndMapSizeLayer.h"

#include "MainScene.h"

#include "GameManager.h"


USING_NS_CC;

bool CGameSettingScene::init(void)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCScene::init() )
	{
		return false;
	}

	// init state == firstStep(Select PlayerNumber and MapSize)
	isSceondStep = false;

	// init current network phase
	m_CurrentPhase = CGameManager::GetInstance()->GetCurrentNetworkPhase();

	/////////////////////////////
	// 2. add layers
	
	// background layer
	CCLayer* BackgroundLayer = CBackgroundLayer::create();
	this->addChild(BackgroundLayer, 0);

	// 2.1 add Player Number and Map Size Select layer
	if ( CGameManager::GetInstance()->IsOnlineMode() ) // OnlineGame
	{
		m_PlayerNumberAndMapSizeLayer = CNetworkPlayerNumberLayer::create();
		this->addChild(m_PlayerNumberAndMapSizeLayer, 1);
	}
	else // Single Game
	{
		m_PlayerNumberAndMapSizeLayer = CPlayerNumberAndMapSizeLayer::create();
		this->addChild(m_PlayerNumberAndMapSizeLayer, 1);
	}

	// 처음 생성된 레이어가 최신 정보로 업데이트 된 상태로 시작할 수 있도록 플래그 설정
	CGameManager::GetInstance()->SetUpdateFlag(true);

	// 현재 레이어에 생성한 레이어를 할당
	m_CurrentLayer = m_PlayerNumberAndMapSizeLayer;

	this->scheduleUpdate();

	return true;
}

void CGameSettingScene::update(float dt)
{
	//dt는 이전 update 이후 지난 시간

	/*
		업데이트하는 방법이 일단 온라인이든지 오프라인이든지 관계없이
		일단 업데이트 플래그를 확인해서 업데이트가 되었다면 온라인 오프라인으로 구분해서 처리할 것
		현재 넥스트 표시 기준은 업데이트 여부 상관 없이 반복적으로 확인하고 있음
	*/


	if ( CGameManager::GetInstance()->IsOnlineMode() )
	{
		if (CGameManager::GetInstance()->IsUpdated() )
		{
			// 만약 업데이트 된 내용이 있다면 현재 phase가 바뀌었는지 확인한다.
			// 로컬에 현재 phase를 저장한 다음, 네트워크 phase와 로컬 phase가 같으면 아래 switch 문은 건너뛴다.
			NetworkPhase tempPhase = CGameManager::GetInstance()->GetCurrentNetworkPhase();

			if (m_CurrentPhase != tempPhase)
			{
				// 상태가 바뀌면 현재 상태를 바꿔주고 
				// 바뀐 상태에 해당하는 레이어를 생성한다.

				m_CurrentPhase = tempPhase;
				this->removeChild(m_CurrentLayer);
				m_CurrentLayer = nullptr;

				CCScene* newScene = nullptr;

				switch (tempPhase)
				{
				case NP_NOTHING:
					// return to the main menu
					newScene = CMainScene::create();
					CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
					return;
					break;
				case NP_GAME_SETTING:
					// real setting layer
					AddSceondStepLayers();
					isSceondStep = true;
					break;
				case NP_PLAYER_NUMBER_SETTING:
					// select player number layer
					m_PlayerNumberAndMapSizeLayer = CNetworkPlayerNumberLayer::create();
					this->addChild(m_PlayerNumberAndMapSizeLayer, 1);

					m_CurrentLayer = m_PlayerNumberAndMapSizeLayer;
					break;
				case NP_WAITING_CHANNEL_ID:
					// waiting channel id layer
					m_CurrentLayer = CWaitingChannelId::create();
					this->addChild(m_CurrentLayer, 1);
					break;
				default:
					break;
				}
			}

			this->m_CurrentLayer->update(dt);
			CGameManager::GetInstance()->SetUpdateFlag(false);
		}
	}
	else
	{
		// 2.2 After Choose Player Number and Map Size, Go Next Step.
		if ( CGameManager::GetInstance()->IsNextButtonSelected() && !isSceondStep )
		{
			AddSceondStepLayers();
			isSceondStep = true;
			this->removeChild(m_PlayerNumberAndMapSizeLayer);
		}

		// if Second Step
		if (CGameManager::GetInstance()->IsUpdated() )
		{
			if (isSceondStep)
			{
				//여기에 각 레이어들을 업데이트하는 코드를 넣음
				m_SettingCharacterLayer->update();
				m_OtherPlayerStatusLayer->update();
				m_StartAndHelpButtonLayer->update();
				//업데이트된 내용을 모두 받아와서 갱신했으므로 flag는 원래대로 false로 만든다
				CGameManager::GetInstance()->SetUpdateFlag(false);
			}
			// is First Step
			else
			{
				m_PlayerNumberAndMapSizeLayer->update(dt);
				CGameManager::GetInstance()->SetUpdateFlag(false);
			}
		}
		
	}
}

void CGameSettingScene::AddSceondStepLayers()
{
	// title layer
	CCLayer* SettingTitleLayer = CSettingTitleLayer::create();
	this->addChild(SettingTitleLayer, 1);

	// Character Select Table layer
	m_SettingCharacterLayer = CSettingCharacterLayer::create();
	this->addChild(m_SettingCharacterLayer, 1);

	// StartButton and HelpButton layer
	m_StartAndHelpButtonLayer = CStartAndHelpButtonLayer::create();
	this->addChild(m_StartAndHelpButtonLayer, 1);

	// PlayerStatusLayer
	m_OtherPlayerStatusLayer = CSettingOtherPlayerStatusLayer::create();
	this->addChild(m_OtherPlayerStatusLayer, 1);
}