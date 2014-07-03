#include "SimpleSettingMenuLayer.h"
#include "MainScene.h"
#include "GameManager.h"
#include "CreditScene.h"
#include "LayerWebView.h"
#include "TutorialScene.h"
#include "ContactScene.h"

USING_NS_CC;

const float DEFAULT_BGM_VOLUME = 0.8f;
const float DEFAULT_SE_VOLUME = 0.8f;

const int BGM_SLIDER_TAG = 1;
const int SE_SLIDER_TAG = 2;

bool CSimpleSettingMenuLayer::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	/////////////////////////////
	// 2. add menus
	
	//add backgroundImg
	CCSprite* pBackground = CCSprite::create(SETTING_BG.c_str());
	pBackground->setAnchorPoint(ccp(0,0));
	pBackground->setPosition(CCPoint(SETTING_BG_POS));
	addChild(pBackground,0);

	CCSprite* pSound = CCSprite::create(SETTING_MENU_SOUND.c_str());
	pSound->setAnchorPoint(ccp(0,0));
	pSound->setPosition(CCPoint(SETTING_MENU_SOUND_POS));
	addChild(pSound,1);
    
    CCSprite* pMusicIcon = CCSprite::create(SETTING_ICON_MUSIC.c_str());
	pMusicIcon->setAnchorPoint(ccp(0,0));
	pMusicIcon->setPosition(CCPoint(SETTING_ICON_MUSIC_POS));
	addChild(pMusicIcon,1);
    
    CCSprite* pSoundIcon = CCSprite::create(SETTING_ICON_SOUND.c_str());
	pSoundIcon->setAnchorPoint(ccp(0,0));
	pSoundIcon->setPosition(CCPoint(SETTING_ICON_SOUND_POS));
	addChild(pSoundIcon,1);
    
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
    
    
    // set BGM & SE slider to current volume
    showCurrentBGMVolume();
    showCurrentSEVolume();
    
    m_previousSEvolume = CAudioManager::GetInstance()->GetSEVolume();
    
    return true;
}

void CSimpleSettingMenuLayer::update( float dt )
{
    
}

bool CSimpleSettingMenuLayer::IsSEVolumeChanged()
{
    if(m_previousSEvolume == CAudioManager::GetInstance()->GetSEVolume())
    {
        return false;
    }
    else
    {
        m_previousSEvolume = CAudioManager::GetInstance()->GetSEVolume();
        return true;
    }
}

void CSimpleSettingMenuLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CGameManager::GetInstance()->SetUpdateFlag(true);
    
    // update Music & SE Volume
	CAudioManager::GetInstance()->SetBGMVolume( getCurrentBGMVolume() );
	CAudioManager::GetInstance()->SetSEVolume( getCurrentSEVolume() );
    
    if ( IsSEVolumeChanged() )
    {
        CAudioManager::GetInstance()->ChangeSE(SE_DRAW_LINE_1);
        CAudioManager::GetInstance()->PlaySE();
    }
}

bool CSimpleSettingMenuLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void CSimpleSettingMenuLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void CSimpleSettingMenuLayer::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);

	CCLayer::onEnter();
}

void CSimpleSettingMenuLayer::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

	CCLayer::onExit();
}