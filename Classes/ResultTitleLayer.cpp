#include "ResultTitleLayer.h"
#include "MainScene.h"

USING_NS_CC;

bool CResultTitleLayer::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a background image *** 일단 레이아웃은 임의로 잡습니다 ***

	//title part
    CCSprite* pTitle = CCSprite::create("image/RESULT_result.png");
	pTitle->setPosition(ccp(pTitle->getContentSize().width/2, visibleSize.height - pTitle->getContentSize().height) );
	this->addChild(pTitle, 0);
 
	//finish button part
	CCMenuItemImage *pMainScene = CCMenuItemImage::create(
										"image/RESULT_finish.png",
										"image/RESULT_finish_selected.png",
										this,
										menu_selector(CResultTitleLayer::mainSceneCallback)
										);
   
	pMainScene->setPosition(ccp(visibleSize.width - pTitle->getContentSize().width, pTitle->getContentSize().height) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pMainScene, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	return true;
}

void CResultTitleLayer::mainSceneCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCScene* newScene = CMainScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}