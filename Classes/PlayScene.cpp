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
		// 서버에 주기적으로 업데이트 확인
		this->schedule(schedule_selector(CGameManager::PlayUpdate), 1.0f);
	}

	//이렇게 설정하면 update함수가 알아서 프레임마다 호출된다.
	this->scheduleUpdate();

	m_GameEndFlag = false;
	m_AnimationDelay = 0.0f;

	if (CGameManager::GetInstance()->IsOnlineMode() )
	{
		// playScene이 준비되었으므로 준비 되었다는 신호를 서버로 보내고
		// 앞으로 주기적으로 업데이트 내용을 확인하는 스케줄을 실행
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

	//게임 종료 확인
	if (CGameManager::GetInstance()->IsEnd() && !m_GameEndFlag)
	{
		m_GameEndFlag = true; //다시 이 조건문 안으로 진입해서 레이어를 추가하지 않도록

		//종료 메시지 layer를 child로 추가해서 result로 갈 수 있게 한다.
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
		// 라인 재생 시간과 타일 재생 시간이 같으므로 아래의 코드에서 0.8의 상수는
		// 라인 재생만 있을 경우에는 라인 재생 시간을, 타일 애니메이션이 포함되는 경우에는 마지막 재생되는 타일 애니메이션 재생 시간을 의미
		float delayTime = CGameManager::GetInstance()->GetAnimationDelay() + 0.8f;

		// 얼마 후에 전송하는 코드 삽입!
		CCCallFunc* readyRequestCallback = CCCallFunc::create(this, callfunc_selector(CGameManager::PlayReady) );
		CCDelayTime* delayAction = CCDelayTime::create(delayTime);
		this->runAction(CCSequence::create(delayAction, readyRequestCallback, NULL));

		// 애니메이션 전송 지연값 초기화
		CGameManager::GetInstance()->SetAnimationDelay(0.0f);
	}

	//업데이트된 내용을 모두 받아와서 갱신했으므로 flag는 원래대로 false로 만든다
	CGameManager::GetInstance()->SetUpdateFlag(false);
}