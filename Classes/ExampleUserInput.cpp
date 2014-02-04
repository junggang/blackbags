#include "MainScene.h"
#include "BackgroundLayer.h"
#include "GameSettingScene.h"
#include "SettingTitleLayer.h"
#include "StartAndHelpButtonLayer.h"
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

	/////////////////////////////
	// 2. add layers
	
	// background layer
	CCLayer* BackgroundLayer = CBackgroundLayer::create();
	this->addChild(BackgroundLayer, 0);

	// title layer
	CCLayer* SettingTitleLayer = CSettingTitleLayer::create();
	this->addChild(SettingTitleLayer, 1);

	// Character Select Table layer
	SettingCharacterLayer = CSettingCharacterLayer::create();
	this->addChild(SettingCharacterLayer, 1);

	// map select table layer
	SettingMapLayer = CSettingMapLayer::create();
	this->addChild(SettingMapLayer, 1);

	// StartButton and HelpButton layer
	CStartAndHelpButtonLayer* StartAndHelpButtonLayer = CStartAndHelpButtonLayer::create();
	this->addChild(StartAndHelpButtonLayer, 1);

	// PlayerStatusLayer
	OtherPlayerStatusLayer = CSettingOtherPlayerStatusLayer::create();
	this->addChild(OtherPlayerStatusLayer, 1);

	this->scheduleUpdate();

	return true;
}

void CGameSettingScene::update(float dt)
{
	//dt�� ���� update ���� ���� �ð�

	if (CGameManager::GetInstance()->IsUpdated() )
	{
		//���⿡ �� ���̾���� ������Ʈ�ϴ� �ڵ带 ����
		//�� ���̾�� ������Ʈ �Լ� ������ ��
		SettingCharacterLayer->update(dt);
		SettingMapLayer->update();
		OtherPlayerStatusLayer->update();
		//������Ʈ�� ������ ��� �޾ƿͼ� ���������Ƿ� flag�� ������� false�� �����
		CGameManager::GetInstance()->SetUpdateFlag(false);
	}
}