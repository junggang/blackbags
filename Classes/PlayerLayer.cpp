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
	
	//m_Player[i]�� �ش��ϳ��� ĳ���͸� �̾��ش�. ���⼭ i�� playerID�� ���Ѵ�.
	for (int i = 0; i<MAX_PLAYER_NUM; ++i)
	{
		//�������� ���� �÷��̾��� �ѱ��.
		if (CGameManager::GetInstance()->GetCharacterId(i)==-1)
			continue;

		int position = CGameManager::GetInstance()->GetPlayerTurn(i);

		switch (CGameManager::GetInstance()->GetCharacterId(i))
		{
		case 0:
			m_Animation[i] = CCAnimation::create();
			m_Animation[i]->setDelayPerUnit(0.5f);
			m_Animation[i]->addSpriteFrame(cache->spriteFrameByName("CHARACTER_1_Ani0.png"));
			m_Animation[i]->addSpriteFrame(cache->spriteFrameByName("CHARACTER_1_Ani1.png"));
			m_Player[i] = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("CHARACTER_1_Ani0.png"));
			m_Player[i]->setPosition(m_UIposition[position]);
			m_pSpriteBatchNode->addChild(m_Player[i]);
			//addChild(m_pSpriteBatchNode);
			break;
		case 1:
			m_Animation[i] = CCAnimation::create();
			m_Animation[i]->setDelayPerUnit(0.5f);
			m_Animation[i]->addSpriteFrame(cache->spriteFrameByName("CHARACTER_2_Ani1.png"));
			m_Animation[i]->addSpriteFrame(cache->spriteFrameByName("CHARACTER_2_Ani2.png"));
			m_Player[i] = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("CHARACTER_2_Ani1.png"));
			m_Player[i]->setPosition(m_UIposition[position]);
			m_pSpriteBatchNode->addChild(m_Player[i]);
			//addChild(m_pSpriteBatchNode);
			break;
		case 2:
			m_Animation[i] = CCAnimation::create();
			m_Animation[i]->setDelayPerUnit(0.5f);
			m_Animation[i]->addSpriteFrame(cache->spriteFrameByName("CHARACTER_3_Ani2.png"));
			m_Animation[i]->addSpriteFrame(cache->spriteFrameByName("CHARACTER_3_Ani1.png"));
			m_Player[i] = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("CHARACTER_3_Ani1.png"));
			m_Player[i]->setPosition(m_UIposition[position]);
			m_pSpriteBatchNode->addChild(m_Player[i]);
			//addChild(m_pSpriteBatchNode);
			break;
		case 3:
			m_Animation[i] = CCAnimation::create();
			m_Animation[i]->setDelayPerUnit(0.5f);
			m_Animation[i]->addSpriteFrame(cache->spriteFrameByName("CHARACTER_4_Ani1.png"));
			m_Animation[i]->addSpriteFrame(cache->spriteFrameByName("CHARACTER_4_Ani2.png"));
			m_Player[i] = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("CHARACTER_4_Ani1.png"));
			m_Player[i]->setPosition(m_UIposition[position]);
			m_pSpriteBatchNode->addChild(m_Player[i]);
			//addChild(m_pSpriteBatchNode);
			break;
		default:
			break;
		}
		
	}


	return true;

}

void CPlayerLayer::update( float dt )
{
	
}
