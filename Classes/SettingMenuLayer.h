#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "AudioManager.h"

class LayerWebView;

class CSettingMenuLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	// a selector callback
	void GoogleLoginCallback(CCObject* pSender);
	void TutorialCallback(CCObject* pSender);
	void CreditCallback(CCObject* pSender);
    void ContactCallback(CCObject* pSender);

	float getCurrentBGMVolume() { return m_pBGMVolume->getValue(); };
	float getCurrentSEVolume() { return m_pSEVolume->getValue(); };
    void showCurrentBGMVolume() { m_pBGMVolume->setValue(CAudioManager::GetInstance()->GetBGMVolume()); }
    void showCurrentSEVolume() { m_pSEVolume->setValue(CAudioManager::GetInstance()->GetSEVolume()); }
    
	virtual void update(float dt);

	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	// implement the "static node()" method manually
    CREATE_FUNC(CSettingMenuLayer);
    
private:
    bool IsSEVolumeChanged();
    
	cocos2d::extension::CCControlSlider *m_pBGMVolume;
	cocos2d::extension::CCControlSlider *m_pSEVolume;
    cocos2d::CCMenu* m_pLoginMenu;
    LayerWebView* m_LoginLayer;
    std::string m_Name;
    
    float m_previousSEvolume;
};

