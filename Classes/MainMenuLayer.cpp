#include "MainMenuLayer.h"
#include "SettingScene.h"
#include "CreditScene.h"
#include "GameManager.h"
#include "GameSettingScene.h"
#include "LoginScene.h"
//for test
#include "NetworkLogic.h"

USING_NS_CC;

bool CMainMenuLayer::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	/////////////////////////////
	// 2. add a background image
	CCMenu* pMenu = nullptr;

	CCMenuItemImage *pOnTable = CCMenuItemImage::create(
										SHARED_MENU1_UNSELECTED.c_str(),
										SHARED_MENU1_SELECTED.c_str(),
										this,
										menu_selector(CMainMenuLayer::newgameCallback)
										);
    
	CCSprite* pMenuImg01 = CCSprite::create(MAIN_MENU1_IMG.c_str());
	pMenuImg01->setPosition(CCPoint(MAIN_MENU1_IMG_POS));
	pMenuImg01->setAnchorPoint(ccp(0,0));
	addChild(pMenuImg01,3);

	pOnTable->setAnchorPoint(ccp(0,0));
	pOnTable->setPosition(CCPoint(MAIN_MENU1_POS) );

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pOnTable, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	CCMenuItemImage *pOnLine = CCMenuItemImage::create(
										SHARED_MENU2_UNSELECTED.c_str(),
										SHARED_MENU2_SELECTED.c_str(),
										this,
										menu_selector(CMainMenuLayer::multiplayCallback)
										);
    
	CCSprite* pMenuImg02 = CCSprite::create(MAIN_MENU2_IMG.c_str());
	pMenuImg02->setPosition(CCPoint(MAIN_MENU2_IMG_POS));
	pMenuImg02->setAnchorPoint(ccp(0,0));
	addChild(pMenuImg02,3);

	pOnLine->setAnchorPoint(ccp(0,0));
	pOnLine->setPosition(CCPoint(MAIN_MENU2_POS));

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pOnLine, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	CCMenuItemImage *pSetting = CCMenuItemImage::create(
										SHARED_MENU3_UNSELECTED.c_str(),
										SHARED_MENU3_SELECTED.c_str(),
										this,
										menu_selector(CMainMenuLayer::settingCallback)
										);

	CCSprite* pMenuImg03 = CCSprite::create(MAIN_MENU3_IMG.c_str());
	pMenuImg03->setPosition(CCPoint(MAIN_MENU3_IMG_POS));
	pMenuImg03->setAnchorPoint(ccp(0,0));
	addChild(pMenuImg03,3);

	pSetting->setAnchorPoint(ccp(0,0));
	pSetting->setPosition(CCPoint(MAIN_MENU3_POS));

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pSetting, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	//create menu title
	CCSprite* pMenuTitle = CCSprite::create(MAIN_MENU_TITLE.c_str());
	pMenuTitle->setPosition(CCPoint(MAIN_MENU_TITLE_POS));
	pMenuTitle->setAnchorPoint(ccp(0,0));
	addChild(pMenuTitle,3);
    
    //create particle animation
    CCParticleSystem* m_star0 = CCParticleFlower::create();
    m_star0->retain();
    m_star0->setStartSize(50.0f);
    m_star0->setEmissionRate(20.0f);
    m_star0->setLife(1.0f);
    m_star0->setDuration(INFINITY);
    m_star0->setPosition(pMenuImg01->getPosition());
    m_star0->setTexture( CCTextureCache::sharedTextureCache()->addImage("image/particle-star.png"));
    addChild(m_star0,2);

    CCParticleSystem* m_star1 = CCParticleFlower::create();
    m_star1->retain();
    m_star1->setStartSize(50.0f);
    m_star1->setEmissionRate(20.0f);
    m_star1->setLife(1.0f);
    m_star1->setDuration(INFINITY);
    m_star1->setPosition(CCPoint(MAIN_MENU2_IMG_POS));
    m_star1->setTexture( CCTextureCache::sharedTextureCache()->addImage("image/particle-star.png"));
    addChild(m_star1,2);
    
    CCParticleSystem* m_star2 = CCParticleFlower::create();
    m_star2->retain();
    m_star2->setStartSize(50.0f);
    m_star2->setEmissionRate(20.0f);
    m_star2->setLife(1.0f);
    m_star2->setDuration(INFINITY);
    m_star2->setPosition(CCPoint(MAIN_MENU1_IMG_POS));
    m_star2->setTexture( CCTextureCache::sharedTextureCache()->addImage("image/particle-star.png"));
    addChild(m_star2,2);
    
	return true;
}

void CMainMenuLayer::newgameCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	//newgame load
    CGameManager::GetInstance()->SetOnlineMode(false);
    
	CCScene* newScene = CGameSettingScene::create();
	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5, newScene) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
#endif
}

void CMainMenuLayer::multiplayCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CGameManager::GetInstance()->SetOnlineMode(true);
	CGameManager::GetInstance()->InitNetworkLogic();
    CGameManager::GetInstance()->SetConnectionStatus(true);

    CCScene* newScene = CLoginScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
#endif
}

void CMainMenuLayer::settingCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	//for test
	CCScene* newScene = CSettingScene::create();
	CCDirector::sharedDirector()->pushScene( newScene );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
#endif
}