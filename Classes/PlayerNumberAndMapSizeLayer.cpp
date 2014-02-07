#include "PlayerNumberAndMapSizeLayer.h"
#include "GameManager.h"

USING_NS_CC;

// ������!! ��Ƽ�÷����� ��� ���� �� �ɼ��� ������ �� �־�� ��!
// ���������� �����ߴ��� flag�� �����ؼ� ������ ���� ���� �־�� ��!

bool CPlayerNumberAndMapSizeLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// Get Window Size
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	// CCMenu
	CreateMapSelectMenu(visibleSize);
	CreateNumberOfPlayerMenu(visibleSize);
	CreateNextButtonMenu(visibleSize);

	return true;
}

void CPlayerNumberAndMapSizeLayer::CreateMapSelectMenu( CCSize visibleSize )
{
	// ������! �ϴ� init�� �ְ� ���ȭ�� �� �ִٰ�..
	CCMenu *MapSelectTable = CCMenu::createWithItems(NULL, NULL);

	// make Image Buttons
	pMapSelect1 = CCMenuItemImage::create(
		"image/SETTING_5x5.png",
		"image/SETTING_5x5_selected.png",
		this,
		menu_selector(CPlayerNumberAndMapSizeLayer::SelectMapCallBack)
		);

	pMapSelect2 = CCMenuItemImage::create(
		"image/SETTING_8x7.png",
		"image/SETTING_8x7_selected.png",
		this,
		menu_selector(CPlayerNumberAndMapSizeLayer::SelectMapCallBack)
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

	//checkǥ��
	pCheck = CCSprite::create("image/SETTING_check.png");

	// Title Position : X Center + Y
	pCheck->setPosition( ccp(0, 0) );
	pCheck->setVisible(false);
	this->addChild(pCheck, 0);
}

void CPlayerNumberAndMapSizeLayer::CreateNumberOfPlayerMenu( CCSize visibleSize )
{
	CCMenu *PlayerNumberSelectTable = CCMenu::createWithItems(NULL, NULL);

	CCMenuItemImage *pPlayerNumber2 = CCMenuItemImage::create(
		"image/PLAYER_NUMBER_TWO.png",
		"image/PLAYER_NUMBER_TWO.png",
		this,
		menu_selector(CPlayerNumberAndMapSizeLayer::NumberOfPlayerCallBack)
		);

	CCMenuItemImage *pPlayerNumber3 = CCMenuItemImage::create(
		"image/PLAYER_NUMBER_THREE.png",
		"image/PLAYER_NUMBER_THREE.png",
		this,
		menu_selector(CPlayerNumberAndMapSizeLayer::NumberOfPlayerCallBack)
		);

	CCMenuItemImage *pPlayerNumber4 = CCMenuItemImage::create(
		"image/PLAYER_NUMBER_FOUR.png",
		"image/PLAYER_NUMBER_FOUR.png",
		this,
		menu_selector(CPlayerNumberAndMapSizeLayer::NumberOfPlayerCallBack)
		);

	// set Tag
	pPlayerNumber2->setTag(0);
	pPlayerNumber3->setTag(1);
	pPlayerNumber4->setTag(2);

	// add buttons to MENU
	PlayerNumberSelectTable->addChild(pPlayerNumber2);
	PlayerNumberSelectTable->addChild(pPlayerNumber3);
	PlayerNumberSelectTable->addChild(pPlayerNumber4);

	// Set Align Style
	PlayerNumberSelectTable->alignItemsHorizontallyWithPadding(10);

	// set menu Position
	PlayerNumberSelectTable->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	// add menu to this layer
	this->addChild(PlayerNumberSelectTable);
}

void CPlayerNumberAndMapSizeLayer::CreateNextButtonMenu( CCSize visibleSize )
{
	CCMenuItemImage* pNextButton = CCMenuItemImage::create(
		"image/NAMESETTING_next.png",
		"image/NAMESETTING_next_selected.png",
		this,
		menu_selector(CPlayerNumberAndMapSizeLayer::NextButtonCallBack)
		);

	pNextButton->setPosition(visibleSize.width - pNextButton->getContentSize().width,
							pNextButton->getContentSize().height);

	this->addChild(pNextButton);
}

void CPlayerNumberAndMapSizeLayer::SelectMapCallBack( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// � ��ư�� Ŭ���Ǿ������� �˾ƺ���.
	int selectedMapId = static_cast<CCMenuItem*>(pSender)->getTag();

	// � ��ư�� Ŭ���Ǿ��ٴ� ���� �˷��ش�.
	CGameManager::GetInstance()->SetMapSize( static_cast<MapSelect>(selectedMapId) );

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

void CPlayerNumberAndMapSizeLayer::NumberOfPlayerCallBack( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// �� ���� �÷��������� ����ٸ� ���� ������
	int selectedPlayerNumber = static_cast<CCMenuItem*>(pSender)->getTag();

	// ������! HardCoding^^;
	CGameManager::GetInstance()->SetPlayerNumberOfThisGame(selectedPlayerNumber + 2);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

void CPlayerNumberAndMapSizeLayer::NextButtonCallBack( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// Logic
	if ( CGameManager::GetInstance()->IsPlayerNumberAndMapSeleted() )
	{

	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}


void CPlayerNumberAndMapSizeLayer::update(void)
{
	float tempX, tempY;

	switch ( CGameManager::GetInstance()->GetSelectedMapSize() )
	{
	case MS_NOT_SELECTED:
		pCheck->setVisible(false);
		break;
	case MS_6X5:
		tempX = pMapSelect1->getPositionX() + WINDOW_WIDTH/2;
		tempY = pMapSelect1->getPositionY();
		pCheck->setPosition( ccp(tempX, tempY) );
		pCheck->setVisible( true );
		break;
	case MS_8X7:
		pCheck->setPosition(pMapSelect2->getPosition() );
		pCheck->setVisible(true);
		break;
	}
}