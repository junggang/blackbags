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

	//�����ϸ鼭 �� �� ������Ʈ �ؾߵǴµ�.
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
			// true >>> false �̹Ƿ� Ÿ�̸� ���� ����(�� Ŭ���̾�Ʈ�� ���� ��ȣ�� ��� �����ؼ� ���ο� ���� ����)
			// �ϴ� ���� Ÿ�̸� ����
			m_progressTimeBar->stopAllActions();

			CCProgressFromTo *progressToZero = CCProgressFromTo::create(20, 100, 0);
			CCFiniteTimeAction* pAction = CCSequence::create(progressToZero, CCCallFunc::create(this, callfunc_selector(CTimerLayer::timerEndFunc)),NULL);
			m_progressTimeBar->runAction(pAction);
		}
		else
		{
			// false >>> true �̹Ƿ� Ÿ�̸� �Ͻ� ����
			m_progressTimeBar->pauseSchedulerAndActions();
		}
	}
    // Offline
	else
	{
        float delayTime = CGameManager::GetInstance()->GetAnimationDelay()+1.2f;
        CCDelayTime* delayAction = CCDelayTime::create(delayTime);
		   
		m_progressTimeBar->stopAllActions();
		//�ٸ� �ִϸ��̼ǵ� ���� �� ���� ��ٷȴٰ� Ÿ�̸Ӹ� ������ֵ��� ����.
		CCProgressFromTo *progressToZero = CCProgressFromTo::create(20, 100, 0);
		CCFiniteTimeAction* pAction = CCSequence::create(delayAction,progressToZero, CCCallFunc::create(this, callfunc_selector(CTimerLayer::timerEndFunc)),NULL);
		m_progressTimeBar->runAction(pAction);
	}
}

void CTimerLayer::timerEndFunc()
{
	CCLog("Timer Ended!");
	//Ÿ�̸Ӱ� ���� �� ������ �׼�
	CGameManager::GetInstance()->TimeOut();
}
