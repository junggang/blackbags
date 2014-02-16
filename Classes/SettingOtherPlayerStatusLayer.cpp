#include "SettingOtherPlayerStatusLayer.h"
#include "GameManager.h"
#include "base_nodes/CCNode.h"

enum PLAYER_TAG
{
	PLAYER_1_TAG,
	PLAYER_2_TAG,
	PLAYER_3_TAG,
	PLAYER_4_TAG,
	CURRENT_FACE_TAG
};

USING_NS_CC;
// ������!! ���� ����� �̸��� ǥ�õǴµ� �� �÷��̾� ��, �� ĳ����, Ready ����, ���嵵 ǥ���ؾ� ��
// �׷��� ȭ�鿡 ������ element�� 2���� �迭�� �� cocos2d-x ���� ǥ���� ����� ã�ƺ�����
bool CSettingOtherPlayerStatusLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
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
			PlayerNames[i] = CCTextFieldTTF::textFieldWithPlaceHolder(
				CGameManager::GetInstance()->GetPlayerName( CGameManager::GetInstance()->GetPlayerIdByCharactyerId(i) ).c_str(),
				CCSize(480,30),
				kCCTextAlignmentCenter,
				"Arial",
				20);

			PlayerNames[i]->setTag(i);

			PlayerNames[i]->setPosition(ccp(m_VisibleSize.width / 6, m_VisibleSize.height * 0.75 - 50 * i));

			this->addChild(PlayerNames[i], 3);
		}
	}

	// ĳ���Ͱ� ���õǸ� �ش� ĳ���͸� ������ �÷��̾� STATUS â�� ������ ������ �ٲ۴�.
	for ( int playerId = 0; playerId < MAX_PLAYER_NUM; ++playerId)
	{
		int characterId = CGameManager::GetInstance()->GetCharacterIdByPlayerId(playerId);
		if ( characterId != -1 ) // selected
		{
			CCSprite* pSelectedFace = CCSprite::create( CGameManager::GetInstance()->GetCharacterResultFaceFileName(playerId).c_str() );
			pSelectedFace->setTag(CURRENT_FACE_TAG);

			m_PlayerStatusFrame[playerId]->removeChildByTag(CURRENT_FACE_TAG);
			m_PlayerStatusFrame[playerId]->addChild(pSelectedFace);
		}
	}
}

void CSettingOtherPlayerStatusLayer::CreateStatusFrame(CCSize m_VisibleSize)
{
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		m_PlayerStatusFrame[i] = CCSprite::create("image/PLAYER_STATUS.png");
		switch ( i )
		{
		case PLAYER_1_TAG:
			m_PlayerStatusFrame[i]->setPosition( ccp( m_PlayerStatusFrame[i]->getContentSize().width / 2.0,
											m_PlayerStatusFrame[i]->getContentSize().height / 2.0) );
			break;
		case PLAYER_2_TAG:
			m_PlayerStatusFrame[i]->setPosition( ccp ( m_VisibleSize.width - m_PlayerStatusFrame[i]->getContentSize().width / 2.0,
											m_PlayerStatusFrame[i]->getContentSize().height / 2.0) );
			break;
		case PLAYER_3_TAG:
			m_PlayerStatusFrame[i]->setPosition( ccp( m_PlayerStatusFrame[i]->getContentSize().width / 2.0,
											m_VisibleSize.height - m_PlayerStatusFrame[i]->getContentSize().height / 2.0) );
			break;
		case PLAYER_4_TAG:
			m_PlayerStatusFrame[i]->setPosition( ccp(m_VisibleSize.width - m_PlayerStatusFrame[i]->getContentSize().width / 2.0,
											m_VisibleSize.height - m_PlayerStatusFrame[i]->getContentSize().height / 2.0) );
			break;
		default:
			break;
		}

		this->addChild( m_PlayerStatusFrame[i] );
	}

	// �⺻ ���� ����ִ´�.
	for (int i = 0; i < CGameManager::GetInstance()->GetPlayerNumberOfThisGame(); ++i )
	{
		CCSprite* pDefaultFaceImg = CCSprite::create("image/DEFAULT_FACE.png");
		pDefaultFaceImg->setPosition( ccp(pDefaultFaceImg->getContentSize().width / 2,
								pDefaultFaceImg->getContentSize().height / 2) );
		// �� ����â�� �⺻ ���� ����־�д�.
		m_PlayerStatusFrame[i]->addChild(pDefaultFaceImg);
		pDefaultFaceImg->setTag(CURRENT_FACE_TAG);
	}

	// �÷��̾� �̸� ���� 
	for (int i = 0; i < CGameManager::GetInstance()->GetPlayerNumberOfThisGame(); ++i)
	{
		extension::CCEditBox* pEditName;
		extension::CCScale9Sprite* NameEditBox = extension::CCScale9Sprite::create("image/PLAYER_NAME.png");

		pEditName = extension::CCEditBox::create( CCSize(NameEditBox->getContentSize() ),
			NameEditBox);

		pEditName->setPosition( ccp(m_PlayerStatusFrame[i]->getContentSize().width - pEditName->getContentSize().width / 2,
									pEditName->getContentSize().height / 2) );
		pEditName->setFontColor( ccYELLOW );
		pEditName->setFontSize( 1 );
		pEditName->setMaxLength( 12 );
		pEditName->setPlaceholderFontSize( 1 );
		pEditName->setPlaceHolder( CGameManager::GetInstance()->GetPlayerName(i).c_str() );
		pEditName->setReturnType( extension::kKeyboardReturnTypeDone );
		pEditName->setDelegate( this );
		pEditName->setTag( i );

		m_PlayerStatusFrame[i]->addChild( pEditName );
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
