#pragma once
#include "cocos2d.h"

class CIntroScene : public cocos2d::CCScene
{
public:
	virtual bool init(void);

	void endIntro();

	// implement the "static node()" method manually
    CREATE_FUNC(CIntroScene);
};
