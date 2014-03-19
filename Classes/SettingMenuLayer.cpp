#include "SettingMenuLayer.h"
#include "MainScene.h"
#include "GameManager.h"
#include "CreditScene.h"
#include "LayerWebView.h"
#include "TutorialScene.h"

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
    
	/////////////////////////////
	// 2. add menus
	
	CCMenu* pMenu = nullptr;
	
	//add backgroundImg
	CCSprite* pBackground = CCSprite::create(SETTING_BG.c_str());
	pBackground->setAnchorPoint(ccp(0,0));
	pBackground->setPosition(CCPoint(SETTING_BG_POS));
	addChild(pBackground,0);

	//add Menu Titles(google, name, sound, tutorial, credit)
    CCSprite* pGoogle = CCSprite::create(SETTING_MENU_GOOGLE.c_str());
	pGoogle->setAnchorPoint(ccp(0,0));
	pGoogle->setPosition(CCPoint(SETTING_MENU_GOOGLE_POS));
	addChild(pGoogle,1);
    
    CCLabelTTF* pName = nullptr;
    // 로그인 되어 있으면 로그인 되어 있는 계정 닉네임이 있어야 할 듯
    m_Name = CGameManager::GetInstance()->GetUsersName();
    if (strcmp(m_Name.c_str(), "no name") == 0) {
        // login button
        pName = CCLabelTTF::create("Login", GAME_FONT, 82 );
        pName->setColor(ccc3(183, 50, 35));
    }
    else
    {
        // google nick name
        pName = CCLabelTTF::create(m_Name.c_str(), GAME_FONT, 82 );
        pName->setColor(ccc3(43, 46, 46));
    }
    
    
    CCMenuItemLabel *pLogin = CCMenuItemLabel::create(
		pName,
		this,
		menu_selector(CSettingMenuLayer::GoogleLoginCallback)
		);
	pLogin->setAnchorPoint(ccp(0,0));
	m_pLoginMenu = CCMenu::create(pLogin, NULL);
	m_pLoginMenu->setPosition(SETTING_LOGIN_POS);
	addChild(m_pLoginMenu, 1);

	CCSprite* pSound = CCSprite::create(SETTING_MENU_SOUND.c_str());
	pSound->setAnchorPoint(ccp(0,0));
	pSound->setPosition(CCPoint(SETTING_MENU_SOUND_POS));
	addChild(pSound,1);

	CCMenuItemImage *pTutorial = CCMenuItemImage::create(
		SETTING_MENU_TUTORIAL.c_str(),
		SETTING_MENU_TUTORIAL.c_str(),
		this,
		menu_selector(CSettingMenuLayer::TutorialCallback)
		);
	pTutorial->setAnchorPoint(ccp(0,0));
	pMenu = CCMenu::create(pTutorial, NULL);
	pMenu->setPosition(SETTING_MENU_TUTORIAL_POS);
	addChild(pMenu, 1);

	CCMenuItemImage *pCredit = CCMenuItemImage::create(
		SETTING_MENU_CREDIT.c_str(),
		SETTING_MENU_CREDIT.c_str(),
		this,
		menu_selector(CSettingMenuLayer::CreditCallback)
		);
	pCredit->setAnchorPoint(ccp(0,0));
	pMenu = CCMenu::create(pCredit, NULL);
	pMenu->setPosition(SETTING_MENU_CREDIT_POS);
	addChild(pMenu, 1);

	

	m_pBGMVolume = extension::CCControlSlider::create(SETTING_BAR.c_str(),SETTING_BAR.c_str(),SETTING_CONTROLLER.c_str());
	m_pSEVolume = extension::CCControlSlider::create(SETTING_BAR.c_str(),SETTING_BAR.c_str(),SETTING_CONTROLLER.c_str());

	// create menu, it's an autorelease object
	addChild(m_pBGMVolume,1);
	addChild(m_pSEVolume,1);

	// set BGM slider
	m_pBGMVolume->setPosition( CCPoint(SETTING_MUSIC_BAR_POS) );
	m_pBGMVolume->setAnchorPoint(ccp(0,0));
	m_pBGMVolume->setMaximumAllowedValue(1.0);
	m_pBGMVolume->setMaximumValue(1.0);
	m_pBGMVolume->setMinimumAllowedValue(0.0);
	m_pBGMVolume->setMinimumValue(0.0);
	m_pBGMVolume->setValue(DEFAULT_BGM_VOLUME);
	m_pBGMVolume->setTag(BGM_SLIDER_TAG);

	// set SE slider
	m_pSEVolume->setPosition( CCPoint(SETTING_SOUND_BAR_POS));
	m_pSEVolume->setAnchorPoint(ccp(0,0));
	m_pSEVolume->setMaximumAllowedValue(1.0);
	m_pSEVolume->setMaximumValue(1.0);
	m_pSEVolume->setMinimumAllowedValue(0.0);
	m_pSEVolume->setMinimumValue(0.0);
	m_pSEVolume->setValue(DEFAULT_SE_VOLUME);
	m_pSEVolume->setTag(SE_SLIDER_TAG);
    
    m_LoginLayer = nullptr;

	return true;
}


void CSettingMenuLayer::GoogleLoginCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// Logic
    // webview 창하나 만들어서 로그인 시키자
    m_LoginLayer = LayerWebView::create();
    this->addChild(m_LoginLayer, 1);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}

void CSettingMenuLayer::TutorialCallback( CCObject* pSender )
{
    CCScene* newScene = CTutorialScene::create();
	CCDirector::sharedDirector()->pushScene( newScene );


}

void CSettingMenuLayer::CreditCallback( CCObject* pSender )
{
	CCScene* newScene = CCreditScene::create();
	CCDirector::sharedDirector()->pushScene( newScene );

}

void CSettingMenuLayer::update( float dt )
{
    /*
	if (CGameManager::GetInstance()->GetCurrentLoginPhase() == LP_OK)
    {
        if (nullptr != m_LoginLayer)
        {
            static_cast<LayerWebView *>(m_LoginLayer)->close();
            this->removeChild(m_LoginLayer);
        }
    }
     */
    
    std::string tempName = CGameManager::GetInstance()->GetUsersName();
    if (strcmp(m_Name.c_str(), tempName.c_str() ) != 0)
    {
        if (nullptr != m_LoginLayer)
        {
            static_cast<LayerWebView *>(m_LoginLayer)->close();
            this->removeChild(m_LoginLayer);
        }
        
        this->removeChild(m_pLoginMenu);
        
        m_Name = tempName;
        CCLabelTTF* pName = nullptr;
        if (strcmp(m_Name.c_str(), "no name") == 0) {
            // login button
            pName = CCLabelTTF::create("Login", GAME_FONT, 82 );
            pName->setColor(ccc3(183, 50, 35));
        }
        else
        {
            // google nick name
            pName = CCLabelTTF::create(m_Name.c_str(), GAME_FONT, 82 );
            pName->setColor(ccc3(43, 46, 46));
        }
        
        CCMenuItemLabel *pLogin = CCMenuItemLabel::create(
                                                          pName,
                                                          this,
                                                          menu_selector(CSettingMenuLayer::GoogleLoginCallback)
                                                          );
        pLogin->setAnchorPoint(ccp(0,0));
        m_pLoginMenu = CCMenu::create(pLogin, NULL);
        m_pLoginMenu->setPosition(SETTING_LOGIN_POS);
        addChild(m_pLoginMenu, 1);
    }
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