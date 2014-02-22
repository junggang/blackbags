#include "NetworkPlayerNumberLayer.h"
#include "GameManager.h"

USING_NS_CC;

const int PLAYER_SELECT_TABLE_TAG = 20;

bool CNetworkPlayerNumberLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// Get Window Size
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	// CCMenu
	CreateNumberOfPlayerMenu(visibleSize);
	CreateNextButtonMenu(visibleSize);

	return true;
}

void CNetworkPlayerNumberLayer::CreateNumberOfPlayerMenu( CCSize visibleSize )
{
	CCMenu *PlayerNumberSelectTable = CCMenu::createWithItems(NULL, NULL);

	CCMenuItemImage *pPlayerNumber2 = CCMenuItemImage::create(
		"image/PLAYER_NUMBER_TWO.png",
		"image/PLAYER_NUMBER_TWO_SELECTED.png",
		this,
		menu_selector(CNetworkPlayerNumberLayer::NumberOfPlayerCallBack)
		);

	CCMenuItemImage *pPlayerNumber3 = CCMenuItemImage::create(
		"image/PLAYER_NUMBER_THREE.png",
		"image/PLAYER_NUMBER_THREE_SELECTED.png",
		this,
		menu_selector(CNetworkPlayerNumberLayer::NumberOfPlayerCallBack)
		);

	CCMenuItemImage *pPlayerNumber4 = CCMenuItemImage::create(
		"image/PLAYER_NUMBER_FOUR.png",
		"image/PLAYER_NUMBER_FOUR_SELECTED.png",
		this,
		menu_selector(CNetworkPlayerNumberLayer::NumberOfPlayerCallBack)
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

void CNetworkPlayerNumberLayer::CreateNextButtonMenu( CCSize visibleSize )
{
	CCMenu* NextButtonMenu = CCMenu::createWithItems(NULL, NULL);

	CCMenuItemImage* pNextButton = CCMenuItemImage::create(
		"image/NAMESETTING_next.png",
		"image/NAMESETTING_next_selected.png",
		this,
		menu_selector(CNetworkPlayerNumberLayer::NextButtonCallBack)
		);

	NextButtonMenu->setPosition(visibleSize.width - pNextButton->getContentSize().width,
		pNextButton->getContentSize().height);


	NextButtonMenu->addChild(pNextButton);
	
	this->addChild(NextButtonMenu);
}

void CNetworkPlayerNumberLayer::NumberOfPlayerCallBack( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// 몇 명이 플레이할지를 골랐다면 값을 전달함
	int selectedPlayerNumber = static_cast<CCMenuItem*>(pSender)->getTag();

	// 조심해! HardCoding^^;
	CGameManager::GetInstance()->SetPlayerNumberOfThisGame(selectedPlayerNumber + 2);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}

void CNetworkPlayerNumberLayer::NextButtonCallBack( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CGameManager::GetInstance()->Login();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}


void CNetworkPlayerNumberLayer::update(float dt)
{
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
		if (CGameManager::GetInstance()->GetStatusPlayerNumber(i) )
		{
			pTempPlayerNumber->selected();
		}
		else
		{
			pTempPlayerNumber->unselected();
		}
	}
}