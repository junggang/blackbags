#include "SettingMenuLayer.h"
#include "MainScene.h"
#include "GameManager.h"

USING_NS_CC;

const float DEFAULT_BGM_VOLUME = 0.8f;
const float DEFAULT_SE_VOLUME = 0.8f;

const int BGM_SLIDER_TAG = 1;
const int SE_SLIDER_TAG = 2;

bool CSettingMenuLayer::init()
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
	// 2. add menus
	CCMenuItemImage *pBackToMainButton = CCMenuItemImage::create(
										"image/MAIN_exit.png",
										"image/MAIN_exit_selected.png",
										this,
										menu_selector(CSettingMenuLayer::MainSceneCallback)
										);
    
	CCMenuItemImage *pFacebookLoginButton = CCMenuItemImage::create(
										"image/LOGIN_WITH_FACEBOOK.png",
										"image/LOGIN_WITH_FACEBOOK.png",
										this,
										menu_selector(CSettingMenuLayer::GoogleLoginCallback)
										);

	m_pBGMVolume = extension::CCControlSlider::create("image/BAR_BACKGROUND.png", "image/BAR_PROGRESS.png", "image/BAR_THUMB.png");
	m_pSEVolume = extension::CCControlSlider::create("image/BAR_BACKGROUND.png", "image/BAR_PROGRESS.png", "image/BAR_THUMB.png");

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(NULL, NULL);

	pMenu->addChild(pFacebookLoginButton);

	this->addChild(m_pBGMVolume);
	this->addChild(m_pSEVolume);

	// set BGM slider
	m_pBGMVolume->setPosition( ccp(pMenu->getPositionX(), 100) );
	m_pBGMVolume->setMaximumAllowedValue(1.0);
	m_pBGMVolume->setMaximumValue(1.0);
	m_pBGMVolume->setMinimumAllowedValue(0.0);
	m_pBGMVolume->setMinimumValue(0.0);
	m_pBGMVolume->setValue(DEFAULT_BGM_VOLUME);
	m_pBGMVolume->setTag(BGM_SLIDER_TAG);

	// set SE slider
	m_pSEVolume->setPosition( ccp(pMenu->getPositionX(), 150) );
	m_pSEVolume->setMaximumAllowedValue(1.0);
	m_pSEVolume->setMaximumValue(1.0);
	m_pSEVolume->setMinimumAllowedValue(0.0);
	m_pSEVolume->setMinimumValue(0.0);
	m_pSEVolume->setValue(DEFAULT_SE_VOLUME);
	m_pSEVolume->setTag(SE_SLIDER_TAG);

	pMenu->addChild(pBackToMainButton);

	pMenu->alignItemsVertically();

	this->addChild(pMenu);
    
	return true;
}

void CSettingMenuLayer::MainSceneCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->popScene();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
#endif
}

void CSettingMenuLayer::GoogleLoginCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	//Logic

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}

void CSettingMenuLayer::update( float dt )
{
	
}

void CSettingMenuLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CGameManager::GetInstance()->SetUpdateFlag(true);
}

bool CSettingMenuLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void CSettingMenuLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void CSettingMenuLayer::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);

	CCLayer::onEnter();
}

void CSettingMenuLayer::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

	CCLayer::onExit();
}
