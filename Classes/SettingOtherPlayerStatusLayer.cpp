#include "SettingOtherPlayerStatusLayer.h"
#include "GameManager.h"
#include "base_nodes\CCNode.h"

USING_NS_CC;
// 조심해!! 현재 사용자 이름만 표시되는데 총 플레이어 수, 고른 캐릭터, Ready 여부, 방장도 표시해야 해
// 그래서 화면에 보여줄 element가 2차원 배열일 때 cocos2d-x 에서 표현할 방법을 찾아봐야해
bool CSettingOtherPlayerStatusLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// Get Window Size
	m_VisibleSize = CCDirector::sharedDirector()->getVisibleSize();

	// Check Every Player Status
	this->update();

	return true;
}

void CSettingOtherPlayerStatusLayer::update()
{
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		// 만약 어떤 캐릭터가 선택되지 않았는데 화면에 표시되고 있다면 제거한다.
		if ( !CGameManager::GetInstance()->isCharacterSelected(i) && (this->getChildByTag(i) != NULL) )
		{
			this->removeChildByTag(i);
		}
		// 만약 어떤 캐릭터가 선택되었는데 화면에는 표시되지 않고 있다면 추가한다.
		else if ( CGameManager::GetInstance()->isCharacterSelected(i) && (this->getChildByTag(i) == NULL) )
		{
			PlayerStatus[i] = CCTextFieldTTF::textFieldWithPlaceHolder(
				CGameManager::GetInstance()->GetPlayerName(i).c_str(),
				CCSize(480,30),
				kCCTextAlignmentCenter,
				"Arial",
				20);

			PlayerStatus[i]->setTag(i);

			PlayerStatus[i]->setPosition(ccp(m_VisibleSize.width / 6, m_VisibleSize.height * 0.75 - 50 * i));

			this->addChild(PlayerStatus[i], 3);
		}

// 		if (m_PlayerStatusMenu->getChildByTag(i) != PlayerStatus[i])
// 		{
// 			m_PlayerStatusMenu->addChild(PlayerStatus[i], 3);
// 		}
	}
}
