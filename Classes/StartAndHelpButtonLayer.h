#pragma once
#include "cocos2d.h"

class CStartAndHelpButtonLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	void update();

	// implement the "static node()" method manually
    CREATE_FUNC(CStartAndHelpButtonLayer);

private:
	void StartButtonCallBack( CCObject* pSender );
	void HelpButtonCallBack( CCObject* pSender );
	void NameInputButtonCallBack( CCObject* pSender );

	cocos2d::CCMenuItemImage *m_StartButton;
};
