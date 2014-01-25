#pragma once
#include "cocos2d.h"
#include "SettingMapLayer.h"

class CGameSettingScene : public cocos2d::CCScene
{
public:
	virtual bool init(void);
	virtual void update(float dt);

	// implement the "static node()" method manually
	CREATE_FUNC(CGameSettingScene);

private:
	CSettingMapLayer* SettingMaplayer;
};

