#include "PlayerNumberAndMapSizeLayer.h"
#include "GameManager.h"

USING_NS_CC;

const int PLAYER_SELECT_TABLE_TAG = 20;

// 조심해!! 멀티플레이의 경우 여러 개 옵션을 선택할 수 있어야 해!
// 무엇무엇을 선택했는지 flag로 저장해서 서버에 보낼 수도 있어야 해!

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
	// 조심해! 일단 init에 넣고 모듈화는 좀 있다가..
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

	//check표시
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
		"image/PLAYER_NUMBER_TWO_SELECTED.png",
		this,
		menu_selector(CPlayerNumberAndMapSizeLayer::NumberOfPlayerCallBack)
		);

	CCMenuItemImage *pPlayerNumber3 = CCMenuItemImage::create(
		"image/PLAYER_NUMBER_THREE.png",
		"image/PLAYER_NUMBER_THREE_SELECTED.png",
		this,
		menu_selector(CPlayerNumberAndMapSizeLayer::NumberOfPlayerCallBack)
		);

	CCMenuItemImage *pPlayerNumber4 = CCMenuItemImage::create(
		"image/PLAYER_NUMBER_FOUR.png",
		"image/PLAYER_NUMBER_FOUR_SELECTED.png",
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

	// set menu Tag
	PlayerNumberSelectTable->setTag(PLAYER_SELECT_TABLE_TAG);

	// add menu to this layer
	this->addChild(PlayerNumberSelectTable);
}

void CPlayerNumberAndMapSizeLayer::CreateNextButtonMenu( CCSize visibleSize )
{
	CCMenu *NextButtonTable = CCMenu::createWithItems(NULL, NULL);

	CCMenuItemImage* pNextButton = CCMenuItemImage::create(
		"image/NAMESETTING_next.png",
		"image/NAMESETTING_next_selected.png",
		this,
		menu_selector(CPlayerNumberAndMapSizeLayer::NextButtonCallBack)
		);

	NextButtonTable->setPosition(visibleSize.width - pNextButton->getContentSize().width,
							pNextButton->getContentSize().height);

	NextButtonTable->addChild(pNextButton);

	this->addChild(NextButtonTable);
}

void CPlayerNumberAndMapSizeLayer::SelectMapCallBack( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// 어떤 버튼이 클릭되었는지를 알아본다.
	int selectedMapId = static_cast<CCMenuItem*>(pSender)->getTag();

	// 어떤 버튼이 클릭되었다는 것을 알려준다.
	CGameManager::GetInstance()->SetMapSize( static_cast<MapSelect>(selectedMapId) );

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}

void CPlayerNumberAndMapSizeLayer::NumberOfPlayerCallBack( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// 몇 명이 플레이할지를 골랐다면 값을 전달함
	int selectedPlayerNumber = static_cast<CCMenuItem*>(pSender)->getTag();

	// 조심해! HardCoding^^;
	// Tag :: 0, 1, 2 이므로 유저 수 2, 3, 4 명에 대응되려면 +2 시켜야 함
	CGameManager::GetInstance()->SetPlayerNumberOfThisGame(selectedPlayerNumber + 2);
	CGameManager::GetInstance()->SetUpdateFlag(true);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
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
		CGameManager::GetInstance()->SetNextButtonSelected();
		CGameManager::GetInstance()->SetUpdateFlag(true);
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}


void CPlayerNumberAndMapSizeLayer::update(float dt)
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

	// 이 게임을 몇 명이 하는지 가져와서 해당 버튼을 선택된 상태로 만든다.
	CCMenuItemImage* pTempPlayerNumber;

	for (int i = 2; i <= MAX_PLAYER_NUM; ++i)
	{
		// 현재 인원수에 해당하는 버튼 포인터를 가져온다.
		pTempPlayerNumber = static_cast<CCMenuItemImage*>( this->getChildByTag(PLAYER_SELECT_TABLE_TAG)->getChildByTag(i - 2) );

		// 방어코드
		if ( pTempPlayerNumber == nullptr )
		{
			return;
		}

		// PLAYER NUMBER == i
		// PLAYER NUMBER 2 == TAG (0), 3 == TAG (1), 4 == TAG (2) 이므로
		// TAG == i - 2
		if ( i == CGameManager::GetInstance()->GetPlayerNumberOfThisGame() )
		{
			pTempPlayerNumber->selected();
		}
		else
		{
			pTempPlayerNumber->unselected();
		}
	}
}