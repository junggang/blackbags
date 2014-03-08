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
		// º≠πˆø° ¡÷±‚¿˚¿∏∑Œ æ˜µ•¿Ã∆Æ »Æ¿Œ
		this->schedule(schedule_selector(CGameManager::PlayUpdate), 1.0f);
	}

	//¿Ã∑∏∞‘ º≥¡§«œ∏È update«‘ºˆ∞° æÀæ∆º≠ «¡∑π¿”∏∂¥Ÿ »£√‚µ»¥Ÿ.
	this->scheduleUpdate();

	m_GameEndFlag = false;
	m_AnimationDelay = 0.0f;

	if (CGameManager::GetInstance()->IsOnlineMode() )
	{
		// playScene¿Ã ¡ÿ∫Òµ«æ˙¿∏π«∑Œ ¡ÿ∫Ò µ«æ˙¥Ÿ¥¬ Ω≈»£∏¶ º≠πˆ∑Œ ∫∏≥ª∞Ì
		// æ’¿∏∑Œ ¡÷±‚¿˚¿∏∑Œ æ˜µ•¿Ã∆Æ ≥ªøÎ¿ª »Æ¿Œ«œ¥¬ Ω∫ƒ…¡Ÿ¿ª Ω««‡
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

	//∞‘¿” ¡æ∑· »Æ¿Œ
	if (CGameManager::GetInstance()->IsEnd() && !m_GameEndFlag)
	{
		m_GameEndFlag = true; //¥ŸΩ√ ¿Ã ¡∂∞«πÆ æ»¿∏∑Œ ¡¯¿‘«ÿº≠ ∑π¿ÃæÓ∏¶ √ﬂ∞°«œ¡ˆ æ µµ∑œ

		//¡æ∑· ∏ﬁΩ√¡ˆ layer∏¶ child∑Œ √ﬂ∞°«ÿº≠ result∑Œ ∞• ºˆ ¿÷∞‘ «—¥Ÿ.
		CCLayer* endButton = CGameEndLayer::create();
		this->addChild(endButton, 2);

		if (CGameManager::GetInstance()->IsOnlineMode() )
		{
			CGameManager::GetInstance()->EndGame();
			this->unschedule(schedule_selector(CGameManager::PlayUpdate) );
		}
	}

	gameBoard->update(dt);
	player->update(dt);
	timer->update(dt);

	if (CGameManager::GetInstance()->IsOnlineMode() )
	{
        if (!CGameManager::GetInstance()->GetConnectionStatus())
        {
            // 메인 메뉴로
            // 나중에는 접속 종료 관련 레이어 하나 추가하고 거기서 버튼 누르면 돌아가도록 만들기
            this->removeAllChildren();
            
            CCLayer* BackgroundLayer = CBackgroundLayer::create();
            this->addChild(BackgroundLayer, 0);
            
            CCLayer* DisconnectedLayer = CDisconnectedLayer::create();
            this->addChild(DisconnectedLayer, 1);
            
            return;
            
        }
		// ∂Û¿Œ ¿Áª˝ Ω√∞£∞˙ ≈∏¿œ ¿Áª˝ Ω√∞£¿Ã ∞∞¿∏π«∑Œ æ∆∑°¿« ƒ⁄µÂø°º≠ 0.8¿« ªÛºˆ¥¬
		// ∂Û¿Œ ¿Áª˝∏∏ ¿÷¿ª ∞ÊøÏø°¥¬ ∂Û¿Œ ¿Áª˝ Ω√∞£¿ª, ≈∏¿œ æ÷¥œ∏ﬁ¿Ãº«¿Ã ∆˜«‘µ«¥¬ ∞ÊøÏø°¥¬ ∏∂¡ˆ∏∑ ¿Áª˝µ«¥¬ ≈∏¿œ æ÷¥œ∏ﬁ¿Ãº« ¿Áª˝ Ω√∞£¿ª ¿«πÃ
		float delayTime = CGameManager::GetInstance()->GetAnimationDelay() + 0.8f;
        
		// æÛ∏∂ »ƒø° ¿¸º€«œ¥¬ ƒ⁄µÂ ª¿‘!
		CCCallFunc* readyRequestCallback = CCCallFunc::create(this, callfunc_selector(CGameManager::PlayReady) );
		CCDelayTime* delayAction = CCDelayTime::create(delayTime);
		this->runAction(CCSequence::create(delayAction, readyRequestCallback, NULL));

		// æ÷¥œ∏ﬁ¿Ãº« ¿¸º€ ¡ˆø¨∞™ √ ±‚»≠
		CGameManager::GetInstance()->SetAnimationDelay(0.0f);
	}

	//æ˜µ•¿Ã∆Æµ» ≥ªøÎ¿ª ∏µŒ πﬁæ∆øÕº≠ ∞ªΩ≈«ﬂ¿∏π«∑Œ flag¥¬ ø¯∑°¥Î∑Œ false∑Œ ∏∏µÁ¥Ÿ
	CGameManager::GetInstance()->SetUpdateFlag(false);
}