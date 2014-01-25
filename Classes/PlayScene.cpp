#include "PlayScene.h"
#include "BackgroundLayer.h"
#include "GameBoardLayer.h"
#include "GameEndLayer.h"
#include "HelpButtonLayer.h"
#include "HelpWindowLayer.h"
#include "PlayerLayer.h"
#include "TimerLayer.h"
#include "GameManager.h"

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

	//�������Ӹ��� update�Լ� ȣ���ϵ��� ����
	//this->schedule(schedule_selector(CPlayScene::update) );

	//�̷��� �����ϸ� update�Լ��� �˾Ƽ� �����Ӹ��� ȣ��ȴ�.
	this->scheduleUpdate();

	m_GameEndFlag = false;

	return true;
}

void CPlayScene::update(float dt)
{
	//dt�� ���� update ���� ���� �ð�

	
	//���� ���� Ȯ��
	if (CGameManager::GetInstance()->IsEnd() && !m_GameEndFlag)
	{
		m_GameEndFlag = true; //�ٽ� �� ���ǹ� ������ �����ؼ� ���̾ �߰����� �ʵ���

		//���� �޽��� layer�� child�� �߰��ؼ� result�� �� �� �ְ� �Ѵ�.
		CCLayer* endButton = CGameEndLayer::create();
		this->addChild(endButton, 2);
	}

	if (CGameManager::GetInstance()->IsUpdated() )
	{
		//���⿡ �� ���̾���� ������Ʈ�ϴ� �ڵ带 ����
		//�� ���̾�� ������Ʈ �Լ� ������ ��

		gameBoard->update(dt);
		player->update(dt);
		timer->update(dt);

		//������Ʈ�� ������ ��� �޾ƿͼ� ���������Ƿ� flag�� ������� false�� �����
		CGameManager::GetInstance()->SetUpdateFlag(false);
	}
}