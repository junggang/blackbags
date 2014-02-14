#pragma once
#include "cocos2d.h"

// CCIMEDelegate 상속 (키보드 호출을 위해)
class CPlayerNameSettingLayer : public cocos2d::CCLayer, public cocos2d::CCIMEDelegate
{
public:
	virtual bool init();

	CREATE_FUNC(CPlayerNameSettingLayer);

	void ShowKeyboard(cocos2d::CCIMEKeyboardNotificationInfo & info);
	void HideKeyboard(cocos2d::CCIMEKeyboardNotificationInfo & info);

	void TouchKeyboard(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
};