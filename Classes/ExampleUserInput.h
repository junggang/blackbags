#pragma once
#include "cocos2d.h"
#include "SettingMapLayer.h"
#include "SettingCharacterLayer.h"
#include "SettingOtherPlayerStatusLayer.h"

class CGameSettingScene : public cocos2d::CCScene
{
public:
	virtual bool init(void);
	virtual void update(float dt);

	// implement the "static node()" method manually
	CREATE_FUNC(CGameSettingScene);

private:
	CSettingCharacterLayer* SettingCharacterLayer;
	CSettingMapLayer* SettingMapLayer;
	CSettingOtherPlayerStatusLayer* OtherPlayerStatusLayer;
};

