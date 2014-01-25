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

	//소유주에 따른 그림 파일 들
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

	// 주인없는 이미지를 넣어준다.
	// (주인이 없을 때 아무것도 안 보인다면 추가 안 하면 된다)
	pTile = CCSprite::create(TileImageFileList[4].c_str(), CCRectMake(0.0f, 0.0f, DEFAULT_TILE_SIZE,  DEFAULT_TILE_SIZE) );
	pTile->setAnchorPoint( ccp(0, 0) );
	pTile->setPosition( ccp(0.0f, 0.0f) );
	this->addChild(pTile, 0);

	// item 추가
	// pItem = CCSprite::create(TileImageFileList[0].c_str(), CCRectMake(0.0f, 0.0f, DEFAULT_TILE_SIZE,  DEFAULT_TILE_SIZE) );
	// pItem->setAnchorPoint( ccp(0, 0) );
	// pItem->setPosition( ccp(0.0f, 0.0f) );
	// this->addChild(pItem, 1);
}

void CMO_tile::update( float delta )
{
	//현재 타일 소유를 물어보고 업데이트
	MO_OWNER tempOwner = CGameManager::GetInstance()->GetMapOwner(m_Index);
	if (tempOwner != m_Owner)
	{
		// 소유 설정을 변경하고 기존의 이미지를 삭제한다.
		m_Owner = tempOwner;
		this->removeChild(pTile, true);

		// 새롭게 설정된 소유자에 따라서 이미지 새로 생성 할당
		// 만약 m_Owner가 MO_NOBODY 상태로 진입하면 큰일남
		pTile = CCSprite::create(TileImageFileList[static_cast<int>(CGameManager::GetInstance()->GetCharacterId(m_Owner))].c_str(), CCRectMake(0.0f, 0.0f, DEFAULT_TILE_SIZE,  DEFAULT_TILE_SIZE) );
		pTile->setAnchorPoint( ccp(0, 0) );
		pTile->setPosition( ccp(0.0f, 0.0f) );
		this->addChild(pTile, 0);
	}
}

