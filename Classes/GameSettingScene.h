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
		setting scene �ܰ迡�� �����ϴ� ���̾�� �ϳ��� �� ��
		ǥ���� ���� �پ��ϸ� ������ ���̾� ������ child�� �߰�
		������ ���⼭�� �������� ���̾ �������� �ʿ��ϰ� ���ǿ� ���� �ٲ��־�� �ϴµ�
		������ ���¿��� �����Ǵ� ���̾��� ���ᳪ ���� �޶����� �����ϱ� ����� ����
	*/

	CSettingCharacterLayer* m_SettingCharacterLayer;
	CSettingOtherPlayerStatusLayer* m_OtherPlayerStatusLayer;
	cocos2d::CCLayer* m_PlayerNumberAndMapSizeLayer;
	CStartAndHelpButtonLayer* m_StartAndHelpButtonLayer;
};

