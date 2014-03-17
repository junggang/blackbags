//
//  LayerWebView.mm
//  MyApp1
//
//  Created by DAC-TOAN HO on 11-10-10.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "LayerWebView.h"
#include "UIWebViewBridge.h"
#include "MainScene.h"
#include "GameManager.h"

USING_NS_CC;

static UIWebViewBridge *gUIWebViewBridge = nil;

bool LayerWebView::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    gUIWebViewBridge = [[UIWebViewBridge alloc] init];
    [gUIWebViewBridge setLayerWebView : this];
    return true;
}

void LayerWebView::webViewDidFinishLoad(std::string newToken)
{
    // 토큰 값 가져와서 저장하고
    CGameManager::GetInstance()->SetTokenId(newToken);
    
    // 현재 떠있는 웹페이지 종료시키기
    // 플래그 설정을 해서 씬에서 이 레이어를 삭제하도록
    CGameManager::GetInstance()->SetCurrentLoginPhase(LP_OK);
    CGameManager::GetInstance()->SetUpdateFlag(true);
    CGameManager::GetInstance()->GetGoogleNick();
}

void LayerWebView::close()
{
    [gUIWebViewBridge releaseResource];
    [gUIWebViewBridge dealloc];
}