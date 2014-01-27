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

	//�׸��� �Ź� �ҷ��� �� ������ �ϴ� �÷��� ������� ĳ���͸� �迭�ϰ�, �� ���̵� ������ ������ �Ѵ�.
	/*
	for (int i = 0; i<CGameManager::GetInstance()->GetPlayerNumber();i++)
	{
		if (CGameManager::GetInstance()->GetPlayerIdByTurn(i)!=-1)
		{
			m_Character[i] = CGameManager::GetInstance()->GetPlayerIdByTurn(i);
			CCSprite* pTitle = CCSprite::create(CGameManager::GetInstance()->GetCharacterPlayFaceById(m_Character[i]).c_str());
			pTitle->setPosition(m_UIposition[i]);
			this->addChild(pTitle, 0);
		}
	}
	*/

	//CCSpriteBatchNode�� ����Ͽ� ���ҽ��� �غ��Ѵ�.
	m_pSpriteBatchNode = CCSpriteBatchNode::create("image/CharacterPlayAnimation.png");
	addChild(m_pSpriteBatchNode,0);

	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("image/CharacterPlayAnimation.plist");
	
	//m_Player[playerId]�� �ش��ϳ��� ĳ���͸� �̾��ش�. 
	for (int playerId = 0; i<MAX_PLAYER_NUM; ++i)
	{
		//�������� ���� �÷��̾��� �ѱ��.
		if (CGameManager::GetInstance()->GetCharacterId(playerId)==-1)
			continue;

		int position = CGameManager::GetInstance()->GetPlayerTurn(playerId);

		switch (CGameManager::GetInstance()->GetCharacterId(playerId))
		{
		case 0:
			m_Player[playerId] = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("CHARACTER_1_Ani0.png"));
			m_Player[playerId]->setPosition(m_UIposition[position]);
			m_pSpriteBatchNode->addChild(m_Player[playerId]);
			//addChild(m_pSpriteBatchNode);
			break;
		case 1:
			m_Player[playerId] = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("CHARACTER_2_Ani1.png"));
			m_Player[playerId]->setPosition(m_UIposition[position]);
			m_pSpriteBatchNode->addChild(m_Player[playerId]);
			//addChild(m_pSpriteBatchNode);
			break;
		case 2:			
			m_Player[playerId] = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("CHARACTER_3_Ani1.png"));
			m_Player[playerId]->setPosition(m_UIposition[position]);
			m_pSpriteBatchNode->addChild(m_Player[playerId]);
			//addChild(m_pSpriteBatchNode);
			break;
		case 3:
			m_Player[playerId] = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("CHARACTER_4_Ani1.png"));
			m_Player[playerId]->setPosition(m_UIposition[position]);
			m_pSpriteBatchNode->addChild(m_Player[playerId]);
			//addChild(m_pSpriteBatchNode);
			break;
		default:
			break;
		}
		CCLOG("Id: %d, turn:%d",i,position);
		
	}

	update(0);

	return true;

}

void CPlayerLayer::update( float dt )
{
	//�ϴ� �� ���� �������̴� �ִϸ��̼��� �����Ѵ�.
	if(m_CurrentPlayerId != -1)
		m_Player[m_CurrentPlayerId]->pauseSchedulerAndActions();

	//���� �Ͽ� �ش��ϴ� ĳ������ �ִϸ��̼��� ����Ѵ�.
	//�ִϸ��̼��� ������Ʈ�� ������ ���� ��������� ��.
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("image/CharacterPlayAnimation.plist");

	m_CurrentPlayerId = CGameManager::GetInstance()->GetCurrentPlayerId();

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
}
