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
	CreateTitle();
	CreateNumberOfPlayerMenu(visibleSize);
	CreateNextButtonMenu(visibleSize);
	CreateBackButtonMenu(visibleSize);

	return true;
}

void CPlayerNumberAndMapSizeLayer::CreateNumberOfPlayerMenu( CCSize visibleSize )
{
	CCMenu *PlayerNumberSelectTable = CCMenu::createWithItems(NULL, NULL);

	CCMenuItemImage *pPlayerNumber2 = CCMenuItemImage::create(
		SHARED_MENU1_UNSELECTED.c_str(),
		SHARED_MENU1_SELECTED.c_str(),
		this,
		menu_selector(CPlayerNumberAndMapSizeLayer::NumberOfPlayerCallBack)
		);

	CCMenuItemImage *pPlayerNumber3 = CCMenuItemImage::create(
		SHARED_MENU2_UNSELECTED.c_str(),
		SHARED_MENU2_SELECTED.c_str(),
		this,
		menu_selector(CPlayerNumberAndMapSizeLayer::NumberOfPlayerCallBack)
		);

	CCMenuItemImage *pPlayerNumber4 = CCMenuItemImage::create(
		SHARED_MENU3_UNSELECTED.c_str(),
		SHARED_MENU3_SELECTED.c_str(),
		this,
		menu_selector(CPlayerNumberAndMapSizeLayer::NumberOfPlayerCallBack)
		);

	CCSprite *pNumberImg2 = CCSprite::create( PLAYER_NUMBER_TWO_TXT.c_str() );
	CCSprite *pNumberImg3 = CCSprite::create( PLAYER_NUMBER_THREE_TXT.c_str() );
	CCSprite *pNumberImg4 = CCSprite::create( PLAYER_NUMBER_FOUR_TXT.c_str() );

	// set Tag
	pPlayerNumber2->setTag( MS_5X5 );
	pPlayerNumber3->setTag( MS_6X6 );
	pPlayerNumber4->setTag( MS_7X7 );

	// add buttons to MENU
	PlayerNumberSelectTable->addChild( pPlayerNumber2 );
	PlayerNumberSelectTable->addChild( pPlayerNumber3 );
	PlayerNumberSelectTable->addChild( pPlayerNumber4 );
	
	// Set Item Position
	pPlayerNumber2->setAnchorPoint( ccp(0,0) );
	pPlayerNumber2->setPosition( CCPoint( PLAYER_NUMBER_TWO_IMG_POS ) );
	pPlayerNumber3->setAnchorPoint( ccp(0,0) );
	pPlayerNumber3->setPosition( CCPoint( PLAYER_NUMBER_THREE_IMG_POS ) );
	pPlayerNumber4->setAnchorPoint( ccp(0,0) );
	pPlayerNumber4->setPosition( CCPoint( PLAYER_NUMBER_FOUR_IMG_POS ) );
	pNumberImg2->setAnchorPoint( ccp(0,0) );
	pNumberImg2->setPosition( CCPoint( PLAYER_NUMBER_TWO_TXT_POS ) );
	pNumberImg3->setAnchorPoint( ccp(0,0) );
	pNumberImg3->setPosition( CCPoint( PLAYER_NUMBER_THREE_TXT_POS ) );
	pNumberImg4->setAnchorPoint( ccp(0,0) );
	pNumberImg4->setPosition( CCPoint( PLAYER_NUMBER_FOUR_TXT_POS ) );

	// set menu Position
	PlayerNumberSelectTable->setPosition( ccp(0, 0) );

	// set menu Tag
	PlayerNumberSelectTable->setTag(PLAYER_SELECT_TABLE_TAG);

	// add menu to this layer
	this->addChild(PlayerNumberSelectTable);

	// add Number Img on button
	this->addChild( pNumberImg2 );
	this->addChild( pNumberImg3 );
	this->addChild( pNumberImg4 );
}

void CPlayerNumberAndMapSizeLayer::CreateBackButtonMenu( cocos2d::CCSize visibleSize )
{

	CCMenuItemImage *pBackToMainButton = CCMenuItemImage::create(
		SHARED_BTN_BACK.c_str(),
		SHARED_BTN_BACK.c_str(),
		this,
		menu_selector(CPlayerNumberAndMapSizeLayer::MainSceneCallback)
		);

	pBackToMainButton->setAnchorPoint(ccp(0,0));
	CCMenu *pBackButton = CCMenu::create(pBackToMainButton, NULL);
	pBackButton->setPosition(SHARED_BTN_BACK_POS);
	addChild(pBackButton, 1);
}


void CPlayerNumberAndMapSizeLayer::CreateNextButtonMenu( CCSize visibleSize )
{
	CCMenu *NextButtonTable = CCMenu::createWithItems(NULL, NULL);

	CCMenuItemImage* pNextButton = CCMenuItemImage::create(
		SHARED_BTN_NEXT.c_str(),
		SHARED_BTN_NEXT.c_str(),
		this,
		menu_selector(CPlayerNumberAndMapSizeLayer::NextButtonCallBack)
		);

	pNextButton->setAnchorPoint( ccp(0, 0) );
	pNextButton->setPosition( CCPoint( PLAYER_NUMBER_NEXT_IMG_POS ) );

	NextButtonTable->addChild(pNextButton);
	NextButtonTable->setPosition( ccp(0, 0) );

	this->addChild(NextButtonTable);
}

void CPlayerNumberAndMapSizeLayer::NumberOfPlayerCallBack( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// 몇 명이 플레이할지를 골랐다면 값을 전달함
	int buttonTag = static_cast<CCMenuItem*>(pSender)->getTag();

	// Tag :: 1, 2, 3 이므로 유저 수 2, 3, 4 명에 대응되려면 +1 시켜야 함
	CGameManager::GetInstance()->SetPlayerNumberOfThisGame(buttonTag + 1);
	CGameManager::GetInstance()->SetUpdateFlag(true);

	// 여기서 맵 크기까지 같이 정해준다!
	CGameManager::GetInstance()->SetMapSize( static_cast<MapSelect>(buttonTag) );

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
	// 이 게임을 몇 명이 하는지 가져와서 해당 버튼을 선택된 상태로 만든다.
	CCMenuItemImage* pTempPlayerNumber;

	for (int i = 2; i <= MAX_PLAYER_NUM; ++i)
	{
		// 현재 인원수에 해당하는 버튼 포인터를 가져온다.
		pTempPlayerNumber = static_cast<CCMenuItemImage*>( this->getChildByTag(PLAYER_SELECT_TABLE_TAG)->getChildByTag(i - 1) );

		// 방어코드
		if ( pTempPlayerNumber == nullptr )
		{
			return;
		}

		// PLAYER NUMBER == i
		// PLAYER NUMBER : 2 == TAG (1), 3 == TAG (2), 4 == TAG (3) 이므로
		// TAG == i - 1
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

void CPlayerNumberAndMapSizeLayer::CreateTitle()
{
	CCSprite* pTitle = CCSprite::create(PLAYER_NUMBER_TITLE.c_str());
	pTitle->setPosition( CCPoint(PLAYER_NUMBER_TITLE_POS) );
	this->addChild(pTitle);
}

void CPlayerNumberAndMapSizeLayer::MainSceneCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->popScene();
}