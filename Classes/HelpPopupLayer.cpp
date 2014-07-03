#include "HelpPopuplLayer.h"
#include "config.h"

USING_NS_CC;

bool CHelpPopupLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize m_VisibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
	CCSprite* LayerFullPage = CCSprite::create(SHARED_POPUP_BG.c_str());
    CCSprite* helpTitle = CCSprite::create(SHARED_POPUP_HELP_TITLE.c_str());
    CCSprite* helpContents = CCSprite::create(SHARED_POPUP_HELP_CON.c_str());
    
	if ( LayerFullPage != NULL )
	{
        LayerFullPage->setAnchorPoint(CCPointZero);
		LayerFullPage->setPosition(CCPoint(SHARED_POPUP_BG_POS));
		this->addChild(LayerFullPage);
	}
    if ( helpTitle != NULL )
	{
        helpTitle->setAnchorPoint(CCPointZero);
		helpTitle->setPosition(CCPoint(SHARED_POPUP_HELP_TITLE_POS));
		this->addChild(helpTitle);
	}
    if ( helpContents != NULL )
	{
        helpContents->setAnchorPoint(CCPointZero);
		helpContents->setPosition(CCPoint(SHARED_POPUP_HELP_CON_POS));
		this->addChild(helpContents);
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
    this->removeAllChildrenWithCleanup(true);
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
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    onExit();
}
