#include "SettingTitleLayer.h"
#include "config.h"

USING_NS_CC;

bool CSettingTitleLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// get Windows Size
	// CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	// Create sprite
	CCSprite* pTitle = CCSprite::create(CHARACTER_SELECT_TITLE.c_str());
    
	// Title Position : X Center + Y
	pTitle->setPosition(CCPoint(GAME_SETTING_CHARACTER_SELECT_TITLE_POS));
  
    // set anchor point 0
    pTitle->setAnchorPoint(ccp(0,0));
    
	this->addChild(pTitle, 1);

	return true;
}