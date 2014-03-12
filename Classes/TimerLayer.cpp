#include "TimerLayer.h"
#include "GameManager.h"

USING_NS_CC;

bool CTimerLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	m_CurrentServerTimerStatus = CGameManager::GetInstance()->GetCurrentTimerStatus();

	m_VisibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite* timerBg = CCSprite::create(PLAYSCENE_TIMER_BG.c_str());
	timerBg->setAnchorPoint(ccp(0,0));
	timerBg->setPosition(CCPoint(PLAYSCENE_TIMER_POS));
	addChild(timerBg,0);

	CCSprite* timerBar = CCSprite::create(PLAYSCENE_TIMER_BAR.c_str());
	m_progressTimeBar = CCProgressTimer::create(timerBar);
	m_progressTimeBar->setType(kCCProgressTimerTypeBar);

	m_progressTimeBar->setAnchorPoint(ccp(0,0));
	m_progressTimeBar->setPosition(CCPoint(PLAYSCENE_TIMER_POS));

    m_progressTimeBar->setScale(m_VisibleSize.width/3.65/timerBar->getContentSize().width);
	m_progressTimeBar->setPercentage(100.f);
	m_progressTimeBar->setMidpoint(ccp(0, 0.5));   
	m_progressTimeBar->setBarChangeRate(ccp(1,0));
    m_progressTimeBar->setType(kCCProgressTimerTypeBar);
    
	addChild(m_progressTimeBar,1);

	//시작하면서 한 번 업데이트 해야되는데.
	CCProgressFromTo *progressToZero = CCProgressFromTo::create(20, 100, 0);
	CCFiniteTimeAction* pAction = CCSequence::create(progressToZero, CCCallFunc::create(this, callfunc_selector(CTimerLayer::timerEndFunc)),NULL);

	m_progressTimeBar->runAction(pAction);

	return true;
}

void CTimerLayer::update( float dt )
{
	if (CGameManager::GetInstance()->IsOnlineMode() )
	{
		bool newStatus = CGameManager::GetInstance()->GetCurrentTimerStatus();

		if (m_CurrentServerTimerStatus == newStatus)
		{
			return;
		}

		m_CurrentServerTimerStatus = newStatus;

		if (!m_CurrentServerTimerStatus)
		{
			// true >>> false 이므로 타이머 새로 시작(각 클라이언트의 레디 신호를 모두 수신해서 새로운 턴이 시작)
			// 일단 기존 타이머 삭제
			m_progressTimeBar->stopAllActions();

			CCProgressFromTo *progressToZero = CCProgressFromTo::create(20, 100, 0);
			CCFiniteTimeAction* pAction = CCSequence::create(progressToZero, CCCallFunc::create(this, callfunc_selector(CTimerLayer::timerEndFunc)),NULL);
			m_progressTimeBar->runAction(pAction);
		}
		else
		{
			// false >>> true 이므로 타이머 일시 정지
			m_progressTimeBar->pauseSchedulerAndActions();
		}
	}
    // Offline
	else
	{
        float delayTime = CGameManager::GetInstance()->GetAnimationDelay()+1.2f;
        CCDelayTime* delayAction = CCDelayTime::create(delayTime);
		   
		m_progressTimeBar->stopAllActions();
		//다른 애니메이션들 끝날 때 까지 기다렸다가 타이머를 재생해주도록 하자.
		CCProgressFromTo *progressToZero = CCProgressFromTo::create(20, 100, 0);
		CCFiniteTimeAction* pAction = CCSequence::create(delayAction,progressToZero, CCCallFunc::create(this, callfunc_selector(CTimerLayer::timerEndFunc)),NULL);
		m_progressTimeBar->runAction(pAction);
	}
}

void CTimerLayer::timerEndFunc()
{
	CCLog("Timer Ended!");
	//타이머가 끝난 후 취해질 액션
	CGameManager::GetInstance()->TimeOut();
}
