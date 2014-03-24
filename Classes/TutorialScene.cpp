#include "TutorialScene.h"
#include "BackgroundLayer.h"
#include "TutorialBoardLayer.h"
#include "GameManager.h"
USING_NS_CC;

bool CTutorialScene::init(void)
{
	//////////////////////////////
    // 1. super init first
	if ( !CCScene::init() )
    {
        return false;
    }
    
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    //1.background
    CCLayer* BackgroundLayer = CBackgroundLayer::create();
    this->addChild(BackgroundLayer, 0);
    
    //2.title
    CCSprite* TutorialTitle = CCSprite::create(TUTORIAL_TITLE.c_str());
    TutorialTitle->setAnchorPoint(ccp(0,0));
    TutorialTitle->setPosition(CCPoint(TUTORIAL_TITLE_POS));
    addChild(TutorialTitle,0);
    
    
	//3.add custom backBtn
	CCMenuItemImage *pBackToMainButton = CCMenuItemImage::create(
                                                                 SHARED_BTN_BACK.c_str(),
                                                                 SHARED_BTN_BACK.c_str(),
                                                                 this,
                                                                 menu_selector(CTutorialScene::SettingSceneCallback)
                                                                 );
    
	pBackToMainButton->setAnchorPoint(ccp(0,0));
	CCMenu* pMenu = CCMenu::create(pBackToMainButton, NULL);
	pMenu->setPosition(SHARED_BTN_BACK_POS);
	addChild(pMenu, 2);
    
    //4.add board layer
    CCLayer* BoardLayer = CTutorialBoardLayer::create();
    this->addChild(BoardLayer, 1);


    return true;
}

void CTutorialScene::update(float dt)
{
    
}

void CTutorialScene::SettingSceneCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
    //go back to SettingScene
}


