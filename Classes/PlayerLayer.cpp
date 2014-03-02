#include "PlayerLayer.h"
#include "GameManager.h"

USING_NS_CC;

bool CPlayerLayer::init()
{
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	m_CurrentPlayerId = -1;

	m_VisibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//위치 선정부터 한다. 위치는 턴 순서대로이다.
	int playerNumber = CGameManager::GetInstance()->GetPlayerNumberOfThisGame();

	m_UIposition[0] = CCPoint(SHARED_PLAYER_UI_UPPER_LEFT_POS);
	m_UIposition[1] = CCPoint(SHARED_PLAYER_UI_UPPER_RIGHT_POS);
	m_UIposition[2] = CCPoint(SHARED_PLAYER_UI_BELOW_LEFT_POS);
	m_UIposition[3] = CCPoint(SHARED_PLAYER_UI_BELOW_RIGHT_POS);
	
	for (int playerId = 0; playerId<MAX_PLAYER_NUM; ++playerId)
	{
		//생성되지 않은 플레이어라면 넘긴다.
		if (CGameManager::GetInstance()->GetCharacterIdByPlayerId(playerId) == -1)
			continue;

		//턴에 따른 위치를 알아낸다.
		int position = CGameManager::GetInstance()->GetPlayerTurn(playerId);
		int characterId = CGameManager::GetInstance()->GetCharacterIdByPlayerId(playerId);

		//배경을 바른다
		m_BackGround[playerId] = CCSprite::create(SHARED_PLAYERUI_BACKGROUND[position].c_str());
		m_BackGround[playerId]->setAnchorPoint(ccp(0,0));
		m_BackGround[playerId]->setPosition(m_UIposition[position]);
		addChild(m_BackGround[playerId],0);

		//위치, 캐릭터 Id에 따라 파일명 알아냄
		if(CGameManager::GetInstance()->IsOnlineMode())
		{
			m_Player[playerId] = CCSprite::create(SHARED_PLAYERUI_CHARACTERS[4*position+characterId].c_str());
			
			//이름을 돌려줘야한다. config에 추가할 것.
			m_PlayerName[playerId] = CCLabelTTF::create(CGameManager::GetInstance()->GetPlayerName(playerId).c_str(), "Arial", 50, 
				CCSizeMake(400, 100), kCCTextAlignmentLeft);
			m_PlayerName[playerId]->setAnchorPoint(ccp(0,0));
			switch (position)
			{
			case 0:
				m_PlayerName[playerId]->setPosition(ccp(m_UIposition[position].x+600.0f,m_UIposition[position].y+300.0f));
				m_PlayerName[playerId]->setRotation(180.0f);
				break;
			case 1:
				m_PlayerName[playerId]->setPosition(ccp(m_UIposition[position].x+400.0f,m_UIposition[position].y+300.0f));
				m_PlayerName[playerId]->setRotation(180.0f);
				break;
			case 2:
				m_PlayerName[playerId]->setPosition(ccp(m_UIposition[position].x+300.0f,m_UIposition[position].y+100.0f));
				break;
			case 3:
				m_PlayerName[playerId]->setPosition(ccp(m_UIposition[position].x+100.0f,m_UIposition[position].y+100.0f));
				break;
			default:
				break;
			}
			addChild(m_PlayerName[playerId],3);
		}
		else
		{
			m_Player[playerId] = CCSprite::create(SHARED_PLAYERUI_CHARACTERS_OFF[4*position+characterId].c_str());
		}
		m_Player[playerId]->setAnchorPoint(ccp(0,0));
		m_Player[playerId]->setPosition(m_UIposition[position]);
		addChild(m_Player[playerId],2);
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
		//SetWaitingCharacters();
		m_Player[m_CurrentPlayerId]->pauseSchedulerAndActions();
	}

	m_CurrentPlayerId = CGameManager::GetInstance()->GetCurrentPlayerId();
	int position = CGameManager::GetInstance()->GetPlayerTurn(m_CurrentPlayerId);
	
	removeChildByTag(0);

	CCSprite* currentTurnUI = CCSprite::create(SHARED_PLAYERUI_BACKGROUND[4+position].c_str());
	currentTurnUI->setTag(0);
	currentTurnUI->setAnchorPoint(ccp(0,0));
	currentTurnUI->setPosition(m_UIposition[position]);
	addChild(currentTurnUI,1);



	//현재 턴에 해당하는 캐릭터의 애니메이션을 재생한다.
	//애니메이션은 업데이트할 때마다 새로 생성해줘야 함.
	/*
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
	*/
}

void CPlayerLayer::SetWaitingCharacters()
{
	//처음 프레임으로 돌려 놓는 함수
	for (int playerId = 0; playerId<MAX_PLAYER_NUM;++playerId)
	{
		if (CGameManager::GetInstance()->GetCharacterIdByPlayerId(playerId)==-1)
			continue;

		
	}	
}
