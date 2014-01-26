#include "SettingTitleLayer.h"

USING_NS_CC;

bool CSettingTitleLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// get Windows Size
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	// Create sprite
	CCSprite* pTitle = CCSprite::create("image/SETTING_title.png");

	// Title Position : X Center + Y
	pTitle->setPosition(ccp(visibleSize.width/2, visibleSize.height - pTitle->getContentSize().height) );
	this->addChild(pTitle, 0);

	return true;
}