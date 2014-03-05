//
//  LoginScene.cpp
//  MonsterScramble
//
//  Created by Gyeongwook on 2014. 3. 5..
//
//

#include "LoginScene.h"
#include "GameManager.h"
#include "LayerWebView.h"
#include "BackgroundLayer.h"
#include "GameSettingScene.h"


USING_NS_CC;

bool CLoginScene::init(void)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCScene::init() )
	{
		return false;
	}
    
	// init current network phase
	m_CurrentPhase = CGameManager::GetInstance()->GetCurrentLoginPhase();
    CGameManager::GetInstance()->AuthenticationCheck();
    
    m_LoginLayer = nullptr;
    
	/////////////////////////////
	// 2. add layers
	
	// background layer
	CCLayer* BackgroundLayer = CBackgroundLayer::create();
	this->addChild(BackgroundLayer, 0);
    
	// 2.1 add Player Number and Map Size Select layer
	//m_CurrentLayer = CSettingFirstStepLayer::create();
    CGameManager::GetInstance()->AuthenticationCheck();
    
	this->scheduleUpdate();
    
	return true;
}

void CLoginScene::update(float dt)
{
    switch (CGameManager::GetInstance()->GetCurrentLoginPhase() )
    {
        case LP_FAIL:
        {
            CGameManager::GetInstance()->SetCurrentLoginPhase(LP_WAITING);
            
            m_LoginLayer = LayerWebView::create();
            this->addChild(m_LoginLayer, 1);
            
            break;
        }
        case LP_OK :
        {
            CGameManager::GetInstance()->SetCurrentLoginPhase(LP_WAITING);
            static_cast<LayerWebView *>(m_LoginLayer)->close();
            this->removeAllChildren();
            
            // next scene gogo
            CCScene* newScene = CGameSettingScene::create();
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
            
            break;
        }
        case LP_WAITING:
        {
            break;
        }
    }
}