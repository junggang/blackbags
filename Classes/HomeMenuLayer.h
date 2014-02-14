#pragma once
#include "cocos2d.h"

class CHomeMenuLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	// a selector callback
	void homeMenuCallback(CCObject* pSender);
	void homeIconCallback(CCObject* pSender);
	void ResumeIconCallback(CCObject* pSender);
	void OptionIconCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(CHomeMenuLayer);

private:
	cocos2d::CCSprite* m_backLayer;
	cocos2d::CCMenu* m_iconResume;
	cocos2d::CCMenu* m_iconHome;
	cocos2d::CCMenu* m_iconOption;
};

