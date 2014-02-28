#include "CMO_tile.h"
#include "GameManager.h"

USING_NS_CC;

/*
CMO_tile::CMO_tile()
{
}

CMO_tile::~CMO_tile()
{

}

CMO_tile* CMO_tile::create(const char* pszFileName, const CCRect& rect)
{
	CMO_tile* pSprite = new CMO_tile();
	if (pSprite && pSprite->initWithFile(pszFileName, rect))
	{
		pSprite->autorelease();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

CMO_tile* CMO_tile::Create(IndexedPosition indexedPosition)
{

	//�����ֿ� ���� �׸� ���� ��
	static std::string objectNames[5] =
	{
		"image/MO_tile.png",
		"image/MO_tile.png",
		"image/MO_tile.png",
		"image/MO_tile.png",
		"image/MO_tile.png"
	};
	
	//int objectIdx = CGameManager::GetInstance()->GetMapOwner(indexedPosition);
	CMO_tile* pMapObejct = CMO_tile::create(objectNames[0].c_str(), CCRectMake(0.0f, 0.0f, DEFAULT_TILE_SIZE,  DEFAULT_TILE_SIZE));

	return pMapObejct;
}
*/

bool CMO_tile::init()
{
	if ( !CCSprite::init() )
    {
        return false;
    }

	pTile = NULL;
	//pItem = NULL;
	m_Owner = MO_NOBODY;

	return true;
}

void CMO_tile::setImage(IndexedPosition indexedPosition)
{
	m_Index = indexedPosition;

	// ���ξ��� �̹����� �־��ش�.
	// (������ ���� �� �ƹ��͵� �� ���δٸ� �߰� �� �ϸ� �ȴ�)
	//pTile = CCSprite::create(TileImageFileList[4].c_str(), CCRectMake(0.0f, 0.0f, DEFAULT_TILE_SIZE,  DEFAULT_TILE_SIZE) );
	pTile = CCSprite::create(PLAYSCENE_LAND_UNOCCUPIED.c_str(), CCRectMake(0.0f, 0.0f, DEFAULT_TILE_WIDTH,  DEFAULT_TILE_HEIGHT) );
	pTile->setAnchorPoint( ccp(0, 0.5f) );
	pTile->setPosition( ccp(0.0f, 0.0f) );
	this->addChild(pTile, 0);

	// item �߰�
	//pItem = CCSprite::create(TileImageFileList[0].c_str(), CCRectMake(0.0f, 0.0f, DEFAULT_TILE_WIDTH,  DEFAULT_TILE_HEIGHT) );
	//pItem->setAnchorPoint( ccp(0, 0) );
	//pItem->setPosition( ccp(0.0f, 0.0f) );
	if (CGameManager::GetInstance()->GetItem(indexedPosition) != ITEM_NOTHING)
	{
		CMO_item* pItem = CMO_item::create();
		pItem->setImage(indexedPosition);
		pItem->setAnchorPoint( ccp(0, 0.5f) );
		pItem->setPosition( ccp(0.0f, 0.0f) );
		this->addChild(pItem, 1);
	}
}

void CMO_tile::update( float delta )
{
	//���� Ÿ�� ������ ����� ������Ʈ
	MO_OWNER tempOwner = CGameManager::GetInstance()->GetMapOwner(m_Index);
	if (tempOwner != m_Owner)
	{
		m_Owner = tempOwner;

		//�ִϸ��̼� ���
		CCAnimation *tileAnimation = CCAnimation::create();
		tileAnimation->setDelayPerUnit(0.2);

		tileAnimation->addSpriteFrameWithFileName("image/flower_0.png");
		tileAnimation->addSpriteFrameWithFileName("image/flower_blue.png");
		//tileAnimation->addSpriteFrameWithFileName("image/MO_tile_void_animation_02.png");
		//tileAnimation->addSpriteFrameWithFileName("image/MO_tile_void_animation_03.png");

		CCAnimate *tileAnimate = CCAnimate::create(tileAnimation);

		//�ִϸ��̼� ����� ���� �Ŀ� �׾��� �� �̹����� ��ü�ϴ� �Լ��� ȣ��
		CCFiniteTimeAction *pAction = CCSequence::create(tileAnimate, 
			CCCallFunc::create(this, callfunc_selector(CMO_tile::changeImage)), NULL);

		// �⺻ ���� �ִϸ��̼� ��� �ð� + Ÿ�Ͽ� �Ҵ� �� ��� ���� * Ÿ�� �ִϸ��̼� ��� �ð�
		float delayTime = 0.8f + 0.8f * (CGameManager::GetInstance()->GetTileAnimationTurn(m_Index) - 1);

		CGameManager::GetInstance()->SetAnimationDelay(delayTime);

		CCDelayTime *dt = CCDelayTime::create(delayTime);
		CCAction *actions = CCSequence::create(dt, pAction, NULL);

		pTile->setAnchorPoint(ccp(0,0.5f));
		pTile->runAction(actions);
	}
}

void CMO_tile::changeImage()
{
	// ������ �̹����� �����Ѵ�.
	this->removeChild(pTile, true);

	// ���Ӱ� ������ �����ڿ� ���� �̹��� ���� ���� �Ҵ�
	// ���� m_Owner�� MO_NOBODY ���·� �����ϸ� ū�ϳ�
	pTile = CCSprite::create(TileImageFileList[static_cast<int>(CGameManager::GetInstance()->GetCharacterIdByPlayerId(m_Owner))].c_str());
	pTile->setAnchorPoint( ccp(0, 0.5) );
	pTile->setPosition( ccp(0.0f, 0.0f) );
	this->addChild(pTile, 0);
}

