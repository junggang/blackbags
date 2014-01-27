#pragma once
#include "cocos2d.h"

class CSettingScene : public cocos2d::CCScene
{
public:
	virtual bool init(void);

	// implement the "static node()" method manually
    CREATE_FUNC(CSettingScene);
};
