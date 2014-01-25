#pragma once
#include "cocos2d.h"

class CStartAndHelpButtonLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	// implement the "static node()" method manually
    CREATE_FUNC(CStartAndHelpButtonLayer);

private:
	void StartButtonCallBack(CCObject* pSender);
	void HelpButtonCallBack( CCObject* pSender );
};
