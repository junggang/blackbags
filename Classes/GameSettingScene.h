#pragma once
#include "cocos2d.h"
// include this layers for UPDATE function
#include "SettingCharacterLayer.h"
#include "SettingOtherPlayerStatusLayer.h"
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

	NetworkPhase m_CurrentPhase;
	cocos2d::CCLayer* m_CurrentLayer;

	/*
		setting scene 단계에서 유지하는 레이어는 하나만 둘 것
		표시할 것이 다양하면 현재의 레이어 하위에 child로 추가
		이유는 여기서는 보여지는 레이어가 여러개가 필요하고 조건에 따라서 바꿔주어야 하는데
		각각의 상태에서 유지되는 레이어의 종료나 수가 달라지면 제어하기 힘들기 때문
	*/

	CSettingCharacterLayer* m_SettingCharacterLayer;
	CSettingOtherPlayerStatusLayer* m_OtherPlayerStatusLayer;
	cocos2d::CCLayer* m_PlayerNumberAndMapSizeLayer;
	CStartAndHelpButtonLayer* m_StartAndHelpButtonLayer;
};

