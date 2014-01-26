// #include "SettingOtherPlayerStatusLayer.h"
// #include "GameManager.h"
// 
// USING_NS_CC;
// 
// bool CSettingOtherPlayerStatusLayer::init()
// {
// 	if ( !CCLayer::init() )
// 	{
// 		return false;
// 	}
// 
// 	// Get Window Size
// 	m_VisibleSize = CCDirector::sharedDirector()->getVisibleSize();
// 	CCMenu *m_PlayerStatusMenu;
// 	
// 	// create empty menu
// 	m_PlayerStatusMenu = CCMenu::createWithItems(NULL, NULL);
// 	// set position left - up
// 	m_PlayerStatusMenu->setPosition(ccp(m_VisibleSize.width / 4, m_VisibleSize.height * 0.75));
// 	// alignVertical
// 	m_PlayerStatusMenu->alignItemsVertically();
// 	
// 	this->addChild(m_PlayerStatusMenu);
// 
// 	// Check Every Player Status per 1 second
// 	this->schedule(schedule_selector(CSettingOtherPlayerStatusLayer::callPlayerStatus), 1.0f);
// 
// 	return true;
// }
// 
// void CSettingOtherPlayerStatusLayer::callPlayerStatus()
// {
// 	// �Ŵ����κ��� ���� ���� ���� �����´�.
// 	int currentPlayerNumber = CGameManager::GetInstance()->GetPlayerNumber();
// 
// 	// ������!! ������ currentPlayerNumber ��ŭ ���� �� �´� �ɱ�? ��ũ�� ����Ʈ�� �´� �� ���⵵ �ѵ�.
// 	for (int i = 0; i < currentPlayerNumber; ++i)
// 	{
// 		PlayerStatus[i] = CCTextFieldTTF::textFieldWithPlaceHolder(
// 								CGameManager::GetInstance()->GetPlayerName(i).c_str(),
// 								CCSize(480,30),
// 								kCCTextAlignmentCenter,
// 								"Arial",
// 								20);
// 		
// 		PlayerStatus[i]->setTag(i);
// 
// 		PlayerStatus[i]->setPosition(ccp(m_VisibleSize.width / 4, m_VisibleSize.height * 0.75 - 100 * i));
// 		
// 		if (this->getChildByTag(i) != PlayerStatus[i])
// 		{
// 			this->addChild(PlayerStatus[i], 3);
// 		}
// 
// // 		if (m_PlayerStatusMenu->getChildByTag(i) != PlayerStatus[i])
// // 		{
// // 			m_PlayerStatusMenu->addChild(PlayerStatus[i], 3);
// // 		}
// 	}
// }
