#include "SettingCharacterLayer.h"
#include "GameManager.h"

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
	// 조심해! 일단 init에 넣고 모듈화는 좀 있다가..
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
	this->addChild(CharacterSelectTable);

	return true;
}

void CSettingCharacterLayer::SelectCharacterCallBack(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// 조심해!! 현재 캐릭터 선택 / 취소가 체크박스 로직이 아니라 클릭했다 손을 떼면 취소되는 형태
	// 적당한 API가 있을 것 같은데.. 좀 더 뒤져봐야겠다.
	// 해결책 : 오버라이딩으로 새 클래스 구현하면 된답니다.
	// 어떤 버튼이 클릭되었는지를 알아본다.
	int selectedCharacterId = static_cast<CCMenuItem*>(pSender)->getTag();

	CGameManager::GetInstance()->SelectCharacter(selectedCharacterId);
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}