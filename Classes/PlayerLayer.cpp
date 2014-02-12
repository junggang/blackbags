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
	m_UIposition[0].x = DEFAULT_CHARACTER_MARGIN_H;
	m_UIposition[0].y = m_VisibleSize.height - DEFAULT_CHARACTER_MARGIN_V;

	m_UIposition[1].x = m_VisibleSize.width - DEFAULT_CHARACTER_MARGIN_H;
	m_UIposition[1].y =m_VisibleSize.height - DEFAULT_CHARACTER_MARGIN_V;

	m_UIposition[2].x = DEFAULT_CHARACTER_MARGIN_H;
	m_UIposition[2].y = DEFAULT_CHARACTER_MARGIN_V;

	m_UIposition[3].x =m_VisibleSize.width -  DEFAULT_CHARACTER_MARGIN_H;
	m_UIposition[3].y = DEFAULT_CHARACTER_MARGIN_V;

	//CCSpriteBatchNode를 사용하여 리소스를 준비한다.
	m_pSpriteBatchNode = CCSpriteBatchNode::create("image/CharacterPlayAnimation.png");
	addChild(m_pSpriteBatchNode,0);
	
	
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("image/CharacterPlayAnimation.plist");
	
	//일단 각 플레이어의 캐릭터가 어디에 위치할 지만 정한다.
	for (int playerId = 0; playerId<MAX_PLAYER_NUM; ++playerId)
	{
		//생성되지 않은 플레이어라면 넘긴다.
		if (CGameManager::GetInstance()->GetCharacterId(playerId)==-1)
			continue;

		int position = CGameManager::GetInstance()->GetPlayerTurn(playerId);

		m_Player[playerId] = CCSprite::create();
		m_Player[playerId]->setPosition(m_UIposition[position]);
		switch(position)
		{
		case 0:
			break;
		case 1:
			m_Player[playerId]->setFlipX(true);
			break;
		case 2:
			m_Player[playerId]->setFlipY(true);
			break;
		case 3:
			m_Player[playerId]->setRotation(180.0f);
			break;
		}
	}

	//캐릭터의 첫번째 프레임으로 모든 UI를 준비한다.
	SetWaitingCharacters();
	
	//addChild해준다.
	for(int playerId=0;playerId<MAX_PLAYER_NUM;++playerId)
	{
		if (CGameManager::GetInstance()->GetCharacterId(playerId)==-1)
			continue;

		m_pSpriteBatchNode->addChild(m_Player[playerId]);
	}

	//현재 턴(첫번째 턴)부터 애니메이션이 재생될 수 있도록 update()를 한 번 해준다.
	update(0);

	return true;

}

void CPlayerLayer::update( float dt )
{
	//일단 이 전에 실행중이던 애니메이션은 중지하고, 모든 캐릭터를 첫번째 프레임으로 돌려 놓는다.
	//pause를 했으므로, 반드시 resume을 이용해야 한다.
	if(m_CurrentPlayerId != -1)
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

	switch(CGameManager::GetInstance()->GetCharacterId(m_CurrentPlayerId))
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

	for(int playerId = 0; playerId<MAX_PLAYER_NUM;++playerId)
	{
		if (CGameManager::GetInstance()->GetCharacterId(playerId)==-1)
			continue;
		switch (CGameManager::GetInstance()->GetCharacterId(playerId))
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
