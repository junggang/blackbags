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

	//��ġ �������� �Ѵ�. ��ġ�� �� ��������̴�.
	m_UIposition[0] = CCPoint(SHARED_PLAYER_UI_UPPER_LEFT_POS);
	m_UIposition[1] = CCPoint(SHARED_PLAYER_UI_UPPER_RIGHT_POS);
	m_UIposition[2] = CCPoint(SHARED_PLAYER_UI_BELOW_LEFT_POS);
	m_UIposition[3] = CCPoint(SHARED_PLAYER_UI_BELOW_RIGHT_POS);
	
	//�ϴ� �� �÷��̾��� ĳ���Ͱ� ��� ��ġ�� ���� ���Ѵ�.
	for (int playerId = 0; playerId<MAX_PLAYER_NUM; ++playerId)
	{
		//�������� ���� �÷��̾��� �ѱ��.
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

	//ĳ������ ù��° ���������� ��� UI�� �غ��Ѵ�.
	SetWaitingCharacters();
	
	//addChild���ش�.
	for (int playerId=0;playerId<MAX_PLAYER_NUM;++playerId)
	{
		if (CGameManager::GetInstance()->GetCharacterIdByPlayerId(playerId)==-1)
			continue;

		m_pSpriteBatchNode->addChild(m_Player[playerId],0);
		addChild(m_PlayerName[playerId],1);

	}

	//���� ��(ù��° ��)���� �ִϸ��̼��� ����� �� �ֵ��� update()�� �� �� ���ش�.
	update(0);

	return true;

}

void CPlayerLayer::update( float dt )
{
	//�ϴ� �� ���� �������̴� �ִϸ��̼��� �����ϰ�, ��� ĳ���͸� ù��° ���������� ���� ���´�.
	//pause�� �����Ƿ�, �ݵ�� resume�� �̿��ؾ� �Ѵ�.
	if (m_CurrentPlayerId != -1)
	{
		SetWaitingCharacters();
		m_Player[m_CurrentPlayerId]->pauseSchedulerAndActions();
	}

	//���� �Ͽ� �ش��ϴ� ĳ������ �ִϸ��̼��� ����Ѵ�.
	//�ִϸ��̼��� ������Ʈ�� ������ ���� ��������� ��.
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
