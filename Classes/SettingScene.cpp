#include "SettingScene.h"
#include "BackgroundLayer.h"
#include "GameManager.h"
#include "AudioManager.h"

USING_NS_CC;

bool CSettingScene::init(void)
{
	//////////////////////////////
    // 1. super init first
	if ( !CCScene::init() )
    {
        return false;
    }

	/////////////////////////////
    // 2. add layers
	CCLayer* BackgroundLayer = CBackgroundLayer::create();

	this->addChild(BackgroundLayer, 0);

	m_SettingMenuLayer = CSettingMenuLayer::create();

	this->addChild(m_SettingMenuLayer, 1);

	/////////////////////////////
	// 3. active schedule
	this->scheduleUpdate();

	/////////////////////////////
	// 4. play music
	CAudioManager::GetInstance()->ChangeMusic(BGM_MAIN);
	CAudioManager::GetInstance()->PlayBGM();

	return true;
}

void CSettingScene::update( float dt )
{
	if ( !CGameManager::GetInstance()->IsUpdated() )
	{
		return;
	}

	m_SettingMenuLayer->update(dt);
}
