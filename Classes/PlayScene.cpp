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
#include "DisconnectedLayer.h"
#include "AudioManager.h"

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

    m_GameEndFlag = false;
	m_AnimationDelay = 0.0f;

	if (CGameManager::GetInstance()->IsOnlineMode() )
	{
		// 플레이 준비가 되었다는 신호를 서버로 보내고
		// 주기적으로 게임 상태를 확인 요청하는 스케줄 생성
		CGameManager::GetInstance()->PlayReady();
		this->schedule(schedule_selector(CGameManager::PlayUpdate), 1.0f);
	}
    
	// 등록된 스케줄 실행
	this->scheduleUpdate();
    
    //temporary - 이거 뭐임? - playReady 보내는거 아님??
    CGameManager::GetInstance()->SetPlayReady();
    
    // play music "BGM_PLAY" made by Junggang
    CAudioManager::GetInstance()->StopBGM();
    
	CAudioManager::GetInstance()->ChangeMusic(BGM_PLAY);
	CAudioManager::GetInstance()->PlayBGM();
    
	return true;
}

void CPlayScene::update(float dt)
{
	if (!CGameManager::GetInstance()->IsUpdated() || m_GameEndFlag)
	{
		return;
	}
    
    CGameManager::GetInstance()->PausePlayReady();

	// 종료 조건 확인
	if (CGameManager::GetInstance()->IsEnd() && !m_GameEndFlag)
	{
		m_GameEndFlag = true; // 다음 루프에서 다시 진입하지 않도록 플래그 설정
        removeChild(timer);
        player->stopAllActions();

		// 게임 종료 버튼 생성
		CCLayer* endButton = CGameEndLayer::create();
		this->addChild(endButton, 2);

		if (CGameManager::GetInstance()->IsOnlineMode() )
		{
            // 온라인 모드인 경우 게임 종료 요청을 서버로 전송 후 업데이트 스케줄 삭제
			CGameManager::GetInstance()->EndGame();
			this->unschedule(schedule_selector(CGameManager::PlayUpdate) );
		}
        return;
    }

    // 종료가 아닌 경우 각종 업데이트 실행
	gameBoard->update(dt);
	player->update(dt);
	timer->update(dt);

	if (CGameManager::GetInstance()->IsOnlineMode() )
	{
        // 접속 상태 확인
        if (!CGameManager::GetInstance()->GetConnectionStatus()
            && !CGameManager::GetInstance()->IsEnd())
        {
            // 업데이트 중단
            this->unscheduleAllSelectors();
            
            // 오류 레이어 생성
            this->removeAllChildren();
            
            CCLayer* BackgroundLayer = CBackgroundLayer::create();
            this->addChild(BackgroundLayer, 0);
            
            CCLayer* DisconnectedLayer = CDisconnectedLayer::create();
            this->addChild(DisconnectedLayer, 1);
            
            return;
            
        }
		// 라인 재생 시간과 타일 재생 시간이 같으므로 아래의 코드에서 0.8의 상수는
        // 라인 재생만 있을 경우에는 라인 재생 시간을, 타일 애니메이션이 포함되는 경우에는 마지막 재생되는 타일 애니메이션 재생 시간을 의미
		float delayTime = CGameManager::GetInstance()->GetAnimationDelay() + 0.8f;
        
		// 애니메이션 끝나면 레디 전송하는 코드 삽입!
		CCCallFunc* readyRequestCallback = CCCallFunc::create(this, callfunc_selector(CGameManager::PlayReady) );
		CCDelayTime* delayAction = CCDelayTime::create(delayTime);
		this->runAction(CCSequence::create(delayAction, readyRequestCallback, NULL));

		// 애니메이션 전송 지연값 초기화
		CGameManager::GetInstance()->SetAnimationDelay(0.0f);
	}
    else
    {
        CCLog("playScene");
        float delayTime = CGameManager::GetInstance()->GetAnimationDelay() + 1.0f;
        
		// 애니메이션 끝내고 다음 턴 시작
		CCCallFunc* readyRequestCallback = CCCallFunc::create(this, callfunc_selector(CGameManager::SetPlayReady) );
		CCDelayTime* delayAction = CCDelayTime::create(delayTime);
		this->runAction(CCSequence::create(delayAction, readyRequestCallback, NULL));
        
        CGameManager::GetInstance()->SetAnimationDelay(0.0f);
    }

	// 모든 업데이트가 완료되었으므로 플래그 초기화
	CGameManager::GetInstance()->SetUpdateFlag(false);
}