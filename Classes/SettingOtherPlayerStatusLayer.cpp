#include "SettingOtherPlayerStatusLayer.h"
#include "GameManager.h"
#include "base_nodes/CCNode.h"

const int PLAYER_FRAME_1_TAG = 100;
const int PLAYER_FRAME_2_TAG = 200;
const int PLAYER_FRAME_3_TAG = 300;
const int PLAYER_FRAME_4_TAG = 400;


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
	////////////////////////////////////////////////////////////
	// ������!! �� �κ��� �������̾�!! ���߿� ��������! ļ!
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		// ���� � ĳ���Ͱ� ���õ��� �ʾҴµ� ȭ�鿡 ǥ�õǰ� �ִٸ� �����Ѵ�.
		if ( !CGameManager::GetInstance()->IsCharacterSelected(i) && (this->getChildByTag(i) != NULL) )
		{
			this->removeChildByTag(i);
		}
		// ���� � ĳ���Ͱ� ���õǾ��µ� ȭ�鿡�� ǥ�õ��� �ʰ� �ִٸ� �߰��Ѵ�.
		else if ( CGameManager::GetInstance()->IsCharacterSelected(i) && (this->getChildByTag(i) == NULL) )
		{
			int playerId = CGameManager::GetInstance()->GetPlayerIdByCharactyerId(i);

			if (playerId < 0) // error
			{
				continue;
			}

			PlayerNames[i] = CCTextFieldTTF::textFieldWithPlaceHolder(
				CGameManager::GetInstance()->GetPlayerName( playerId ).c_str(),
				CCSize(480,30),
				kCCTextAlignmentCenter,
				"Arial",
				20);

			PlayerNames[i]->setTag(i);

			PlayerNames[i]->setPosition(ccp(m_VisibleSize.width / 6, m_VisibleSize.height * 0.75 - 50 * i));

			this->addChild(PlayerNames[i], 3);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	// �� �� ��
	//////////////////////////////////////////////////////////////////////////

	// ĳ���Ͱ� ���õǸ� �ش� ĳ���͸� ������ �÷��̾� STATUS â�� ������ ������ �ٲ۴�.
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

			// ����ڵ�
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

	// PlayerFrame�� ���õǾ� �ִٸ� selected()�� ������Ʈ�Ѵ�.
	int tempPlayerId = CGameManager::GetInstance()->GetPlayerFrameSelected();
	if (tempPlayerId != -1)
	{
		m_PlayerStatusFrame[ tempPlayerId ]->selected();
	}

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
    /*
    // test Function
    if ( !CGameManager::GetInstance()->IsOnlineMode() )
	{
		for (int i = 0 ; i < CGameManager::GetInstance()->GetPlayerNumberOfThisGame(); ++i)
		{
			CCSprite* readyStateImg = nullptr;
			m_PlayerStatusFrame[i]->removeChildByTag(READY_STATE_TAG);
            
			if ( true )
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
            ////////// position test ///////////
            switch (i)
            {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                default:
                    break;
            }
            
            
            
            ////////////////////////////////////
     
            
			m_PlayerStatusFrame[i]->addChild( readyStateImg );
		}
	}
    */
}

void CSettingOtherPlayerStatusLayer::CreateStatusFrame(CCSize m_VisibleSize)
{
	CCMenu* playerFrameMenu = CCMenu::create(NULL, NULL);

	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		switch ( i )
		{
		case PLAYER_1_TAG:
			m_PlayerStatusFrame[i] = CCMenuItemImage::create(
				SHARED_PLAYER_UI_BELOW_LEFT_UNSELECTED.c_str(),
				SHARED_PLAYER_UI_BELOW_LEFT_SELECTED.c_str(),
				this,
				menu_selector( CSettingOtherPlayerStatusLayer::PlayerActivateCallBack) );
			m_PlayerStatusFrame[i]->setPosition( CCPoint(GAME_SETTING_PLAYER_ONE_STATUS_POS) );
			m_PlayerStatusFrame[i]->setTag( PLAYER_FRAME_1_TAG );
			break;
		case PLAYER_2_TAG:
			m_PlayerStatusFrame[i] = CCMenuItemImage::create( 
				SHARED_PLAYER_UI_BELOW_RIGHT_UNSELECTED.c_str(),
				SHARED_PLAYER_UI_BELOW_RIGHT_SELECTED.c_str(),
				this,
				menu_selector( CSettingOtherPlayerStatusLayer::PlayerActivateCallBack) );
			m_PlayerStatusFrame[i]->setPosition( CCPoint(GAME_SETTING_PLAYER_TWO_STATUS_POS) );
			m_PlayerStatusFrame[i]->setTag( PLAYER_FRAME_2_TAG );
			break;
		case PLAYER_3_TAG:
			m_PlayerStatusFrame[i] = CCMenuItemImage::create( 
				SHARED_PLAYER_UI_UPPER_LEFT_UNSELECTED.c_str(),
				SHARED_PLAYER_UI_UPPER_LEFT_SELECTED.c_str(),
				this,
				menu_selector( CSettingOtherPlayerStatusLayer::PlayerActivateCallBack) );
			m_PlayerStatusFrame[i]->setPosition( CCPoint(GAME_SETTING_PLAYER_THREE_STATUS_POS) );
			m_PlayerStatusFrame[i]->setTag( PLAYER_FRAME_3_TAG );
			break;
		case PLAYER_4_TAG:
			m_PlayerStatusFrame[i] = CCMenuItemImage::create( 
				SHARED_PLAYER_UI_UPPER_RIGHT_UNSELECTED.c_str(),
				SHARED_PLAYER_UI_UPPER_RIGHT_SELECTED.c_str(),
				this,
				menu_selector( CSettingOtherPlayerStatusLayer::PlayerActivateCallBack) );
			m_PlayerStatusFrame[i]->setPosition( CCPoint(GAME_SETTING_PLAYER_FOUR_STATUS_POS) );
			m_PlayerStatusFrame[i]->setTag( PLAYER_FRAME_4_TAG );
			break;
		default:
			break;
		}
		m_PlayerStatusFrame[i]->setAnchorPoint( ccp(0,0) );

		// ���� ����� ������ ���� Menu�� �߰�
		if (m_PlayerStatusFrame[i] != nullptr)
		{
			playerFrameMenu->addChild( m_PlayerStatusFrame[i] );
		}
	}
	// add player status Frame
	playerFrameMenu->setAnchorPoint( ccp(0, 0) );
	playerFrameMenu->setPosition( ccp(0, 0) );
	this->addChild(playerFrameMenu);

	// �⺻ ���� ����ִ´�.
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

		// ����ڵ� : ���� ���н� ����
		if ( nullptr == pDefaultFaceImg )
		{
			return;
		}

		pDefaultFaceImg->setTag( CURRENT_FACE_TAG );
		pDefaultFaceImg->setAnchorPoint( ccp(0,0) );

		// �� ����â�� �⺻ ���� ����־�д�.
		m_PlayerStatusFrame[i]->addChild(pDefaultFaceImg);
	}

	// �÷��̾� �̸� ����â ����
	for (int i = 0; i < CGameManager::GetInstance()->GetPlayerNumberOfThisGame(); ++i)
	{
		extension::CCEditBox* pEditName;
		extension::CCScale9Sprite* NameEditBox = extension::CCScale9Sprite::create("image/PLAYER_NAME.png");

		pEditName = extension::CCEditBox::create( CCSize(NameEditBox->getContentSize() ),
			NameEditBox);

		pEditName->setPosition( ccp(m_PlayerStatusFrame[i]->getContentSize().width - pEditName->getContentSize().width / 2,
									pEditName->getContentSize().height / 2) );
		pEditName->setFontColor( ccYELLOW );
		pEditName->setFont( GAME_FONT, 30);
		pEditName->setMaxLength( 12 );
		pEditName->setPlaceholderFontSize( 1 );
		pEditName->setPlaceHolder( CGameManager::GetInstance()->GetPlayerName(i).c_str() );
		pEditName->setReturnType( extension::kKeyboardReturnTypeDone );
		pEditName->setDelegate( this );
		pEditName->setTag( i );

		m_PlayerStatusFrame[i]->addChild( pEditName );
	}

	// Ready State ǥ��
	if ( CGameManager::GetInstance()->IsOnlineMode() )
	{
		for (int i = 0; i < CGameManager::GetInstance()->GetPlayerNumberOfThisGame(); ++i)
		{
			CCSprite* readyStateImg = CCSprite::create("image/SETTING_ready_unselected.png");
			readyStateImg->setTag(READY_STATE_TAG);
			readyStateImg->setPosition(ccp(m_PlayerStatusFrame[i]->getContentSize().width - readyStateImg->getContentSize().width / 2,
				m_PlayerStatusFrame[i]->getContentSize().height - readyStateImg->getContentSize().height / 2));
			m_PlayerStatusFrame[i]->addChild( readyStateImg );
		}
	}
}

void CSettingOtherPlayerStatusLayer::editBoxEditingDidBegin( extension::CCEditBox* editBox )
{

}

void CSettingOtherPlayerStatusLayer::editBoxEditingDidEnd( extension::CCEditBox* editBox )
{
	CGameManager::GetInstance()->SetPlayerName( editBox->getTag(), editBox->getText() );
}

void CSettingOtherPlayerStatusLayer::editBoxTextChanged( extension::CCEditBox* editBox, const std::string& text )
{

}

void CSettingOtherPlayerStatusLayer::editBoxReturn( extension::CCEditBox* editBox )
{

}

void CSettingOtherPlayerStatusLayer::PlayerActivateCallBack( CCObject* pSender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	int selectedPlayerId = ( static_cast<CCMenuItem*>(pSender)->getTag() / 100 ) - 1;
	// ����ڵ�
	// selectedPlayerTag / 100 - 1== playerId
	if ( selectedPlayerId < 0 || selectedPlayerId >= MAX_PLAYER_NUM )
	{
		return;
	}

	// ���� ���õǾ� �ִ� �÷��̾ �ִٸ� ��ҽ�Ų��.
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
