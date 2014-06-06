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

	//Ω√¿€«œ∏Èº≠ «— π¯ æ˜µ•¿Ã∆Æ «ÿæﬂµ«¥¬µ•.
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

		if (m_CurrentServerTimerStatus)
		{
			float delayTime = CGameManager::GetInstance()->GetAnimationDelay() + 1.2f;
            CCDelayTime* delayAction = CCDelayTime::create(delayTime);
            
            m_progressTimeBar->stopAllActions();
            //¥Ÿ∏• æ÷¥œ∏ﬁ¿Ãº«µÈ ≥°≥Ø ∂ß ±Ó¡ˆ ±‚¥Ÿ∑»¥Ÿ∞° ≈∏¿Ã∏”∏¶ ¿Áª˝«ÿ¡÷µµ∑œ «œ¿⁄.
            CCProgressFromTo *progressToZero = CCProgressFromTo::create(20, 100, 0);
            CCFiniteTimeAction* pAction = CCSequence::create(delayAction,progressToZero, CCCallFunc::create(this, callfunc_selector(CTimerLayer::timerEndFunc)),NULL);
            m_progressTimeBar->runAction(pAction);
		}
	}
    // Offline
	else
	{
        float delayTime = CGameManager::GetInstance()->GetAnimationDelay() + 1.2f;
        CCDelayTime* delayAction = CCDelayTime::create(delayTime);
		   
		m_progressTimeBar->stopAllActions();
		//¥Ÿ∏• æ÷¥œ∏ﬁ¿Ãº«µÈ ≥°≥Ø ∂ß ±Ó¡ˆ ±‚¥Ÿ∑»¥Ÿ∞° ≈∏¿Ã∏”∏¶ ¿Áª˝«ÿ¡÷µµ∑œ «œ¿⁄.
		CCProgressFromTo *progressToZero = CCProgressFromTo::create(20, 100, 0);
		CCFiniteTimeAction* pAction = CCSequence::create(delayAction,progressToZero, CCCallFunc::create(this, callfunc_selector(CTimerLayer::timerEndFunc)),NULL);
		m_progressTimeBar->runAction(pAction);
	}
}

void CTimerLayer::timerEndFunc()
{
	CCLog("Timer Ended!");
    
    //타임아웃 애니메이션
    CCSprite* pTimeOut = CCSprite::create(PLAYSCENE_TIMER_OUT.c_str());
    pTimeOut->setAnchorPoint(ccp(0,0));
    pTimeOut->setPosition(CCPoint(PLAYSCENE_TIMER_OUT_POS));
    CCActionInterval* jumpAction=CCJumpBy::create(1, ccp(0, 0), 50, 2);
    CCFadeOut* FadeOut = CCFadeOut::create(0.4f);
    CCAction* sequence = CCSequence::create(CCDelayTime::create(0.6f),FadeOut,NULL);
	pTimeOut->runAction(jumpAction);
    pTimeOut->runAction(sequence);
    addChild(pTimeOut,2);
    
	//≈∏¿Ã∏”∞° ≥°≥≠ »ƒ √Î«ÿ¡˙ æ◊º«
	CGameManager::GetInstance()->TimeOut();
}



