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
// 	// 매니저로부터 현재 유저 수를 가져온다.
// 	int currentPlayerNumber = CGameManager::GetInstance()->GetPlayerNumber();
// 
// 	// 조심해!! 루프를 currentPlayerNumber 만큼 도는 게 맞는 걸까? 링크드 리스트면 맞는 것 같기도 한데.
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
