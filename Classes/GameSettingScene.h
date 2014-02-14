#pragma once
#include "cocos2d.h"
#include "config.h"

class CGameSettingScene : public cocos2d::CCScene
{
public:
	virtual bool init(void);
	virtual void update(float dt);

	// implement the "static node()" method manually
	CREATE_FUNC(CGameSettingScene);
private:
	NetworkPhase m_CurrentPhase;
	cocos2d::CCLayer* m_CurrentLayer;

	/*
		setting scene �ܰ迡�� �����ϴ� ���̾�� �ϳ��� �� ��
		ǥ���� ���� �پ��ϸ� ������ ���̾� ������ child�� �߰�
		������ ���⼭�� �������� ���̾ �������� �ʿ��ϰ� ���ǿ� ���� �ٲ��־�� �ϴµ�
		������ ���¿��� �����Ǵ� ���̾��� ���ᳪ ���� �޶����� �����ϱ� ����� ����
		�� ��
	*/
};

