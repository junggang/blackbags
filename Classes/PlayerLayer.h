#pragma once
#include "cocos2d.h"
#include "config.h"
#include <array>

class CPlayerLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	virtual void update(float dt);
	void SetWaitingCharacters();

	// implement the "static node()" method manually
	CREATE_FUNC(CPlayerLayer);

private:
	cocos2d::CCSize m_VisibleSize;
	std::array<cocos2d::CCPoint,MAX_PLAYER_NUM> m_UIposition;
	std::array<cocos2d::CCSprite*, MAX_PLAYER_NUM> m_Player;
	cocos2d::CCSpriteBatchNode* m_pSpriteBatchNode;
	cocos2d::CCAnimation* m_CharacterAni;
	int m_CurrentPlayerId;

	std::array<cocos2d::CCLabelTTF*,MAX_PLAYER_NUM>m_PlayerName;
};

