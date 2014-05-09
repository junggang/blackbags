#include "PlayerNumberAndMapSizeLayer.h"
#include "GameManager.h"

USING_NS_CC;

const int PLAYER_SELECT_TABLE_TAG = 20;

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
	// �� ���� �÷��������� ����ٸ� ���� ������
	int buttonTag = static_cast<CCMenuItem*>(pSender)->getTag();

	// Tag :: 1, 2, 3 �̹Ƿ� ���� �� 2, 3, 4 �� �����Ƿ��� +1 ���Ѿ� ��
	CGameManager::GetInstance()->SetPlayerNumberOfThisGame(buttonTag + 1);
	CGameManager::GetInstance()->SetUpdateFlag(true);

	// ���⼭ �� ũ����� ���� �����ش�!
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
	// �� ������ �� ���� �ϴ��� �����ͼ� �ش� ��ư�� ���õ� ���·� �����.
	CCMenuItemImage* pTempPlayerNumber;

	for (int i = 2; i <= MAX_PLAYER_NUM; ++i)
	{
		// ���� �ο����� �ش��ϴ� ��ư �����͸� �����´�.
		pTempPlayerNumber = static_cast<CCMenuItemImage*>( this->getChildByTag(PLAYER_SELECT_TABLE_TAG)->getChildByTag(i - 1) );

		// ����ڵ�
		if ( pTempPlayerNumber == nullptr )
		{
			return;
		}

		// PLAYER NUMBER == i
		// PLAYER NUMBER : 2 == TAG (1), 3 == TAG (2), 4 == TAG (3) �̹Ƿ�
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