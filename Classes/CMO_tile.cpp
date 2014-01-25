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
	pItem = NULL;
	m_Owner = MO_NOBODY;

	return true;
}

void CMO_tile::setImage(IndexedPosition indexedPosition)
{
	m_Index = indexedPosition;

	// ���ξ��� �̹����� �־��ش�.
	// (������ ���� �� �ƹ��͵� �� ���δٸ� �߰� �� �ϸ� �ȴ�)
	pTile = CCSprite::create(TileImageFileList[4].c_str(), CCRectMake(0.0f, 0.0f, DEFAULT_TILE_SIZE,  DEFAULT_TILE_SIZE) );
	pTile->setAnchorPoint( ccp(0, 0) );
	pTile->setPosition( ccp(0.0f, 0.0f) );
	this->addChild(pTile, 0);

	// item �߰�
	// pItem = CCSprite::create(TileImageFileList[0].c_str(), CCRectMake(0.0f, 0.0f, DEFAULT_TILE_SIZE,  DEFAULT_TILE_SIZE) );
	// pItem->setAnchorPoint( ccp(0, 0) );
	// pItem->setPosition( ccp(0.0f, 0.0f) );
	// this->addChild(pItem, 1);
}

void CMO_tile::update( float delta )
{
	//���� Ÿ�� ������ ����� ������Ʈ
	MO_OWNER tempOwner = CGameManager::GetInstance()->GetMapOwner(m_Index);
	if (tempOwner != m_Owner)
	{
		// ���� ������ �����ϰ� ������ �̹����� �����Ѵ�.
		m_Owner = tempOwner;
		this->removeChild(pTile, true);

		// ���Ӱ� ������ �����ڿ� ���� �̹��� ���� ���� �Ҵ�
		// ���� m_Owner�� MO_NOBODY ���·� �����ϸ� ū�ϳ�
		pTile = CCSprite::create(TileImageFileList[static_cast<int>(CGameManager::GetInstance()->GetCharacterId(m_Owner))].c_str(), CCRectMake(0.0f, 0.0f, DEFAULT_TILE_SIZE,  DEFAULT_TILE_SIZE) );
		pTile->setAnchorPoint( ccp(0, 0) );
		pTile->setPosition( ccp(0.0f, 0.0f) );
		this->addChild(pTile, 0);
	}
}

