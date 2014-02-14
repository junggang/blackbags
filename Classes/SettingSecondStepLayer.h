#pragma once
#include "cocos2d.h"
#include "config.h"
#include "SettingTitleLayer.h"
#include "SettingCharacterLayer.h"
#include "StartAndHelpButtonLayer.h"
#include "SettingOtherPlayerStatusLayer.h"

class CSettingSecondStepLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(CSettingSecondStepLayer);

private:
	CSettingTitleLayer* m_SettingTitleLayer;
	CSettingCharacterLayer* m_SettingCharacterLayer;
	CStartAndHelpButtonLayer* m_StartAndHelpButtonLayer;
	CSettingOtherPlayerStatusLayer* m_OtherPlayerStatusLayer;
};