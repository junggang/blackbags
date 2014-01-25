#pragma once
#include "cocos2d.h"

class CSettingMapLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	virtual void update(void);

	CREATE_FUNC(CSettingMapLayer);

private:
	void SelectMapCallBack(CCObject* pSender);

	cocos2d::CCSprite* pCheck;
	cocos2d::CCMenuItemImage *pMapSelect1;
	cocos2d::CCMenuItemImage *pMapSelect2;
};