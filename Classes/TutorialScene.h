#pragma once
#include "cocos2d.h"

class CTutorialScene : public cocos2d::CCScene
{
public:
	virtual bool init(void);
    
	virtual void update(float dt);
	
    CREATE_FUNC(CTutorialScene);
    
	void SettingSceneCallback(CCObject* pSender);
    
private:
};
