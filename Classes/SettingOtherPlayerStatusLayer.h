#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "config.h"
#include <array>

class CSettingOtherPlayerStatusLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	virtual void update();

	CREATE_FUNC(CSettingOtherPlayerStatusLayer);
    
private:
	void CreateStatusFrame(cocos2d::CCSize m_VisibleSize);
    
    void CreateEmptyFrame();
    void CreateOnlineEmptyPortrait();
    void CreateOfflineEmptyPortrait();
    
    void UpdatePlayerAndCharacterPairsOnline();
    void UpdatePlayerAndCharacterPairsOffline();
    
    void UpdateNamesToPlayerFrame();

	void PlayerActivateCallBack( CCObject* pSender );

	cocos2d::CCSize m_VisibleSize;
	cocos2d::CCLabelTTF *PlayerNames[MAX_PLAYER_NUM];
	cocos2d::CCMenuItemImage* m_PlayerStatusFrame[MAX_PLAYER_NUM];

};