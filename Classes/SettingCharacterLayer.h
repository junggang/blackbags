#pragma once
#include "cocos2d.h"

class CSettingCharacterLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	virtual void update();
	CREATE_FUNC(CSettingCharacterLayer);

private:
	// ĳ���͸� ���������� �Ͼ�� ��
	void SelectCharacterCallBack(CCObject* pSender);
	void CreateCharacters();
};

