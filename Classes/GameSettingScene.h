#pragma once
#include "cocos2d.h"
// include this layers for UPDATE function
#include "SettingCharacterLayer.h"
#include "SettingOtherPlayerStatusLayer.h"
#include "PlayerNumberAndMapSizeLayer.h"
#include "StartAndHelpButtonLayer.h"

class CGameSettingScene : public cocos2d::CCScene
{
public:
	virtual bool init(void);
	virtual void update(float dt);
	void AddSceondStepLayers();

	// implement the "static node()" method manually
	CREATE_FUNC(CGameSettingScene);
private:
	bool isSceondStep;

	CSettingCharacterLayer* m_SettingCharacterLayer;
	CSettingOtherPlayerStatusLayer* m_OtherPlayerStatusLayer;
	CPlayerNumberAndMapSizeLayer* m_PlayerNumberAndMapSizeLayer;
	CStartAndHelpButtonLayer* m_StartAndHelpButtonLayer;
};

