#include "SettingFirstStepLayer.h"
#include "GameManager.h"

USING_NS_CC;

bool CSettingFirstStepLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	m_NetworkLayer = nullptr;
	m_SingleLayer = nullptr;

	if ( CGameManager::GetInstance()->IsOnlineMode() ) // Online Mode
	{
		m_NetworkLayer = CNetworkPlayerNumberLayer::create();
		this->addChild( m_NetworkLayer );
	}
	else												// Single Mode
	{
		m_SingleLayer = CPlayerNumberAndMapSizeLayer::create();
		this->addChild( m_SingleLayer );
	}

	return true;
}

void CSettingFirstStepLayer::update( float dt )
{
	if ( CGameManager::GetInstance()->IsOnlineMode() ) // Online Mode
	{
		m_NetworkLayer->update(dt);
	}
	else												// Single Mode
	{
		m_SingleLayer->update(dt);
	}
}
