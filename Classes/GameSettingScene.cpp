#include "MainScene.h"
#include "BackgroundLayer.h"
#include "GameSettingScene.h"
#include "SettingFirstStepLayer.h"
#include "SettingSecondStepLayer.h"
#include "WaitingChannelId.h"

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

	m_CurrentLayer = nullptr;

	// init current network phase
	m_CurrentPhase = CGameManager::GetInstance()->GetCurrentNetworkPhase();

	/////////////////////////////
	// 2. add layers
	
	// background layer
	CCLayer* BackgroundLayer = CBackgroundLayer::create();
	this->addChild(BackgroundLayer, 0);

	// 2.1 add Player Number and Map Size Select layer
	m_CurrentLayer = CSettingFirstStepLayer::create();
	this->addChild(m_CurrentLayer);

	// 처음 생성된 레이어가 최신 정보로 업데이트 된 상태로 시작할 수 있도록 플래그 설정
	CGameManager::GetInstance()->SetUpdateFlag(true);

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

	if ( !CGameManager::GetInstance()->IsUpdated() )
	{
		return;
	}

	if ( CGameManager::GetInstance()->IsOnlineMode() )
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
					this->removeChild(m_CurrentLayer);
					m_CurrentLayer = CSettingSecondStepLayer::create();
					this->addChild(m_CurrentLayer);
					break;
				case NP_PLAYER_NUMBER_SETTING:
					// select player number layer
					m_CurrentLayer = CSettingFirstStepLayer::create();
					this->addChild(m_CurrentLayer, 1);
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
		}
	else// SinglePlay
	{
		// 2.2 After Choose Player Number and Map Size, Go Next Step.
		if ( CGameManager::GetInstance()->IsNextButtonSelected() )
			{
			this->removeChild(m_CurrentLayer);
			m_CurrentLayer = CSettingSecondStepLayer::create();
			this->addChild(m_CurrentLayer);
	}
}

	this->m_CurrentLayer->update(dt);
	CGameManager::GetInstance()->SetUpdateFlag(false);
}