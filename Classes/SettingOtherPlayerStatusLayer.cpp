#include "SettingOtherPlayerStatusLayer.h"
#include "GameManager.h"
#include "base_nodes/CCNode.h"

const int PLAYER_FRAME_1_TAG = 100;
const int PLAYER_FRAME_2_TAG = 200;
const int PLAYER_FRAME_3_TAG = 300;
const int PLAYER_FRAME_4_TAG = 400;

const int PLAYER_READYSTATE_TAG = 1000;

enum PLAYER_TAG
{
	PLAYER_1_TAG,
	PLAYER_2_TAG,
	PLAYER_3_TAG,
	PLAYER_4_TAG,
	CURRENT_FACE_TAG,
	READY_STATE_TAG
};

USING_NS_CC;

bool CSettingOtherPlayerStatusLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	// init m_PlayerStatusFrame
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		m_PlayerStatusFrame[i] = nullptr;
	}

	// Get Window Size
	m_VisibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CreateStatusFrame(m_VisibleSize);

	// Check Every Player Status
	this->update();

	return true;
}

void CSettingOtherPlayerStatusLayer::update()
{
    // online mode only
    UpdateNamesToPlayerFrame();
    UpdateReadyStateToPlayerFrame();
    
    // update status frames if select characters
    if ( CGameManager::GetInstance()->IsOnlineMode() )
    {
        UpdatePlayerAndCharacterPairsOnline();
    }
    else
    {
        UpdatePlayerAndCharacterPairsOffline();
    }
    
	// PlayerFrame이 선택되어 있다면 selected()로 업데이트한다.
	int tempPlayerId = CGameManager::GetInstance()->GetPlayerFrameSelected();
	if (tempPlayerId != -1)
	{
		m_PlayerStatusFrame[ tempPlayerId ]->selected();
	}
    
    // update Ready status
	if ( CGameManager::GetInstance()->IsOnlineMode() )
	{
		for (int i = 0 ; i < CGameManager::GetInstance()->GetPlayerNumberOfThisGame(); ++i)
		{
			CCSprite* readyStateImg = nullptr;
			m_PlayerStatusFrame[i]->removeChildByTag(READY_STATE_TAG);

			if ( CGameManager::GetInstance()->IsReady(i) )
			{
				readyStateImg = CCSprite::create(PLAYER_STATUS_READY_IMG.c_str());
			}
			else
			{
				readyStateImg = CCSprite::create(PLAYER_STATUS_READY_IMG.c_str());
			}

			// if load image failed
			if (nullptr == readyStateImg)
			{
				continue;
			}

			readyStateImg->setTag(READY_STATE_TAG);

			readyStateImg->setPosition(ccp(m_PlayerStatusFrame[i]->getContentSize().width - readyStateImg->getContentSize().width / 2,
				m_PlayerStatusFrame[i]->getContentSize().height - readyStateImg->getContentSize().height / 2));

			m_PlayerStatusFrame[i]->addChild( readyStateImg );
		}
	}
}

void CSettingOtherPlayerStatusLayer::CreateStatusFrame(CCSize m_VisibleSize)
{
	
    CreateEmptyFrame();
    
    if ( CGameManager::GetInstance()->IsOnlineMode() )
    {
        CreateOnlineEmptyPortrait();
    }
    else
    {
        CreateOfflineEmptyPortrait();
    }
}

void CSettingOtherPlayerStatusLayer::PlayerActivateCallBack( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	int selectedPlayerId = ( static_cast<CCMenuItem*>(pSender)->getTag() / 100 ) - 1;
	// πÊæÓƒ⁄µÂ
	// selectedPlayerTag / 100 - 1== playerId
	if ( selectedPlayerId < 0 || selectedPlayerId >= MAX_PLAYER_NUM )
	{
		return;
	}

	// ∏∏æ‡ º±≈√µ«æÓ ¿÷¥¬ «√∑π¿ÃæÓ∞° ¿÷¥Ÿ∏È √Îº“Ω√≈≤¥Ÿ.
	int tempPlayerId = CGameManager::GetInstance()->GetPlayerFrameSelected();
	if ( tempPlayerId != -1 )
	{
			CGameManager::GetInstance()->SetPlayerFrameSelected(tempPlayerId, false);
			m_PlayerStatusFrame[ tempPlayerId ]->unselected();
	}

	CGameManager::GetInstance()->SetPlayerFrameSelected(selectedPlayerId, true);
	m_PlayerStatusFrame[ selectedPlayerId ]->selected();

	CGameManager::GetInstance()->SetUpdateFlag(true);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
#endif
}


void CSettingOtherPlayerStatusLayer::UpdatePlayerAndCharacterPairsOnline()
{
    // 캐릭터가 선택되면 해당 캐릭터를 선택한 플레이어 STATUS 창의 프로필 사진을 바꾼다.
	for ( int playerId = 0; playerId < MAX_PLAYER_NUM; ++playerId)
	{
		int characterId = CGameManager::GetInstance()->GetCharacterIdByPlayerId(playerId);
		if ( characterId != -1 ) // selected
		{
			// create selected face
			CCSprite* pSelectedFace = nullptr;
            
			switch (playerId)
			{
                case 0: // player 1 :: below left
                    pSelectedFace = CCSprite::create( PlayerUiCharacterBelowLeft[characterId].c_str() );
                    break;
                case 1: // player 2 :: below right
                    pSelectedFace = CCSprite::create( PlayerUiCharacterBelowRight[characterId].c_str() );
                    break;
                case 2: // player 3 :: upper left
                    pSelectedFace = CCSprite::create( PlayerUiCharacterUpperLeft[characterId].c_str() );
                    break;
                case 3: // player 4 :: upper right
                    pSelectedFace = CCSprite::create( PlayerUiCharacterUpperRight[characterId].c_str() );
                    break;
			}
            
            // 방어코드
			if ( nullptr == pSelectedFace )
			{
				return;
			}
            
			// set position
			pSelectedFace->setPosition( ccp(0, 0) );
			pSelectedFace->setAnchorPoint( ccp(0, 0) );
            
			pSelectedFace->setTag(CURRENT_FACE_TAG);
            
			m_PlayerStatusFrame[playerId]->removeChildByTag(CURRENT_FACE_TAG);
			m_PlayerStatusFrame[playerId]->addChild(pSelectedFace);
		}
	}
}

void CSettingOtherPlayerStatusLayer::UpdatePlayerAndCharacterPairsOffline()
{
    // 캐릭터가 선택되면 해당 캐릭터를 선택한 플레이어 STATUS 창의 프로필 사진을 바꾼다.
	for ( int playerId = 0; playerId < MAX_PLAYER_NUM; ++playerId)
	{
		int characterId = CGameManager::GetInstance()->GetCharacterIdByPlayerId(playerId);
		if ( characterId != -1 ) // selected
		{
			// create selected face
			CCSprite* pSelectedFace = nullptr;
            
			switch (playerId)
			{
                case 0: // player 1 :: below left
                    pSelectedFace = CCSprite::create( PlayerUiCharacterBelowLeftOffline[characterId].c_str() );
                    break;
                case 1: // player 2 :: below right
                    pSelectedFace = CCSprite::create( PlayerUiCharacterBelowRightOffline[characterId].c_str() );
                    break;
                case 2: // player 3 :: upper left
                    pSelectedFace = CCSprite::create( PlayerUiCharacterUpperLeftOffline[characterId].c_str() );
                    break;
                case 3: // player 4 :: upper right
                    pSelectedFace = CCSprite::create( PlayerUiCharacterUpperRightOffline[characterId].c_str() );
                    break;
			}
            
            // 방어코드
			if ( nullptr == pSelectedFace )
			{
				return;
			}
            
			// set position
			pSelectedFace->setPosition( ccp(0, 0) );
			pSelectedFace->setAnchorPoint( ccp(0, 0) );
            
			pSelectedFace->setTag(CURRENT_FACE_TAG);
            
			m_PlayerStatusFrame[playerId]->removeChildByTag(CURRENT_FACE_TAG);
			m_PlayerStatusFrame[playerId]->addChild(pSelectedFace);
		}
	}
}

void CSettingOtherPlayerStatusLayer::CreateOfflineEmptyPortrait()
{
    
	// ±‚∫ª æÛ±º¿ª ¡˝æÓ≥÷¥¬¥Ÿ.
	for (int i = 0; i < CGameManager::GetInstance()->GetPlayerNumberOfThisGame(); ++i )
	{
		CCSprite* pDefaultFaceImg = nullptr;
        
		switch (i)
		{
            case PLAYER_1_TAG:
                pDefaultFaceImg = CCSprite::create( PlayerUiCharacterBelowLeftOffline[4].c_str() );
                pDefaultFaceImg->setPosition( CCPoint(0, 0) );
                break;
            case PLAYER_2_TAG:
                pDefaultFaceImg = CCSprite::create( PlayerUiCharacterBelowRightOffline[4].c_str() );
                pDefaultFaceImg->setPosition( CCPoint(0, 0) );
                break;
            case PLAYER_3_TAG:
                pDefaultFaceImg = CCSprite::create( PlayerUiCharacterUpperLeftOffline[4].c_str() );
                pDefaultFaceImg->setPosition( CCPoint(0, 0) );
                break;
            case PLAYER_4_TAG:
                pDefaultFaceImg = CCSprite::create( PlayerUiCharacterUpperRightOffline[4].c_str() );
                pDefaultFaceImg->setPosition( CCPoint(0, 0) );
                break;
            default:
                break;
		}
        
		// πÊæÓƒ⁄µÂ : ª˝º∫ Ω«∆–Ω√ ∏Æ≈œ
		if ( nullptr == pDefaultFaceImg )
		{
			return;
		}
        
		pDefaultFaceImg->setTag( CURRENT_FACE_TAG );
		pDefaultFaceImg->setAnchorPoint( ccp(0,0) );
        
		// ∞¢ ªÛ≈¬√¢ø° ±‚∫ª æÛ±º¿ª ¡˝æÓ≥÷æÓµ–¥Ÿ.
		m_PlayerStatusFrame[i]->addChild(pDefaultFaceImg);
	}
}

void CSettingOtherPlayerStatusLayer::CreateOnlineEmptyPortrait()
{
    
	// ±‚∫ª æÛ±º¿ª ¡˝æÓ≥÷¥¬¥Ÿ.
	for (int i = 0; i < CGameManager::GetInstance()->GetPlayerNumberOfThisGame(); ++i )
	{
		CCSprite* pDefaultFaceImg = nullptr;
        
		switch (i)
		{
            case PLAYER_1_TAG:
                pDefaultFaceImg = CCSprite::create( PlayerUiCharacterBelowLeft[4].c_str() );
                pDefaultFaceImg->setPosition( CCPoint(0, 0) );
                break;
            case PLAYER_2_TAG:
                pDefaultFaceImg = CCSprite::create( PlayerUiCharacterBelowRight[4].c_str() );
                pDefaultFaceImg->setPosition( CCPoint(0, 0) );
                break;
            case PLAYER_3_TAG:
                pDefaultFaceImg = CCSprite::create( PlayerUiCharacterUpperLeft[4].c_str() );
                pDefaultFaceImg->setPosition( CCPoint(0, 0) );
                break;
            case PLAYER_4_TAG:
                pDefaultFaceImg = CCSprite::create( PlayerUiCharacterUpperRight[4].c_str() );
                pDefaultFaceImg->setPosition( CCPoint(0, 0) );
                break;
            default:
                break;
		}
        
		// πÊæÓƒ⁄µÂ : ª˝º∫ Ω«∆–Ω√ ∏Æ≈œ
		if ( nullptr == pDefaultFaceImg )
		{
			return;
		}
        
		pDefaultFaceImg->setTag( CURRENT_FACE_TAG );
		pDefaultFaceImg->setAnchorPoint( ccp(0,0) );
        
		// ∞¢ ªÛ≈¬√¢ø° ±‚∫ª æÛ±º¿ª ¡˝æÓ≥÷æÓµ–¥Ÿ.
		m_PlayerStatusFrame[i]->addChild(pDefaultFaceImg);
	}
}

void CSettingOtherPlayerStatusLayer::UpdateNamesToPlayerFrame()
{
    // update name works online-mode only
    if (!CGameManager::GetInstance()->IsOnlineMode())
    {
        //return;
    }
    
    for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		// 만약 어떤 캐릭터가 선택되지 않았는데 화면에 이름이 표시되고 있다면 제거한다.
		if ( !CGameManager::GetInstance()->IsCharacterSelected(i) && (this->getChildByTag(i) != NULL) )
		{
			this->removeChildByTag(i);
		}
		// 만약 어떤 캐릭터가 선택되었는데 화면에는 이름이 표시되지 않고 있다면 추가한다.
		else if ( CGameManager::GetInstance()->IsCharacterSelected(i) && (this->getChildByTag(i) == NULL) )
		{
			int playerId = CGameManager::GetInstance()->GetPlayerIdByCharactyerId(i);
            
			if (playerId < 0) // error
			{
				continue;
			}
            
			PlayerNames[i] = CCLabelTTF::create(CGameManager::GetInstance()->GetPlayerName(playerId).c_str(),
                                                GAME_FONT,
                                                50,
                                                CCSizeMake(400, 100), kCCTextAlignmentLeft);
			PlayerNames[i]->setTag(i);
            
            int playerNumber = CGameManager::GetInstance()->GetPlayerIdByCharactyerId(i);
            switch(playerNumber)
            {
                case 0:
                    PlayerNames[i]->setPosition( ccp( CCPoint(GAME_SETTING_PLAYER_ONE_STATUS_POS).x+300.0f, CCPoint(GAME_SETTING_PLAYER_ONE_STATUS_POS).y + 50.0f ) );
                    break;
                case 1:
                    PlayerNames[i]->setPosition( ccp( CCPoint(GAME_SETTING_PLAYER_TWO_STATUS_POS).x+100.0f, CCPoint(GAME_SETTING_PLAYER_TWO_STATUS_POS).y + 50.0f ) );
                    break;
                case 2:
                     PlayerNames[i]->setPosition( ccp( CCPoint(GAME_SETTING_PLAYER_THREE_STATUS_POS).x+300.0f, CCPoint(GAME_SETTING_PLAYER_THREE_STATUS_POS).y + 150.0f ) );
                    break;
                case 3:
                     PlayerNames[i]->setPosition( ccp( CCPoint(GAME_SETTING_PLAYER_FOUR_STATUS_POS).x+100.0f, CCPoint(GAME_SETTING_PLAYER_FOUR_STATUS_POS).y + 150.0f ) );
                    break;
                default:
                    break;
            }
            PlayerNames[i]->setAnchorPoint(ccp(0, 0));
			this->addChild(PlayerNames[i], 3);
		}
	}
}


void CSettingOtherPlayerStatusLayer::CreateEmptyFrame()
{
    CCMenu* playerFrameMenu = CCMenu::create(NULL, NULL);
    
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		switch ( i )
		{
            case PLAYER_1_TAG:
            {
                m_PlayerStatusFrame[i] = CCMenuItemImage::create(SHARED_PLAYER_UI_BELOW_LEFT_UNSELECTED.c_str(),
                                                                 SHARED_PLAYER_UI_BELOW_LEFT_SELECTED.c_str(),
                                                                 this,
                                                                 menu_selector( CSettingOtherPlayerStatusLayer::PlayerActivateCallBack) );
                m_PlayerStatusFrame[i]->setPosition( CCPoint(GAME_SETTING_PLAYER_ONE_STATUS_POS) );
                
                m_PlayerStatusFrame[i]->setTag( PLAYER_FRAME_1_TAG );
                
                // create ready state button (Multiplay Only)
                CCSprite* readyStateImg = CCSprite::create( GAME_SETTING_PLAYER_READY_STATE_LEFT.c_str() );
                readyStateImg->setAnchorPoint( ccp(0,0) );
                readyStateImg->setTag(READY_STATE_TAG);
                m_PlayerStatusFrame[i]->addChild(readyStateImg);
                
                // ready state img == invisible when initialized
                readyStateImg->setVisible(false);
                break;
            }
            case PLAYER_2_TAG:
            {
                m_PlayerStatusFrame[i] = CCMenuItemImage::create(
                                                                 SHARED_PLAYER_UI_BELOW_RIGHT_UNSELECTED.c_str(),
                                                                 SHARED_PLAYER_UI_BELOW_RIGHT_SELECTED.c_str(),
                                                                 this,
                                                                 menu_selector( CSettingOtherPlayerStatusLayer::PlayerActivateCallBack) );
                m_PlayerStatusFrame[i]->setPosition( CCPoint(GAME_SETTING_PLAYER_TWO_STATUS_POS) );
                m_PlayerStatusFrame[i]->setTag( PLAYER_FRAME_2_TAG );
                
                // create ready state button (Multiplay Only)
                CCSprite* readyStateImg = CCSprite::create( GAME_SETTING_PLAYER_READY_STATE_RIGHT.c_str() );
                readyStateImg->setAnchorPoint( ccp(0,0) );
                readyStateImg->setTag(READY_STATE_TAG);
                m_PlayerStatusFrame[i]->addChild(readyStateImg);
                
                // ready state img == invisible when initialized
                readyStateImg->setVisible(false);
                break;
            }
            case PLAYER_3_TAG:
            {
                m_PlayerStatusFrame[i] = CCMenuItemImage::create(
                                                                 SHARED_PLAYER_UI_UPPER_LEFT_UNSELECTED.c_str(),
                                                                 SHARED_PLAYER_UI_UPPER_LEFT_SELECTED.c_str(),
                                                                 this,
                                                                 menu_selector( CSettingOtherPlayerStatusLayer::PlayerActivateCallBack) );
                m_PlayerStatusFrame[i]->setPosition( CCPoint(GAME_SETTING_PLAYER_THREE_STATUS_POS) );
                m_PlayerStatusFrame[i]->setTag( PLAYER_FRAME_3_TAG );
                
                // create ready state button (Multiplay Only)
                CCSprite* readyStateImg = CCSprite::create( GAME_SETTING_PLAYER_READY_STATE_LEFT.c_str() );
                readyStateImg->setAnchorPoint( ccp(0,0) );
                readyStateImg->setPosition(ccp(0, 100));
                readyStateImg->setTag(READY_STATE_TAG);
                m_PlayerStatusFrame[i]->addChild(readyStateImg);
                
                // ready state img == invisible when initialized
                readyStateImg->setVisible(false);
                break;
            }
            case PLAYER_4_TAG:
            {
                m_PlayerStatusFrame[i] = CCMenuItemImage::create(
                                                                 SHARED_PLAYER_UI_UPPER_RIGHT_UNSELECTED.c_str(),
                                                                 SHARED_PLAYER_UI_UPPER_RIGHT_SELECTED.c_str(),
                                                                 this,
                                                                 menu_selector( CSettingOtherPlayerStatusLayer::PlayerActivateCallBack) );
                m_PlayerStatusFrame[i]->setPosition( CCPoint(GAME_SETTING_PLAYER_FOUR_STATUS_POS) );
                m_PlayerStatusFrame[i]->setTag( PLAYER_FRAME_4_TAG );
                
                // create ready state button (Multiplay Only)
                CCSprite* readyStateImg = CCSprite::create( GAME_SETTING_PLAYER_READY_STATE_RIGHT.c_str() );
                readyStateImg->setAnchorPoint( ccp(0,0) );
                readyStateImg->setPosition(ccp(0, 100));
                readyStateImg->setTag(READY_STATE_TAG);
                m_PlayerStatusFrame[i]->addChild(readyStateImg);
                
                // ready state img == invisible when initialized
                readyStateImg->setVisible(false);
                break;
            }
            default:
                break;
		}
		m_PlayerStatusFrame[i]->setAnchorPoint( ccp(0,0) );
        
		// ∞™¿Ã ¡¶¥Î∑Œ µÈæÓø‘¿ª ∂ß∏∏ Menuø° √ﬂ∞°
		if (m_PlayerStatusFrame[i] != nullptr)
		{
			playerFrameMenu->addChild( m_PlayerStatusFrame[i] );
		}
	}
	// add player status Frame
	playerFrameMenu->setAnchorPoint( ccp(0, 0) );
	playerFrameMenu->setPosition( ccp(0, 0) );
	this->addChild(playerFrameMenu);
}


void CSettingOtherPlayerStatusLayer::UpdateReadyStateToPlayerFrame()
{
    if (!CGameManager::GetInstance()->IsOnlineMode())
    {
        return;
    }
    
    for (int i = 0; i < MAX_PLAYER_NUM; ++i)
    {
        CCSprite* ready = (CCSprite*)m_PlayerStatusFrame[i]->getChildByTag(READY_STATE_TAG);
        // if player i is ready, show ready image
        if (CGameManager::GetInstance()->IsReady(i))
        {
            if (ready != nullptr)
            {
                ready->setVisible(true);
            }
        }
        else
        {
            if (ready != nullptr)
            {
                ready->setVisible(false);
            }
        }
    }
}