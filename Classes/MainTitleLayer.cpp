#include "MainTitleLayer.h"
#include "config.h"

USING_NS_CC;

bool CMainTitleLayer::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	/////////////////////////////
	CCSprite* pTitle = CCSprite::create(MAIN_TITLE.c_str());
	pTitle->setAnchorPoint(ccp(0,0));
	pTitle->setPosition(CCPoint(MAIN_TITLE_POS));
    this->addChild(pTitle, 1);
    
    CCSprite *pFlower0 = CCSprite::create("image/main_flower.png");
    pFlower0->setScale(1.2f);
    pFlower0->setPosition(ccp(1830,1380));
    addChild(pFlower0,0);
    
    CCSprite *pFlower1 = CCSprite::create("image/main_flower.png");
    pFlower1->setPosition(ccp(1758,1030));
    addChild(pFlower1,0);
    
    CCSprite *pFlower2 = CCSprite::create("image/main_flower.png");
    pFlower2->setScale(0.8f);
    pFlower2->setPosition(ccp(308,1403));
    addChild(pFlower2,0);
    
    CCSprite *pFlower3 = CCSprite::create("image/main_flower.png");
    pFlower3->setScale(1.3f);
    pFlower3->setPosition(ccp(178,1015));
    addChild(pFlower3,0);
    
    CCRepeatForever* rotate0 =CCRepeatForever::create(CCRotateBy::create(5.0f,360));
    CCRepeatForever* rotate1 =CCRepeatForever::create(CCRotateBy::create(7.0f,360));
    CCRepeatForever* rotate2 =CCRepeatForever::create(CCRotateBy::create(8.0f,360));
    CCRepeatForever* rotate3 =CCRepeatForever::create(CCRotateBy::create(4.0f,360));
    pFlower0->runAction(rotate0);
    pFlower1->runAction(rotate1);
    pFlower2->runAction(rotate2);
    pFlower3->runAction(rotate3);
    
    return true;
}

