#include "SettingMapLayer.h"
#include "GameManager.h"

USING_NS_CC;

bool CSettingMapLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// Get Window Size
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	// CCMenu
	// 조심해! 일단 init에 넣고 모듈화는 좀 있다가..
	CCMenu *MapSelectTable = CCMenu::createWithItems(NULL, NULL);

	// make Image Buttons
	pMapSelect1 = CCMenuItemImage::create(
		"image/SETTING_5x5.png",
		"image/SETTING_5x5_selected.png",
		this,
		menu_selector(CSettingMapLayer::SelectMapCallBack)
		);

	pMapSelect2 = CCMenuItemImage::create(
		"image/SETTING_8x7.png",
		"image/SETTING_8x7_selected.png",
		this,
		menu_selector(CSettingMapLayer::SelectMapCallBack)
		);

	// set Tag
	pMapSelect1->setTag( MS_6X5 );
	pMapSelect2->setTag( MS_8X7 );

	// add child
	MapSelectTable->addChild(pMapSelect1);
	MapSelectTable->addChild(pMapSelect2);

	// set position
	MapSelectTable->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 2 * pMapSelect1->getContentSize().width);
	MapSelectTable->alignItemsHorizontally();

	// add menu to this class
	this->addChild(MapSelectTable);

	//check표시
	pCheck = CCSprite::create("image/SETTING_check.png");
	// Title Position : X Center + Y
	pCheck->setPosition(ccp(0, 0) );
	pCheck->setVisible(false);
	this->addChild(pCheck, 0);

	return true;
}

void CSettingMapLayer::SelectMapCallBack( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// 어떤 버튼이 클릭되었는지를 알아본다.
	int selectedMapId = static_cast<CCMenuItem*>(pSender)->getTag();

	CGameManager::GetInstance()->SetMapSize( static_cast<MapSelect>(selectedMapId) );

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}

void CSettingMapLayer::update(void)
{
	float tempX, tempY;

	switch (CGameManager::GetInstance()->GetSelectedMapSize() )
	{
	case MS_NOT_SELECTED:
		pCheck->setVisible(false);
		break;
	case MS_6X5:
		tempX = pMapSelect1->getPositionX() + WINDOW_WIDTH/2;
		tempY = pMapSelect1->getPositionY();
		pCheck->setPosition(ccp(tempX, tempY) );
		pCheck->setVisible(true);
		break;
	case MS_8X7:
		pCheck->setPosition(pMapSelect2->getPosition() );
		pCheck->setVisible(true);
		break;
	}
}