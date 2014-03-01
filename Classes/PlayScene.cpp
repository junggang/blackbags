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

	player = CPlayerLayer::create();
	this->addChild(player, 1);

	timer = CTimerLayer::create();
	this->addChild(timer, 1);

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
	m_AnimationDelay = 0.0f;

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

	if (CGameManager::GetInstance()->IsOnlineMode() )
	{
		// ���� ��� �ð��� Ÿ�� ��� �ð��� �����Ƿ� �Ʒ��� �ڵ忡�� 0.8�� �����
		// ���� ����� ���� ��쿡�� ���� ��� �ð���, Ÿ�� �ִϸ��̼��� ���ԵǴ� ��쿡�� ������ ����Ǵ� Ÿ�� �ִϸ��̼� ��� �ð��� �ǹ�
		float delayTime = CGameManager::GetInstance()->GetAnimationDelay() + 0.8f;

		// �� �Ŀ� �����ϴ� �ڵ� ����!
		CCCallFunc* readyRequestCallback = CCCallFunc::create(this, callfunc_selector(CGameManager::PlayReady) );
		CCDelayTime* delayAction = CCDelayTime::create(delayTime);
		this->runAction(CCSequence::create(delayAction, readyRequestCallback, NULL));

		// �ִϸ��̼� ���� ������ �ʱ�ȭ
		CGameManager::GetInstance()->SetAnimationDelay(0.0f);
	}

	//������Ʈ�� ������ ��� �޾ƿͼ� ���������Ƿ� flag�� ������� false�� �����
	CGameManager::GetInstance()->SetUpdateFlag(false);
}