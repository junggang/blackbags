#include "IntroLayer.h"
#include "MainScene.h"

USING_NS_CC;

bool CIntroLayer::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a background image
	
	CCSprite* pLogo = CCSprite::create("image/INTRO_logo.png");

	pLogo->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	this->addChild(pLogo, 0);

	this->schedule(schedule_selector(CIntroLayer::endIntro),1.0f);
    
	return true;
}

void CIntroLayer::endIntro(float dt)
{
	CCScene* newScene = CMainScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
}
