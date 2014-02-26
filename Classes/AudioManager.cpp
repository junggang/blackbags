#include "AudioManager.h"

CAudioManager* CAudioManager::m_pInstance = nullptr;

CAudioManager::CAudioManager(void)
{
	init();
}

CAudioManager::~CAudioManager(void)
{
}

CAudioManager* CAudioManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CAudioManager();
	}

	return m_pInstance;
}

void CAudioManager::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CAudioManager::PlayBGM()
{
	if ( !m_CurrentMusic.empty() )
	{
		CCLOG( "%s", m_CurrentMusic.c_str() );
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
			m_CurrentMusic.c_str(), true);
	}
}

void CAudioManager::ChangeMusic( MusicList BGMNumber )
{
	CCLOG( "%s", BGMList[BGMNumber].c_str() );
	m_CurrentMusic = BGMList[BGMNumber];
}

bool CAudioManager::init()
{
	for (int i = 0; i < MAX_BGM_LIST; ++i)
	{
		switch (i)
		{
		case BGM_MAIN:
			// 조심해!! 테스트 코드야!
			BGMList[i] = "Sound/simpleMusic.mp3";
			break;
		case BGM_PLAY:
			break;
		case BGM_SETTING:
			break;
		default:
			break;
		}
	}

	return true;
}
