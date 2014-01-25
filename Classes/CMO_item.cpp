#include "CMO_item.h"
#include "GameManager.h"

USING_NS_CC;


CMO_item::CMO_item()
{
}

CMO_item::~CMO_item()
{

}

CMO_item* CMO_item::create(const char* pszFileName, const CCRect& rect)
{
	CMO_item* pSprite = new CMO_item();
	if (pSprite && pSprite->initWithFile(pszFileName, rect))
	{
		pSprite->autorelease();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

CMO_item* CMO_item::Create(IndexedPosition indexedPosition)
{

	//아이템 종류
	static std::string objectNames[2] =
	{
		"image/PLAY_gold.png",
		"image/PLAY_trash.png",
	};

	int objectIdx = CGameManager::GetInstance()->GetItem(indexedPosition);
	CMO_item* pMapObejct = CMO_item::create(objectNames[objectIdx].c_str(), CCRectMake(0.0f, 0.0f, 100.0f,  100.0f));

	return pMapObejct;
}

void CMO_item::update( float delta )
{

}
