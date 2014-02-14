#pragma once
#include "cocos2d.h"
#include "config.h"
#include "PlayerNumberAndMapSizeLayer.h"
#include "NetworkPlayerNumberLayer.h"

class CSettingFirstStepLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(CSettingFirstStepLayer);

private:
	CPlayerNumberAndMapSizeLayer* m_SingleLayer;
	CNetworkPlayerNumberLayer* m_NetworkLayer;
};