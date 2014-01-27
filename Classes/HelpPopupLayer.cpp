#include "HelpPopuplLayer.h"

USING_NS_CC;

bool CHelpPopupLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	// 조심해!! Targeted touch 방식으로 구현해서 터치가 이 레이어를 벗어나지 않게 만들어야 해!!

	CCSize m_VisibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite* LayerFullPage = CCSprite::create("image/HelpLayerImage.png");

	if ( LayerFullPage != NULL )
	{
		LayerFullPage->setPosition( ccp(m_VisibleSize.width / 2, m_VisibleSize.height / 2) );
		this->addChild(LayerFullPage);
	}

	return true;
}

void CHelpPopupLayer::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -256, true);

	CCLayer::onEnter();
}

void CHelpPopupLayer::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

	CCLayer::onExit();
}


bool CHelpPopupLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent* event )
{
	return true;
}

void CHelpPopupLayer::ccTouchMoved( cocos2d::CCTouch *pTouch, cocos2d::CCEvent* event )
{

}

void CHelpPopupLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent* event )
{

}
