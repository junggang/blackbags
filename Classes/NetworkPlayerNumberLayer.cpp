#include "NetworkPlayerNumberLayer.h"
#include "GameManager.h"
#include "MainScene.h"

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
    CreateBackButtonMenu(visibleSize);
    CreateTitle();

	return true;
}

void CNetworkPlayerNumberLayer::CreateNumberOfPlayerMenu( CCSize visibleSize )
{
	CCMenu *PlayerNumberSelectTable = CCMenu::createWithItems(NULL, NULL);

	CCMenuItemImage *pPlayerNumber2 = CCMenuItemImage::create(
		SHARED_MENU1_UNSELECTED.c_str(),
		SHARED_MENU1_SELECTED.c_str(),
		this,
		menu_selector(CNetworkPlayerNumberLayer::NumberOfPlayerCallBack)
		);

	CCMenuItemImage *pPlayerNumber3 = CCMenuItemImage::create(
		SHARED_MENU2_UNSELECTED.c_str(),
		SHARED_MENU2_SELECTED.c_str(),
		this,
		menu_selector(CNetworkPlayerNumberLayer::NumberOfPlayerCallBack)
		);

	CCMenuItemImage *pPlayerNumber4 = CCMenuItemImage::create(
		SHARED_MENU3_UNSELECTED.c_str(),
		SHARED_MENU3_SELECTED.c_str(),
		this,
		menu_selector(CNetworkPlayerNumberLayer::NumberOfPlayerCallBack)
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

void CNetworkPlayerNumberLayer::CreateNextButtonMenu( CCSize visibleSize )
{
	CCMenu *NextButtonTable = CCMenu::createWithItems(NULL, NULL);

	CCMenuItemImage* pNextButton = CCMenuItemImage::create(
		SHARED_BTN_NEXT.c_str(),
		SHARED_BTN_NEXT.c_str(),
		this,
		menu_selector(CNetworkPlayerNumberLayer::NextButtonCallBack)
		);

	pNextButton->setAnchorPoint( ccp(0, 0) );
	pNextButton->setPosition( CCPoint( PLAYER_NUMBER_NEXT_IMG_POS ) );

	NextButtonTable->addChild(pNextButton);
	NextButtonTable->setPosition( ccp(0, 0) );

	this->addChild(NextButtonTable);
}

void CNetworkPlayerNumberLayer::CreateBackButtonMenu( CCSize visibleSize )
{
	CCMenu *BackButtonTable = CCMenu::createWithItems(NULL, NULL);
    
	CCMenuItemImage* pBackButton = CCMenuItemImage::create(
                                                           SHARED_BTN_BACK.c_str(),
                                                           SHARED_BTN_BACK.c_str(),
                                                           this,
                                                           menu_selector(CNetworkPlayerNumberLayer::MainSceneCallback)
                                                           );
    
	pBackButton->setAnchorPoint( ccp(0, 0) );
	pBackButton->setPosition( CCPoint( WAITING_CHANNEL_BACK_BUTTON_POSITION ) );
    
	BackButtonTable->addChild(pBackButton);
	BackButtonTable->setPosition( ccp(0, 0) );
    
	this->addChild(BackButtonTable);
}

void CNetworkPlayerNumberLayer::NumberOfPlayerCallBack( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// ∏Ó ∏Ì¿Ã «√∑π¿Ã«“¡ˆ∏¶ ∞Ò∂˙¥Ÿ∏È ∞™¿ª ¿¸¥ﬁ«‘
	int selectedPlayerNumber = static_cast<CCMenuItem*>(pSender)->getTag();

	// ¡∂Ω…«ÿ! HardCoding^^;
	CGameManager::GetInstance()->SetPlayerNumberOfThisGame(selectedPlayerNumber + 1);

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

void CNetworkPlayerNumberLayer::MainSceneCallback(cocos2d::CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    // 여기서 다음 단계로 넘어가면서 로그인을 하므로 뒤로 가면 로그아웃 할 필요는 없다.
	// CGameManager::GetInstance()->Logout();
    
	CCScene* newScene = CMainScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}


void CNetworkPlayerNumberLayer::update(float dt)
{
	// ¿Ã ∞‘¿”¿ª ∏Ó ∏Ì¿Ã «œ¥¬¡ˆ ∞°¡ÆøÕº≠ «ÿ¥Á πˆ∆∞¿ª º±≈√µ» ªÛ≈¬∑Œ ∏∏µÁ¥Ÿ.
	CCMenuItemImage* pTempPlayerNumber;

	for (int i = 2; i <= MAX_PLAYER_NUM; ++i)
	{
		// «ˆ¿Á ¿Œø¯ºˆø° «ÿ¥Á«œ¥¬ πˆ∆∞ ∆˜¿Œ≈Õ∏¶ ∞°¡Æø¬¥Ÿ.
		pTempPlayerNumber = static_cast<CCMenuItemImage*>( this->getChildByTag(PLAYER_SELECT_TABLE_TAG)->getChildByTag(i - 1) );

		// πÊæÓƒ⁄µÂ
		if ( pTempPlayerNumber == nullptr )
		{
			return;
		}
		
		// PLAYER NUMBER == i
		// PLAYER NUMBER 2 == TAG (1), 3 == TAG (2), 4 == TAG (3) ¿Ãπ«∑Œ
		// TAG == i - 1
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

void CNetworkPlayerNumberLayer::CreateTitle()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCSprite* pTitle = CCSprite::create(PLAYER_NUMBER_TITLE.c_str());
    pTitle->setPosition( CCPoint(PLAYER_NUMBER_TITLE_POS) );
	this->addChild(pTitle);
    
    CCSprite* pDescription = CCSprite::create(GAMESET01_ONLINE_DES.c_str());
    pDescription->setPosition(ccp(visibleSize.width/2,GAMESET01_ONLINE_DES_POS));
    this->addChild(pDescription);
}