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
	m_VisibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSprite* timer = CCSprite::create("image/timer.png");
	m_progressTimeBar = CCProgressTimer::create(timer);
	m_progressTimeBar->setType(kCCProgressTimerTypeBar);

	m_progressTimeBar->setPosition( ccp(origin.x+100.0f, m_VisibleSize.height/2));

	m_progressTimeBar->setScale(m_VisibleSize.height/3.65/timer->getContentSize().height);
	m_progressTimeBar->setPercentage(100.f);
	m_progressTimeBar->setMidpoint(ccp(0, 0));   
	m_progressTimeBar->setBarChangeRate(ccp(0, 1));

	this->addChild(m_progressTimeBar,0);


	//시작하면서 한 번 업데이트 해야되는데.
	CCProgressFromTo *progressToZero = CCProgressFromTo::create(20, 100, 0);
	CCFiniteTimeAction* pAction = CCSequence::create(progressToZero, CCCallFunc::create(this, callfunc_selector(CTimerLayer::timerEndFunc)),NULL);

	m_progressTimeBar->runAction(pAction);

	return true;
}

void CTimerLayer::update( float dt )
{
	CCProgressFromTo *progressToZero = CCProgressFromTo::create(20, 100, 0);
	CCFiniteTimeAction* pAction = CCSequence::create(progressToZero, CCCallFunc::create(this, callfunc_selector(CTimerLayer::timerEndFunc)),NULL);
	m_progressTimeBar->runAction(pAction);
}

void CTimerLayer::timerEndFunc()
{
	CCLog("Timer Ended!");
	//타이머가 끝난 후 취해질 액션
	CGameManager::GetInstance()->TimeOut();
}
