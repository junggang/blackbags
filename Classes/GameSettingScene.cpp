#include "MainScene.h"
#include "BackgroundLayer.h"
#include "GameSettingScene.h"

#include "SettingTitleLayer.h"

#include "GameManager.h"


USING_NS_CC;

bool CGameSettingScene::init(void)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCScene::init() )
	{
		return false;
	}

	// init state == firstStep(Select PlayerNumber and MapSize)
	isSceondStep = false;

	/////////////////////////////
	// 2. add layers
	
	// background layer
	CCLayer* BackgroundLayer = CBackgroundLayer::create();
	this->addChild(BackgroundLayer, 0);

	// 2.1 add Player Number and Map Size Select layer
	if ( CGameManager::GetInstance()->IsOnlineMode() ) // OnlineGame
	{
		// ������!! �¶����� ���� ���̾ �����ؾ� ��!
		m_PlayerNumberAndMapSizeLayer = CPlayerNumberAndMapSizeLayer::create();
		this->addChild(m_PlayerNumberAndMapSizeLayer, 1);
	}
	else // Single Game
	{
		m_PlayerNumberAndMapSizeLayer = CPlayerNumberAndMapSizeLayer::create();
		this->addChild(m_PlayerNumberAndMapSizeLayer, 1);
	}

	this->scheduleUpdate();

	return true;
}

void CGameSettingScene::update(float dt)
{
	//dt�� ���� update ���� ���� �ð�

	// 2.2 After Choose Player Number and Map Size, Go Next Step.
	if ( CGameManager::GetInstance()->IsPlayerNumberAndMapSeleted() && !isSceondStep )
	{
		AddSceondStepLayers();
		isSceondStep = true;
		this->removeChild(m_PlayerNumberAndMapSizeLayer);
	}

	// if Second Step
	if ( CGameManager::GetInstance()->IsUpdated() && isSceondStep )
	{
		//���⿡ �� ���̾���� ������Ʈ�ϴ� �ڵ带 ����
		m_SettingCharacterLayer->update();
		m_OtherPlayerStatusLayer->update();
		m_StartAndHelpButtonLayer->update();
		//������Ʈ�� ������ ��� �޾ƿͼ� ���������Ƿ� flag�� ������� false�� �����
		CGameManager::GetInstance()->SetUpdateFlag(false);
	}
	// is First Step
	else if ( CGameManager::GetInstance()->IsUpdated() && !isSceondStep )
	{
		m_PlayerNumberAndMapSizeLayer->update();
		CGameManager::GetInstance()->SetUpdateFlag(false);
	}
}

void CGameSettingScene::AddSceondStepLayers()
{
	// title layer
	CCLayer* SettingTitleLayer = CSettingTitleLayer::create();
	this->addChild(SettingTitleLayer, 1);

	// Character Select Table layer
	m_SettingCharacterLayer = CSettingCharacterLayer::create();
	this->addChild(m_SettingCharacterLayer, 1);

	// StartButton and HelpButton layer
	m_StartAndHelpButtonLayer = CStartAndHelpButtonLayer::create();
	this->addChild(m_StartAndHelpButtonLayer, 1);

	// PlayerStatusLayer
	m_OtherPlayerStatusLayer = CSettingOtherPlayerStatusLayer::create();
	this->addChild(m_OtherPlayerStatusLayer, 1);
}