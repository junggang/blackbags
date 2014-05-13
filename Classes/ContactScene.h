#pragma once
#include "cocos2d.h"

class CContactScene : public cocos2d::CCScene
{
public:
	virtual bool init(void);
    
    void SettingSceneCallback(CCObject* pSender);
    
	// implement the "static node()" method manually
    CREATE_FUNC(CContactScene);
};
