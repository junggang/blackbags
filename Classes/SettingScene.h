#pragma once
#include "cocos2d.h"
#include "SettingMenuLayer.h"

class CSettingScene : public cocos2d::CCScene
{
public:
	virtual bool init(void);

	virtual void update(float dt);
	// implement the "static node()" method manually
    CREATE_FUNC(CSettingScene);

private:
	CSettingMenuLayer* m_SettingMenuLayer;
};
