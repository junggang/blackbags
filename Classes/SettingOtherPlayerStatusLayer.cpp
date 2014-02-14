#include "SettingOtherPlayerStatusLayer.h"
#include "GameManager.h"
#include "base_nodes\CCNode.h"

enum PLAYER_TAG
{
	PLAYER_1_TAG,
	PLAYER_2_TAG,
	PLAYER_3_TAG,
	PLAYER_4_TAG
};

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

	CreateStatusFrame(m_VisibleSize);

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
			PlayerNames[i] = CCTextFieldTTF::textFieldWithPlaceHolder(
				CGameManager::GetInstance()->GetPlayerName(i).c_str(),
				CCSize(480,30),
				kCCTextAlignmentCenter,
				"Arial",
				20);

			PlayerNames[i]->setTag(i);

			PlayerNames[i]->setPosition(ccp(m_VisibleSize.width / 6, m_VisibleSize.height * 0.75 - 50 * i));

			this->addChild(PlayerNames[i], 3);
		}
	}
}

void CSettingOtherPlayerStatusLayer::CreateStatusFrame(CCSize m_VisibleSize)
{
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		m_PlayerStatusFrame[i] = CCSprite::create("image/PLAYER_STATUS.png");
		switch(i)
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

	for (int i = 0; i < CGameManager::GetInstance()->GetPlayerNumberOfThisGame(); ++i )
	{
		CCSprite* pDefaultFaceImg = CCSprite::create("image/DEFAULT_FACE.png");
		pDefaultFaceImg->setPosition( ccp(pDefaultFaceImg->getContentSize().width / 2,
								pDefaultFaceImg->getContentSize().height / 2) );
		// 각 상태창에 기본 얼굴을 집어넣어둔다.
		m_PlayerStatusFrame[i]->addChild(pDefaultFaceImg);
	}

	for (int i = 0; i < CGameManager::GetInstance()->GetPlayerNumberOfThisGame(); ++i)
	{
		extension::CCEditBox* pEditName;
		extension::CCScale9Sprite* NameEditBox = extension::CCScale9Sprite::create("image/PLAYER_NAME.png");

		pEditName = extension::CCEditBox::create( NameEditBox->getContentSize() , NameEditBox );

		pEditName->setPosition( ccp(m_PlayerStatusFrame[i]->getContentSize().width + pEditName->getContentSize().width / 2,
			m_PlayerStatusFrame[i]->getContentSize().height + pEditName->getContentSize().height / 2) );
		pEditName->setFontSize(10);
		pEditName->setFontColor(ccYELLOW);
		pEditName->setPlaceHolder("name:");
		pEditName->setReturnType(extension::kKeyboardReturnTypeDone);
		pEditName->setDelegate(this);

		m_PlayerStatusFrame[i]->addChild(pEditName);
	}
	

}

void CSettingOtherPlayerStatusLayer::editBoxEditingDidBegin( extension::CCEditBox* editBox )
{

}

void CSettingOtherPlayerStatusLayer::editBoxEditingDidEnd( extension::CCEditBox* editBox )
{

}

void CSettingOtherPlayerStatusLayer::editBoxTextChanged( extension::CCEditBox* editBox, const std::string& text )
{

}

void CSettingOtherPlayerStatusLayer::editBoxReturn( extension::CCEditBox* editBox )
{

}
