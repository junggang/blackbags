#include "SettingOtherPlayerStatusLayer.h"
#include "GameManager.h"
#include "base_nodes\CCNode.h"

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
		if ( !CGameManager::GetInstance()->isCharacterSelected(i) && (this->getChildByTag(i) != NULL) )
		{
			this->removeChildByTag(i);
		}
		// ���� � ĳ���Ͱ� ���õǾ��µ� ȭ�鿡�� ǥ�õ��� �ʰ� �ִٸ� �߰��Ѵ�.
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
		case 0:
			m_PlayerStatusFrame[i]->setPosition( ccp( m_PlayerStatusFrame[i]->getContentSize().width / 2.0,
											m_PlayerStatusFrame[i]->getContentSize().height / 2.0) );
			break;
		case 1:
			m_PlayerStatusFrame[i]->setPosition( ccp ( m_VisibleSize.width - m_PlayerStatusFrame[i]->getContentSize().width / 2.0,
											m_PlayerStatusFrame[i]->getContentSize().height / 2.0) );
			break;
		case 2:
			m_PlayerStatusFrame[i]->setPosition( ccp( m_PlayerStatusFrame[i]->getContentSize().width / 2.0,
											m_VisibleSize.height - m_PlayerStatusFrame[i]->getContentSize().height / 2.0) );
			break;
		case 3:
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
		m_PlayerStatusFrame[i]->addChild(pDefaultFaceImg);
	}

	extension::CCEditBox* pEditName;
	// 
	// 		pEditName = extension::CCEditBox::create();
	// 		pEditName->setPosition(ccp(240, 250));
	// 		pEditName->setFontColor(ccGREEN);
	// 		pEditName->setPlaceHolder("name:");
	// 		pEditName->setReturnType(kKeyboardReturnTypeDone);
	// 		pEditName->setDelegate(this);
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
