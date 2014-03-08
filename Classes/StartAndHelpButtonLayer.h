#pragma once
#include "cocos2d.h"

class CStartAndHelpButtonLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	void update();

	// implement the "static node()" method manually
    CREATE_FUNC(CStartAndHelpButtonLayer);

	// Online Mode :: StartButtonCallBack & m_StartButton == Ready Logic
private:
	void StartButtonCallBack( CCObject* pSender );
	void ReadyButtonCallBack( CCObject* pSender );
	cocos2d::CCMenuItemImage *m_StartButton;
};
