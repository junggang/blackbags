#include "SettingCharacterLayer.h"
#include "GameManager.h"

const int CHARACTER_TABLE_TAG = 10;

USING_NS_CC;

bool CSettingCharacterLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// Get Window Size
	CreateCharacters();

	return true;
}

void CSettingCharacterLayer::CreateCharacters()
{
	// CCMenu
	CCMenu *CharacterSelectTable = CCMenu::createWithItems(NULL, NULL);

	// make Image Buttons
	CCMenuItemImage *pCharacter1 = CCMenuItemImage::create(
		CHARACTER_UNSELECT_01.c_str(),
		CHARACTER_SELECT_01.c_str(),
		this,
		menu_selector(CSettingCharacterLayer::SelectCharacterCallBack)
		);

	CCMenuItemImage *pCharacter2 = CCMenuItemImage::create(
		CHARACTER_UNSELECT_02.c_str(),
		CHARACTER_SELECT_02.c_str(),
		this,
		menu_selector(CSettingCharacterLayer::SelectCharacterCallBack)
		);

	CCMenuItemImage *pCharacter3 = CCMenuItemImage::create(
		CHARACTER_UNSELECT_03.c_str(),
		CHARACTER_SELECT_03.c_str(),
		this,
		menu_selector(CSettingCharacterLayer::SelectCharacterCallBack)
		);

	CCMenuItemImage *pCharacter4 = CCMenuItemImage::create(
		CHARACTER_UNSELECT_04.c_str(),
		CHARACTER_SELECT_04.c_str(),
		this,
		menu_selector(CSettingCharacterLayer::SelectCharacterCallBack)
		);

	// set Tag : 어떤 캐릭터가 선택됐는지 확인해야 하므로
	pCharacter1->setTag(0);
	pCharacter2->setTag(1);
	pCharacter3->setTag(2);
	pCharacter4->setTag(3);

	// add Child
	CharacterSelectTable->addChild(pCharacter1, 2);
	CharacterSelectTable->addChild(pCharacter2, 2);
	CharacterSelectTable->addChild(pCharacter3, 2);
	CharacterSelectTable->addChild(pCharacter4, 2);

	// set Position
	pCharacter1->setAnchorPoint( ccp(0,0) );
	pCharacter1->setPosition( CCPoint(GAME_SETTING_CHARACTER_POS_01) );
	pCharacter2->setAnchorPoint( ccp(0,0) );
	pCharacter2->setPosition( CCPoint(GAME_SETTING_CHARACTER_POS_02) );
	pCharacter3->setAnchorPoint( ccp(0,0) );
	pCharacter3->setPosition( CCPoint(GAME_SETTING_CHARACTER_POS_03) );
	pCharacter4->setAnchorPoint( ccp(0,0) );
	pCharacter4->setPosition( CCPoint(GAME_SETTING_CHARACTER_POS_04) );

	CharacterSelectTable->setPosition( ccp(0, 0) );

	// add to class Character Select menu
	CharacterSelectTable->setTag(CHARACTER_TABLE_TAG);
	this->addChild(CharacterSelectTable);
}

void CSettingCharacterLayer::SelectCharacterCallBack(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	int selectedCharacterId = static_cast<CCMenuItem*>(pSender)->getTag();

	// 버튼 터치로 캐릭터 선택 / 취소 구현
	CCMenuItemImage* touchedButton = static_cast<CCMenuItemImage*>(pSender);

	// 방어코드
	if ( touchedButton == nullptr )
	{
		return;
	}

	// 방어코드 online : Ready 상태에서는 캐릭터 변경 불가
	if ( CGameManager::GetInstance()->IsOnlineMode() && CGameManager::GetInstance()->IsReady() )
	{
		return;
	}
	
	// 분기 1 : 만약 플레이어가 선택되어 있는 상태라면 그 플레이어에게 캐릭터를 준다.
	int selectedPlayerId = CGameManager::GetInstance()->GetPlayerFrameSelected();
	if ( selectedPlayerId != -1 )
	{
		CGameManager::GetInstance()->SelectCharacter(selectedPlayerId, selectedCharacterId);
		return;
	}

	// 분기 2 : 만약 플레이어가 선택되어 있지 않다면 다음 플레이어에게 할당해준다.
	// 방어코드 Single : 현재 게임의 최대 사용자 수보다 캐릭터를 많이 고를 수 없다.
	if ( !CGameManager::GetInstance()->IsOnlineMode() &&
		CGameManager::GetInstance()->GetCurrentPlayerNumber() >= CGameManager::GetInstance()->GetPlayerNumberOfThisGame() )
	{
		// 캐릭터 취소는 가능해야 하므로 선택되지 않은 캐릭터를 고르려고 할 때만 리턴시켜버린다
		if ( !CGameManager::GetInstance()->IsCharacterSelected(selectedCharacterId) )
		{
			return;
		}
	}

	CGameManager::GetInstance()->SelectCharacter(selectedCharacterId);
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}

void CSettingCharacterLayer::update()
{
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		// 모든 캐릭터를 돌면서 선택된 캐릭터인지 아닌지 확인한다.
		bool isSelected = CGameManager::GetInstance()->IsCharacterSelected(i);

		CCMenuItemImage* tempButton = static_cast<CCMenuItemImage*>( this->getChildByTag(CHARACTER_TABLE_TAG)->getChildByTag(i) );

		if ( isSelected )
		{
			tempButton->selected();
		}
		else
		{
			tempButton->unselected();
		}
	}
}
