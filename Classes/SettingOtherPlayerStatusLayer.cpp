#include "SettingOtherPlayerStatusLayer.h"
#include "GameManager.h"
#include "base_nodes\CCNode.h"

USING_NS_CC;

bool CSettingOtherPlayerStatusLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// Get Window Size
	m_VisibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCMenu *m_PlayerStatusMenu;
	
	// create empty menu
	m_PlayerStatusMenu = CCMenu::createWithItems(NULL, NULL);
	// set position left - up
	m_PlayerStatusMenu->setPosition(ccp(m_VisibleSize.width / 4, m_VisibleSize.height * 0.75));
	// alignVertical
	m_PlayerStatusMenu->alignItemsVertically();
	
	this->addChild(m_PlayerStatusMenu);

	// Check Every Player Status per 1 second
	this->update();

	return true;
}

void CSettingOtherPlayerStatusLayer::update()
{
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		if ( !CGameManager::GetInstance()->isCharacterSelected(i) && this->getChildByTag(i) != NULL )
		{
			this->removeChildByTag(i);
		}
		else if ( CGameManager::GetInstance()->isCharacterSelected(i) && this->getChildByTag(i) == NULL )
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
