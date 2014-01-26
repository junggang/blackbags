#pragma once
#include "cocos2d.h"
#include "config.h"
#include <array>

class CPlayerLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	virtual void update(float dt);

	// implement the "static node()" method manually
	CREATE_FUNC(CPlayerLayer);

private:
	cocos2d::CCSize m_VisibleSize;
	std::array<cocos2d::CCPoint,MAX_PLAYER_NUM> m_UIposition;
	//std::array<int,MAX_PLAYER_NUM> m_Character;

	std::array<cocos2d::CCSprite*, MAX_PLAYER_NUM> m_Player;
	cocos2d::CCSpriteBatchNode* m_pSpriteBatchNode;
	std::array<cocos2d::CCAnimation*,MAX_PLAYER_NUM> m_Animation;
};

