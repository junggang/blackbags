#include "CMO_item.h"
#include "GameManager.h"

USING_NS_CC;

bool CMO_item::init()
{
	if ( !CCSprite::init() )
	{
		return false;
	}

	return true;
}
void CMO_item::update( float delta )
{

}

void CMO_item::setImage( IndexedPosition indexedPosition )
{
	int objectIdx = CGameManager::GetInstance()->GetItem(indexedPosition);
	pItem = CCSprite::create(ItemImageFileList[objectIdx].c_str());
	pItem->setAnchorPoint(ccp(0.5f, 0.5f));
	pItem->setPosition(ccp(DEFAULT_TILE_WIDTH/2,0));
	this->addChild(pItem,0);
}
