#include "TimerLayer.h"

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

	m_progressTimeBar->setPosition( ccp(m_VisibleSize.width/2, m_VisibleSize.height-100.0f));

	m_progressTimeBar->setScale(m_VisibleSize.width/3.65/timer->getContentSize().width);
	m_progressTimeBar->setPercentage(100.f);
	m_progressTimeBar->setMidpoint(ccp(0, 0.5));   
	m_progressTimeBar->setBarChangeRate(ccp(1, 0));
	m_progressTimeBar->setType(kCCProgressTimerTypeRadial);

	this->addChild(m_progressTimeBar,0);


	//시작하면서 한 번 업데이트 해야되는데.
	CCProgressFromTo *progressToZero = CCProgressFromTo::create(20, 100, 0);
	m_progressTimeBar->runAction(progressToZero);

}

void CTimerLayer::update( float dt )
{
	CCProgressFromTo *progressToZero = CCProgressFromTo::create(20, 100, 0);
	m_progressTimeBar->runAction(progressToZero);
}
