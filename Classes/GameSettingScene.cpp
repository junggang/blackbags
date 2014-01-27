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
	//dt는 이전 update 이후 지난 시간

	if (CGameManager::GetInstance()->IsUpdated() )
	{
		//여기에 각 레이어들을 업데이트하는 코드를 넣음
		//각 레이어별로 업데이트 함수 만들어야 함
		SettingCharacterLayer->update(dt);
		SettingMapLayer->update();
		OtherPlayerStatusLayer->update();
		//업데이트된 내용을 모두 받아와서 갱신했으므로 flag는 원래대로 false로 만든다
		CGameManager::GetInstance()->SetUpdateFlag(false);
	}
}