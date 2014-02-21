#include "PlayScene.h"
#include "BackgroundLayer.h"
#include "GameBoardLayer.h"
#include "GameEndLayer.h"
#include "HelpButtonLayer.h"
#include "HelpWindowLayer.h"
#include "PlayerLayer.h"
#include "TimerLayer.h"
#include "GameManager.h"
#include "HomeMenuLayer.h"

USING_NS_CC;

bool CPlayScene::init(void)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCScene::init() )
	{
		return false;
	}

	/////////////////////////////
    // 2. add layers
	CCLayer* BackgroundLayer = CBackgroundLayer::create();
	this->addChild(BackgroundLayer, 0);

	gameBoard = CGameBoardLayer::create();
	this->addChild(gameBoard, 1);

	CCLayer* helpButton = CHelpButtonLayer::create();
	this->addChild(helpButton, 1);

	player = CPlayerLayer::create();
	this->addChild(player, 1);

	timer = CTimerLayer::create();
	this->addChild(timer, 1);

	CCLayer* helpWindow = CHelpWindowLayer::create();
	this->addChild(helpWindow, 2);

	menu = CHomeMenuLayer::create();
	this->addChild(menu,2);

	if (CGameManager::GetInstance()->IsOnlineMode() )
	{
		// ������ �ֱ������� ������Ʈ Ȯ��
		this->schedule(schedule_selector(CGameManager::PlayUpdate), 1.0f);
	}

	//�̷��� �����ϸ� update�Լ��� �˾Ƽ� �����Ӹ��� ȣ��ȴ�.
	this->scheduleUpdate();

	m_GameEndFlag = false;

	if (CGameManager::GetInstance()->IsOnlineMode() )
	{
		// playScene�� �غ�Ǿ����Ƿ� �غ� �Ǿ��ٴ� ��ȣ�� ������ ������
		// ������ �ֱ������� ������Ʈ ������ Ȯ���ϴ� �������� ����
		CGameManager::GetInstance()->PlayReady();
		this->schedule(schedule_selector(CGameManager::PlayUpdate), 1.0f);
	}

	return true;
}

void CPlayScene::update(float dt)
{
	if (!CGameManager::GetInstance()->IsUpdated() )
	{
		return;
	}

	//���� ���� Ȯ��
	if (CGameManager::GetInstance()->IsEnd() && !m_GameEndFlag)
	{
		m_GameEndFlag = true; //�ٽ� �� ���ǹ� ������ �����ؼ� ���̾ �߰����� �ʵ���

		//���� �޽��� layer�� child�� �߰��ؼ� result�� �� �� �ְ� �Ѵ�.
		CCLayer* endButton = CGameEndLayer::create();
		this->addChild(endButton, 2);

		if (CGameManager::GetInstance()->IsOnlineMode() )
		{
			CGameManager::GetInstance()->Logout();
			this->unschedule(schedule_selector(CGameManager::PlayUpdate) );
		}
	}

	gameBoard->update(dt);
	player->update(dt);
	timer->update(dt);

	//������Ʈ�� ������ ��� �޾ƿͼ� ���������Ƿ� flag�� ������� false�� �����
	CGameManager::GetInstance()->SetUpdateFlag(false);
}