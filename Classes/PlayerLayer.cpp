#include "PlayerLayer.h"
#include "GameManager.h"

USING_NS_CC;

bool CPlayerLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	m_CurrentPlayerId = -1;

	m_VisibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//위치 선정부터 한다. 위치는 턴 순서대로이다.
	m_UIposition[0] = CCPoint(SHARED_PLAYER_UI_UPPER_LEFT_POS);
	m_UIposition[1] = CCPoint(SHARED_PLAYER_UI_UPPER_RIGHT_POS);
	m_UIposition[2] = CCPoint(SHARED_PLAYER_UI_BELOW_LEFT_POS);
	m_UIposition[3] = CCPoint(SHARED_PLAYER_UI_BELOW_RIGHT_POS);
	
	//일단 각 플레이어의 캐릭터가 어디에 위치할 지만 정한다.
	for (int playerId = 0; playerId<MAX_PLAYER_NUM; ++playerId)
	{
		//생성되지 않은 플레이어라면 넘긴다.
		if (CGameManager::GetInstance()->GetCharacterIdByPlayerId(playerId) == -1)
			continue;

		m_BackGround[playerId] = CCSprite::create();

		int position = CGameManager::GetInstance()->GetPlayerTurn(playerId);

		m_Player[playerId] = CCSprite::create();
		m_Player[playerId]->setAnchorPoint(ccp(0,0));
		m_Player[playerId]->setPosition(m_UIposition[position]);

		m_PlayerName[playerId] = CCLabelTTF::create(CGameManager::GetInstance()->GetPlayerName(playerId).c_str(), "Arial", 12, 
			CCSizeMake(245, 32), kCCTextAlignmentCenter);

		m_PlayerName[playerId]->setPosition(m_UIposition[position]);

		switch(position)
		{
		case 0:
			m_PlayerName[playerId]->setRotation(-45.0f);
			break;
		case 1:
			m_Player[playerId]->setFlipX(true);
			m_PlayerName[playerId]->setRotation(45.0f);
			break;
		case 2:
			m_Player[playerId]->setFlipY(true);
			m_PlayerName[playerId]->setRotation(-135.0f);
			break;
		case 3:
			m_Player[playerId]->setRotation(180.0f);
			m_PlayerName[playerId]->setRotation(135.0f);
			break;
		}
	}

	//캐릭터의 첫번째 프레임으로 모든 UI를 준비한다.
	SetWaitingCharacters();
	
	//addChild해준다.
	for (int playerId=0;playerId<MAX_PLAYER_NUM;++playerId)
	{
		if (CGameManager::GetInstance()->GetCharacterIdByPlayerId(playerId)==-1)
			continue;

		m_pSpriteBatchNode->addChild(m_Player[playerId],0);
		addChild(m_PlayerName[playerId],1);

	}

	//현재 턴(첫번째 턴)부터 애니메이션이 재생될 수 있도록 update()를 한 번 해준다.
	update(0);

	return true;

}

void CPlayerLayer::update( float dt )
{
	//일단 이 전에 실행중이던 애니메이션은 중지하고, 모든 캐릭터를 첫번째 프레임으로 돌려 놓는다.
	//pause를 했으므로, 반드시 resume을 이용해야 한다.
	if (m_CurrentPlayerId != -1)
	{
		SetWaitingCharacters();
		m_Player[m_CurrentPlayerId]->pauseSchedulerAndActions();
	}

	//현재 턴에 해당하는 캐릭터의 애니메이션을 재생한다.
	//애니메이션은 업데이트할 때마다 새로 생성해줘야 함.
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("image/CharacterPlayAnimation.plist");

	m_CurrentPlayerId = CGameManager::GetInstance()->GetCurrentPlayerId();

	CCLOG("currentId = %d, it's turn = %d",m_CurrentPlayerId,CGameManager::GetInstance()->GetPlayerTurn(m_CurrentPlayerId));

	m_CharacterAni = CCAnimation::create();
	m_CharacterAni->setDelayPerUnit(0.5f);

	switch(CGameManager::GetInstance()->GetCharacterIdByPlayerId(m_CurrentPlayerId))
	{
	case 0:
		m_CharacterAni->addSpriteFrame(cache->spriteFrameByName("CHARACTER_1_Ani0.png"));
		m_CharacterAni->addSpriteFrame(cache->spriteFrameByName("CHARACTER_1_Ani1.png"));
		break;
	case 1:
		m_CharacterAni->addSpriteFrame(cache->spriteFrameByName("CHARACTER_2_Ani1.png"));
		m_CharacterAni->addSpriteFrame(cache->spriteFrameByName("CHARACTER_2_Ani2.png"));
		break;
	case 2:
		m_CharacterAni->addSpriteFrame(cache->spriteFrameByName("CHARACTER_3_Ani1.png"));
		m_CharacterAni->addSpriteFrame(cache->spriteFrameByName("CHARACTER_3_Ani2.png"));
		break;
	case 3:
		m_CharacterAni->addSpriteFrame(cache->spriteFrameByName("CHARACTER_4_Ani1.png"));
		m_CharacterAni->addSpriteFrame(cache->spriteFrameByName("CHARACTER_4_Ani2.png"));
		break;
	}

	CCRepeatForever* repeatAction = CCRepeatForever::create(CCAnimate::create(m_CharacterAni));
	m_Player[m_CurrentPlayerId]->runAction(repeatAction);	
	m_Player[m_CurrentPlayerId]->resumeSchedulerAndActions();

}

void CPlayerLayer::SetWaitingCharacters()
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("image/CharacterPlayAnimation.plist","image/CharacterPlayAnimation.png");

	for (int playerId = 0; playerId<MAX_PLAYER_NUM;++playerId)
	{
		if (CGameManager::GetInstance()->GetCharacterIdByPlayerId(playerId)==-1)
			continue;
		switch (CGameManager::GetInstance()->GetCharacterIdByPlayerId(playerId))
		{
		case 0:
			m_Player[playerId]->setDisplayFrame(cache->spriteFrameByName("CHARACTER_1_Ani0.png"));
			break;
		case 1:
			m_Player[playerId]->setDisplayFrame(cache->spriteFrameByName("CHARACTER_2_Ani1.png"));
			break;
		case 2:
			m_Player[playerId]->setDisplayFrame(cache->spriteFrameByName("CHARACTER_3_Ani1.png"));
			break;
		case 3:
			m_Player[playerId]->setDisplayFrame(cache->spriteFrameByName("CHARACTER_4_Ani1.png"));
			break;
		default:
			break;
		}
	}	
}
