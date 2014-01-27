#pragma once
#include "cocos2d.h"
#include "config.h"
#include <array>

class CSettingOtherPlayerStatusLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	virtual void update();

	CREATE_FUNC(CSettingOtherPlayerStatusLayer);

private:
	cocos2d::CCSize m_VisibleSize;
	cocos2d::CCTextFieldTTF *PlayerStatus[MAX_PLAYER_NUM];
};