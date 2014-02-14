#include "SettingSecondStepLayer.h"
#include "GameManager.h"

USING_NS_CC;

bool CSettingSecondStepLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// title layer
	m_SettingTitleLayer = CSettingTitleLayer::create();
	this->addChild(m_SettingTitleLayer, 1);

	// Character Select Table layer
	m_SettingCharacterLayer = CSettingCharacterLayer::create();
	this->addChild(m_SettingCharacterLayer, 1);

	// StartButton and HelpButton layer
	m_StartAndHelpButtonLayer = CStartAndHelpButtonLayer::create();
	this->addChild(m_StartAndHelpButtonLayer, 1);

	// PlayerStatusLayer
	m_OtherPlayerStatusLayer = CSettingOtherPlayerStatusLayer::create();
	this->addChild(m_OtherPlayerStatusLayer, 1);

	return true;
}

void CSettingSecondStepLayer::update( float dt )
{
	m_SettingCharacterLayer->update();
	m_OtherPlayerStatusLayer->update();
	m_StartAndHelpButtonLayer->update();
	CGameManager::GetInstance()->SetUpdateFlag(false);
}
