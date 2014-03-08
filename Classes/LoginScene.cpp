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
#include "BackgroundLayer.h"


USING_NS_CC;

bool CLoginScene::init(void)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCScene::init() )
	{
		return false;
	}
    
    CCLayer* BackgroundLayer = CBackgroundLayer::create();
	this->addChild(BackgroundLayer, 0);
    
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
            
            //this->removeAllChildren();
            if (nullptr != m_LoginLayer)
            {
                static_cast<LayerWebView *>(m_LoginLayer)->close();
                this->removeChild(m_LoginLayer);
            }
            
            // next scene gogo
            // 바로 바로 씬 전환을 시도하면 에러 발생 - 전환되는 시간 을 좀 두는 방식으로 일단 해결 시도
            float delayTime = 1.5;
            CCCallFunc* readyRequestCallback = CCCallFunc::create(this, callfunc_selector(CLoginScene::closeScene) );
            CCDelayTime* delayAction = CCDelayTime::create(delayTime);
            this->runAction(CCSequence::create(delayAction, readyRequestCallback, NULL));
            
            break;
        }
        case LP_WAITING:
        {
            break;
        }
    }
}

void CLoginScene::closeScene()
{
    CCScene* newScene = CGameSettingScene::create();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
}