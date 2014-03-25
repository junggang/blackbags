#include "CMO_tile.h"
#include "GameManager.h"

USING_NS_CC;

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
	
    /*
    if (CGameManager::GetInstance()->GetItem(indexedPosition) != ITEM_NOTHING)
	{
		CMO_item* pItem = CMO_item::create();
		pItem->setImage(indexedPosition);
		pItem->setAnchorPoint( ccp(0, 0.5f) );
		pItem->setPosition( ccp(0.0f, 0.0f) );
		this->addChild(pItem, 3);
	}
     */
}

void CMO_tile::update( float delta )
{
    MO_OWNER tempOwner = CGameManager::GetInstance()->GetMapOwner(m_Index);
	if (tempOwner != m_Owner)
	{
        float delayTime = 0.8f + 0.8f * (CGameManager::GetInstance()->GetTileAnimationTurn(m_Index) - 1);
        
		CGameManager::GetInstance()->SetAnimationDelay(delayTime);
        
		CCDelayTime *dt = CCDelayTime::create(delayTime);
        
		m_Owner = tempOwner;
        int characterId = CGameManager::GetInstance()->GetCharacterIdByPlayerId(m_Owner);
        
        //background grass
        pTile = CCSprite::create(PLAYSCENE_LAND_OCCUPIED.c_str());
        CCFadeIn* FadeIn = CCFadeIn::create(0.8f);
        CCAction *Fadeactions = CCSequence::create(dt, FadeIn, NULL);
        pTile->setOpacity(0);
        pTile->setAnchorPoint( ccp(0, 0.5f) );
        pTile->runAction(Fadeactions);
        addChild(pTile,1);
        
        
        //
        CCSpriteBatchNode* spritebatch = CCSpriteBatchNode::create(PLAYSCENE_LAND_ANI[characterId].c_str());
        //
        
        CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
        cache->addSpriteFramesWithFile(PLAYSCENE_LAND_ANI_PLIST[characterId].c_str());
        
        
        CCArray* animFrames = CCArray::createWithCapacity(PLAYSCENE_LAND_FRAME);
        
        char str[100] = {0};
        
        characterId++;
        
        for(int i = 1; i <= PLAYSCENE_LAND_FRAME; i++)
        {
            sprintf(str, "PLAYSCENE_ani_land_%d_000%02d.png",characterId,i);
            CCSpriteFrame* frame = cache->spriteFrameByName( str );
            animFrames->addObject(frame);
        }
        
        //first frame
        sprintf(str, "PLAYSCENE_ani_land_%d_00001.png",characterId);
        CCSprite *pElement = CCSprite::createWithSpriteFrameName(str);
        
        pElement->setAnchorPoint(ccp(0,0.5f));
        spritebatch->addChild(pElement);
        addChild(spritebatch,2);
        
        CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames,0.2f);
        CCAction* myTile = CCAnimate::create(animation);

		CCAction *actions = CCSequence::create(dt, myTile, NULL);
        
        pElement->runAction(actions);
        
        
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

