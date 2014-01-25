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

	//��ġ �������� �Ѵ�.
	m_UIposition[0].x = DEFAULT_CHARACTER_MARGIN_H;
	m_UIposition[0].y = m_VisibleSize.height - DEFAULT_CHARACTER_MARGIN_V;

	m_UIposition[1].x = m_VisibleSize.width - DEFAULT_CHARACTER_MARGIN_H;
	m_UIposition[1].y =m_VisibleSize.height - DEFAULT_CHARACTER_MARGIN_V;

	m_UIposition[2].x = DEFAULT_CHARACTER_MARGIN_H;
	m_UIposition[2].y = DEFAULT_CHARACTER_MARGIN_V;

	m_UIposition[3].x =m_VisibleSize.width -  DEFAULT_CHARACTER_MARGIN_H;
	m_UIposition[3].y = DEFAULT_CHARACTER_MARGIN_V;

	//�׸��� �Ź� �ҷ��� �� ������ �ϴ� �÷��� ������� ĳ���͸� �迭�ϰ�, �� ���̵� ������ ������ �Ѵ�.
	for(int i = 0; i<CGameManager::GetInstance()->GetPlayerNumber();i++)
	{
		if (CGameManager::GetInstance()->GetPlayerIdByTurn(i)!=-1)
		{
			m_Character[i] = CGameManager::GetInstance()->GetPlayerIdByTurn(i);
			CCSprite* pTitle = CCSprite::create(CGameManager::GetInstance()->GetCharacterPlayFaceById(m_Character[i]).c_str());
			pTitle->setPosition(m_UIposition[i]);
			this->addChild(pTitle, 0);
		}
	}
	
	return true;

}

void CPlayerLayer::update( float dt )
{

}
