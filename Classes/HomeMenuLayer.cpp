#include "HomeMenuLayer.h"
#include "MainScene.h"
#include "config.h"
#include "HelpScene.h"
#include "GameSettingScene.h"
#include "HomeMenuPopUp.h"
#include "GameManager.h"

USING_NS_CC;

bool CHomeMenuLayer::init()
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

	CCMenuItemImage *pMenuIcon = CCMenuItemImage::create(
		SHARED_BTN_HOME.c_str(),
		SHARED_BTN_HOME.c_str(),
		this,
		menu_selector(CHomeMenuLayer::homeMenuCallback)
		);

	pMenuIcon->setPosition(ccp(0,0));
    pMenuIcon->setAnchorPoint(ccp(0,0));

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pMenuIcon, NULL);
	pMenu->setPosition(CCPoint(SHARED_BTN_HOME_POS));
	this->addChild(pMenu, 1);
	return true;
}

void CHomeMenuLayer::homeMenuCallback(CCObject* pSender)
{
    /*
        결과 버튼이 전체 화면을 덮어서 여기서 따로 처리할 필요없음
    if (CGameManager::GetInstance()->GetGameEndFlag())
        return;
    */
    
    if(IsOn)
    {
        CCDirector::sharedDirector()->resume();
        removeChildByTag(100);
        IsOn = false;
    }
    else
    {
        CCDirector::sharedDirector()->pause();
        CCLayer* popUp = CHomeMenuPopUp::create();
        addChild(popUp,1, 100);
        IsOn = true;
    }
}