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

	// ó�� ������ ���̾ �ֽ� ������ ������Ʈ �� ���·� ������ �� �ֵ��� �÷��� ����
	CGameManager::GetInstance()->SetUpdateFlag(true);

	// ���� ���̾ ������ ���̾ �Ҵ�
	m_CurrentLayer = m_PlayerNumberAndMapSizeLayer;

	this->scheduleUpdate();

	return true;
}

void CGameSettingScene::update(float dt)
{
	//dt�� ���� update ���� ���� �ð�

	/*
		������Ʈ�ϴ� ����� �ϴ� �¶����̵��� ���������̵��� �������
		�ϴ� ������Ʈ �÷��׸� Ȯ���ؼ� ������Ʈ�� �Ǿ��ٸ� �¶��� ������������ �����ؼ� ó���� ��
		���� �ؽ�Ʈ ǥ�� ������ ������Ʈ ���� ��� ���� �ݺ������� Ȯ���ϰ� ����
	*/


	if ( CGameManager::GetInstance()->IsOnlineMode() )
	{
		if (CGameManager::GetInstance()->IsUpdated() )
		{
			// ���� ������Ʈ �� ������ �ִٸ� ���� phase�� �ٲ������ Ȯ���Ѵ�.
			// ���ÿ� ���� phase�� ������ ����, ��Ʈ��ũ phase�� ���� phase�� ������ �Ʒ� switch ���� �ǳʶڴ�.
			NetworkPhase tempPhase = CGameManager::GetInstance()->GetCurrentNetworkPhase();

			if (m_CurrentPhase != tempPhase)
			{
				// ���°� �ٲ�� ���� ���¸� �ٲ��ְ� 
				// �ٲ� ���¿� �ش��ϴ� ���̾ �����Ѵ�.

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
				//���⿡ �� ���̾���� ������Ʈ�ϴ� �ڵ带 ����
				m_SettingCharacterLayer->update();
				m_OtherPlayerStatusLayer->update();
				m_StartAndHelpButtonLayer->update();
				//������Ʈ�� ������ ��� �޾ƿͼ� ���������Ƿ� flag�� ������� false�� �����
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