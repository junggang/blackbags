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
	m_UIposition[0].x = DEFAULT_CHARACTER_MARGIN_H;
	m_UIposition[0].y = m_VisibleSize.height - DEFAULT_CHARACTER_MARGIN_V;

	m_UIposition[1].x = m_VisibleSize.width - DEFAULT_CHARACTER_MARGIN_H;
	m_UIposition[1].y =m_VisibleSize.height - DEFAULT_CHARACTER_MARGIN_V;

	m_UIposition[2].x = DEFAULT_CHARACTER_MARGIN_H;
	m_UIposition[2].y = DEFAULT_CHARACTER_MARGIN_V;

	m_UIposition[3].x =m_VisibleSize.width -  DEFAULT_CHARACTER_MARGIN_H;
	m_UIposition[3].y = DEFAULT_CHARACTER_MARGIN_V;

	//CCSpriteBatchNode�� ����Ͽ� ���ҽ��� �غ��Ѵ�.
	m_pSpriteBatchNode = CCSpriteBatchNode::create("image/CharacterPlayAnimation.png");
	addChild(m_pSpriteBatchNode,0);
	
	
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("image/CharacterPlayAnimation.plist");
	
	//�ϴ� �� �÷��̾��� ĳ���Ͱ� ��� ��ġ�� ���� ���Ѵ�.
	for (int playerId = 0; playerId<MAX_PLAYER_NUM; ++playerId)
	{
		//�������� ���� �÷��̾��� �ѱ��.
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

	//ĳ������ ù��° ���������� ��� UI�� �غ��Ѵ�.
	SetWaitingCharacters();
	
	//addChild���ش�.
	for(int playerId=0;playerId<MAX_PLAYER_NUM;++playerId)
	{
		if (CGameManager::GetInstance()->GetCharacterId(playerId)==-1)
			continue;

		m_pSpriteBatchNode->addChild(m_Player[playerId]);
	}

	//���� ��(ù��° ��)���� �ִϸ��̼��� ����� �� �ֵ��� update()�� �� �� ���ش�.
	update(0);

	return true;

}

void CPlayerLayer::update( float dt )
{
	//�ϴ� �� ���� �������̴� �ִϸ��̼��� �����ϰ�, ��� ĳ���͸� ù��° ���������� ���� ���´�.
	//pause�� �����Ƿ�, �ݵ�� resume�� �̿��ؾ� �Ѵ�.
	if(m_CurrentPlayerId != -1)
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
