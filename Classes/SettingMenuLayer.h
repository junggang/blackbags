#pragma once
#include "cocos2d.h"
#include "GUI\CCControlExtension\CCControlSlider.h"

class CSettingMenuLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	// a selector callback
	void FacebookLoginCallback(CCObject* pSender);
	void TutorialCallback(CCObject* pSender);
	void CreditCallback(CCObject* pSender);
	void mainSceneCallback(CCObject* pSender);

	// implement the "static node()" method manually
    CREATE_FUNC(CSettingMenuLayer);
private:
	cocos2d::extension::CCControlSlider *m_pBGMVolume;
	cocos2d::extension::CCControlSlider *m_pSEVolume;
};

