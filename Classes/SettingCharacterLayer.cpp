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
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); 

	// CCMenu
	CCMenu *CharacterSelectTable = CCMenu::createWithItems(NULL, NULL);

	// make Image Buttons
	CCMenuItemImage *pCharacter1 = CCMenuItemImage::create(
		"image/PLAYER_1_face.png",
		"image/PLAYER_1_selected_face.png",
		this,
		menu_selector(CSettingCharacterLayer::SelectCharacterCallBack)
		);

	CCMenuItemImage *pCharacter2 = CCMenuItemImage::create(
		"image/PLAYER_2_face.png",
		"image/PLAYER_2_selected_face.png",
		this,
		menu_selector(CSettingCharacterLayer::SelectCharacterCallBack)
		);

	CCMenuItemImage *pCharacter3 = CCMenuItemImage::create(
		"image/PLAYER_3_face.png",
		"image/PLAYER_3_selected_face.png",
		this,
		menu_selector(CSettingCharacterLayer::SelectCharacterCallBack)
		);

	CCMenuItemImage *pCharacter4 = CCMenuItemImage::create(
		"image/PLAYER_4_face.png",
		"image/PLAYER_4_selected_face.png",
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
	CharacterSelectTable->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	CharacterSelectTable->alignItemsHorizontally();

	// add to class Character Select menu
	CharacterSelectTable->setTag(CHARACTER_TABLE_TAG);
	this->addChild(CharacterSelectTable);

	return true;
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

	// 방어코드 : 현재 게임의 최대 사용자 수보다 캐릭터를 많이 고를 수 없다.
 	if ( CGameManager::GetInstance()->GetCurrentPlayerNumber() >= CGameManager::GetInstance()->GetPlayerNumberOfThisGame() )
 	{
		// 캐릭터 취소는 가능해야 하므로 선택되지 않은 캐릭터를 고르려고 하면 그냥 리턴시켜버린다
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
		// 모든 캐릭터를 돌면서 선택된 캐릭터인지 아닌지 지속적으로 확인한다.
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
