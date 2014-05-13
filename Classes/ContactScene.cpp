#include "ContactScene.h"
#include "config.h"
#include "BackgroundLayer.h"
#include "AdMobObjectCPP.h"

USING_NS_CC;

bool CContactScene::init(void)
{
	//////////////////////////////
    // 1. super init first
	if ( !CCScene::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    // 광고 끄기
    gene::AdMobObjectCPP * admob = new gene::AdMobObjectCPP();
    admob->hideAdMob();
    
	/////////////////////////////
    // 2. add layers
	CCLayer* BackgroundLayer = CBackgroundLayer::create();
	this->addChild(BackgroundLayer, 0);
    
    CCSprite* ContactTitle = CCSprite::create(CONTACT_TITLE.c_str());
    ContactTitle->setAnchorPoint(ccp(0,0));
    ContactTitle->setPosition(CCPoint(CONTACT_TITLE_POS));
    addChild(ContactTitle,0);

    //add backgroundImg
	CCSprite* pBackground = CCSprite::create(SETTING_BG.c_str());
	pBackground->setAnchorPoint(ccp(0,0));
	pBackground->setPosition(CCPoint(SETTING_BG_POS));
	addChild(pBackground,1);
    
    //add mail
    CCSprite* pMail = CCSprite::create(CONTACT_MAIL.c_str());
	pMail->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	addChild(pMail,1);
    
    //add custom backBtn
	CCMenuItemImage *pBackToMainButton = CCMenuItemImage::create(
         SHARED_BTN_BACK.c_str(),
         SHARED_BTN_BACK.c_str(),
         this,
         menu_selector(CContactScene::SettingSceneCallback)
         );
    
	pBackToMainButton->setAnchorPoint(ccp(0,0));
	CCMenu* pMenu = CCMenu::create(pBackToMainButton, NULL);
	pMenu->setPosition(SHARED_BTN_BACK_POS);
	addChild(pMenu, 1);
    
    
    
    
	return true;
}

void CContactScene::SettingSceneCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
    //go back to SettingScene
}

