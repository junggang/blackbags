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
	//pItem = NULL;
	m_Owner = MO_NOBODY;

	return true;
}

void CMO_tile::setImage(IndexedPosition indexedPosition)
{
	m_Index = indexedPosition;

	// 주인없는 이미지를 넣어준다.
	// (주인이 없을 때 아무것도 안 보인다면 추가 안 하면 된다)
	//pTile = CCSprite::create(TileImageFileList[4].c_str(), CCRectMake(0.0f, 0.0f, DEFAULT_TILE_SIZE,  DEFAULT_TILE_SIZE) );
	pTile = CCSprite::create(PLAYSCENE_LAND_UNOCCUPIED.c_str(), CCRectMake(0.0f, 0.0f, DEFAULT_TILE_WIDTH,  DEFAULT_TILE_HEIGHT) );
	pTile->setAnchorPoint( ccp(0, 0.5f) );
	pTile->setPosition( ccp(0.0f, 0.0f) );
	this->addChild(pTile, 0);

	// item 추가
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
	//현재 타일 소유를 물어보고 업데이트
	MO_OWNER tempOwner = CGameManager::GetInstance()->GetMapOwner(m_Index);
	if (tempOwner != m_Owner)
	{
		m_Owner = tempOwner;

		//애니메이션 등록
		CCAnimation *tileAnimation = CCAnimation::create();
		tileAnimation->setDelayPerUnit(0.2);

		tileAnimation->addSpriteFrameWithFileName("image/flower_0.png");
		tileAnimation->addSpriteFrameWithFileName("image/flower_blue.png");
		//tileAnimation->addSpriteFrameWithFileName("image/MO_tile_void_animation_02.png");
		//tileAnimation->addSpriteFrameWithFileName("image/MO_tile_void_animation_03.png");

		CCAnimate *tileAnimate = CCAnimate::create(tileAnimation);

		//애니메이션 재생이 끝난 후에 그어진 선 이미지로 교체하는 함수를 호출
		CCFiniteTimeAction *pAction = CCSequence::create(tileAnimate, 
			CCCallFunc::create(this, callfunc_selector(CMO_tile::changeImage)), NULL);

		// 기본 라인 애니메이션 재생 시간 + 타일에 할당 된 재생 순서 * 타일 애니메이션 재생 시간
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
	// 기존의 이미지를 삭제한다.
	this->removeChild(pTile, true);

	// 새롭게 설정된 소유자에 따라서 이미지 새로 생성 할당
	// 만약 m_Owner가 MO_NOBODY 상태로 진입하면 큰일남
	pTile = CCSprite::create(TileImageFileList[static_cast<int>(CGameManager::GetInstance()->GetCharacterIdByPlayerId(m_Owner))].c_str());
	pTile->setAnchorPoint( ccp(0, 0.5) );
	pTile->setPosition( ccp(0.0f, 0.0f) );
	this->addChild(pTile, 0);
}

