#pragma once
#include "cocos2d.h"

class CPlayScene : public cocos2d::CCScene
{
public:
	virtual bool init(void);

	virtual void update(float dt);

	CREATE_FUNC(CPlayScene);

private:
	bool m_GameEndFlag;

	cocos2d::CCLayer* gameBoard;
	cocos2d::CCLayer* player;
	cocos2d::CCLayer* timer;
	cocos2d::CCLayer* menu;
};