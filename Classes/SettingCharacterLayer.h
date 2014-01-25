#pragma once
#include "cocos2d.h"

class CSettingCharacterLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	CREATE_FUNC(CSettingCharacterLayer);

private:
	// 캐릭터를 선택했을떄 일어나는 일
	void SelectCharacterCallBack(CCObject* pSender);

};

