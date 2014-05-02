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

	// ¡÷¿Œæ¯¥¬ ¿ÃπÃ¡ˆ∏¶ ≥÷æÓ¡ÿ¥Ÿ.
	// (¡÷¿Œ¿Ã æ¯¿ª ∂ß æ∆π´∞Õµµ æ» ∫∏¿Œ¥Ÿ∏È √ﬂ∞° æ» «œ∏È µ»¥Ÿ)
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
        // 애니메이션이 시작하는 시간은 라인이 재생되는 시간 + 인덱스가 낮은 타일들이 모두 그려지는 시간(애니메이션이 있는 타일은 인덱스 1부터 시작하므로 자신의 인덱스에서 1을 빼서 재생시간 곱함)
        float delayTime = PLAYSCENE_ANIMATION_TIME + PLAYSCENE_ANIMATION_TIME * (CGameManager::GetInstance()->GetTileAnimationTurn(m_Index) - 1);
        
        // 애니메이션이 끝나는 시간을 지정함 
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
        
        CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames,PLAYSCENE_ANIMATION_TIME/PLAYSCENE_LAND_FRAME);
        CCAction* myTile = CCAnimate::create(animation);

		CCAction *actions = CCSequence::create(dt, myTile, NULL);
        
        pElement->runAction(actions);
        
        
	}
    
    
}

void CMO_tile::changeImage()
{
	// ±‚¡∏¿« ¿ÃπÃ¡ˆ∏¶ ªË¡¶«—¥Ÿ.
	this->removeChild(pTile, true);

	// ªı∑”∞‘ º≥¡§µ» º“¿Ø¿⁄ø° µ˚∂Ûº≠ ¿ÃπÃ¡ˆ ªı∑Œ ª˝º∫ «“¥Á
	// ∏∏æ‡ m_Owner∞° MO_NOBODY ªÛ≈¬∑Œ ¡¯¿‘«œ∏È ≈´¿œ≥≤
	pTile = CCSprite::create(TileImageFileList[static_cast<int>(CGameManager::GetInstance()->GetCharacterIdByPlayerId(m_Owner))].c_str());
	pTile->setAnchorPoint( ccp(0, 0.5) );
	pTile->setPosition( ccp(0.0f, 0.0f) );
	this->addChild(pTile, 0);
}

