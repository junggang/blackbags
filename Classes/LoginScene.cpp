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
    
	// send request for authentication
    CGameManager::GetInstance()->AuthenticationCheck();
    
    m_LoginLayer = nullptr;
    
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