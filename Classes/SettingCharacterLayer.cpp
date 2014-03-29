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

	// ��ư ��ġ�� ĳ���� ���� / ��� ����
	CCMenuItemImage* touchedButton = static_cast<CCMenuItemImage*>(pSender);

	// ����ڵ�
	if ( touchedButton == nullptr )
	{
		return;
	}

	// ����ڵ� online : Ready ���¿����� ĳ���� ���� �Ұ�
	if ( CGameManager::GetInstance()->IsOnlineMode() && CGameManager::GetInstance()->IsReady() )
	{
		return;
	}
	
	// �б� 1 : ���� �÷��̾ ���õǾ� �ִ� ���¶�� �� �÷��̾�� ĳ���͸� �ش�.
	int selectedPlayerId = CGameManager::GetInstance()->GetPlayerFrameSelected();
	if ( selectedPlayerId != -1 )
	{
		CGameManager::GetInstance()->SelectCharacter(selectedPlayerId, selectedCharacterId);
		return;
	}

	// �б� 2 : ���� �÷��̾ ���õǾ� ���� �ʴٸ� ���� �÷��̾�� �Ҵ����ش�.
	// ����ڵ� Single : ���� ������ �ִ� ����� ������ ĳ���͸� ���� �� �� ����.
	if ( !CGameManager::GetInstance()->IsOnlineMode() &&
		CGameManager::GetInstance()->GetCurrentPlayerNumber() >= CGameManager::GetInstance()->GetPlayerNumberOfThisGame() )
	{
		// ĳ���� ��Ҵ� �����ؾ� �ϹǷ� ���õ��� ���� ĳ���͸� ������ �� ���� ���Ͻ��ѹ�����
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
		// ��� ĳ���͸� ���鼭 ���õ� ĳ�������� �ƴ��� Ȯ���Ѵ�.
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
