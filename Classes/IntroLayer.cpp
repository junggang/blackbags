#include "IntroLayer.h"
#include "MainScene.h"
#include "config.h"

USING_NS_CC;

bool CIntroLayer::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    /////////////////////////////
	// 2. add a background image
	
	CCSprite* pLogo = CCSprite::create(INTRO_LOGO.c_str());
	pLogo->setAnchorPoint(ccp(0,0));

	pLogo->setPosition(CCPoint(INTRO_LOGO_POS));
	this->addChild(pLogo, 0);

	this->schedule(schedule_selector(CIntroLayer::endIntro),1.0f);
    
	return true;
}

void CIntroLayer::endIntro(float dt)
{
	CCScene* newScene = CMainScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
}
