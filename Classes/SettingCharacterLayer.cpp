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

	// set Tag : � ĳ���Ͱ� ���õƴ��� Ȯ���ؾ� �ϹǷ�
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

	// ��ư ��ġ�� ĳ���� ���� / ��� ����
	CCMenuItemImage* touchedButton = static_cast<CCMenuItemImage*>(pSender);

	// ����ڵ�
	if ( touchedButton == nullptr )
	{
		return;
	}

	// ����ڵ� : ���� ������ �ִ� ����� ������ ĳ���͸� ���� �� �� ����.
 	if ( CGameManager::GetInstance()->GetCurrentPlayerNumber() >= CGameManager::GetInstance()->GetPlayerNumberOfThisGame() )
 	{
		// ĳ���� ��Ҵ� �����ؾ� �ϹǷ� ���õ��� ���� ĳ���͸� ������ �ϸ� �׳� ���Ͻ��ѹ�����
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
		// ��� ĳ���͸� ���鼭 ���õ� ĳ�������� �ƴ��� ���������� Ȯ���Ѵ�.
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
