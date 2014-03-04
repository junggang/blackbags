#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "config.h"
#include <array>

class CSettingOtherPlayerStatusLayer : public cocos2d::CCLayer,
	public cocos2d::extension::CCEditBoxDelegate
{
public:
	virtual bool init();
	virtual void update();

	CREATE_FUNC(CSettingOtherPlayerStatusLayer);

	// functions for edit Player Name
	virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);

private:
	void CreateStatusFrame(cocos2d::CCSize m_VisibleSize);

	void PlayerActivateCallBack( CCObject* pSender );

	cocos2d::CCSize m_VisibleSize;
	cocos2d::CCTextFieldTTF *PlayerNames[MAX_PLAYER_NUM];
	cocos2d::CCMenuItemImage* m_PlayerStatusFrame[MAX_PLAYER_NUM];

};