#pragma once
#include "cocos2d.h"

class CHomeMenuPopUp : public cocos2d::CCLayer
{
public:
	virtual bool init();

	// a selector callback
	void homeMenuCallback(CCObject* pSender);
	void ResumeIconCallback(CCObject* pSender);
	void HelpIconCallback(CCObject* pSender);
	void SettingIconCallback(CCObject* pSender);
	void QuitIconCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(CHomeMenuPopUp);

private:
	cocos2d::CCSprite* m_backLayer;
	cocos2d::CCMenu* m_iconResume;
	cocos2d::CCMenu* m_iconHelp;
	cocos2d::CCMenu* m_iconSetting;
	cocos2d::CCMenu* m_iconQuit;

};

