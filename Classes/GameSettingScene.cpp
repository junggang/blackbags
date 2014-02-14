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

	// ó�� ������ ���̾ �ֽ� ������ ������Ʈ �� ���·� ������ �� �ֵ��� �÷��� ����
	CGameManager::GetInstance()->SetUpdateFlag(true);

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

	if ( !CGameManager::GetInstance()->IsUpdated() )
	{
		return;
	}

	if ( CGameManager::GetInstance()->IsOnlineMode() )
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