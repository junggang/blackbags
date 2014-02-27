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

bool CAudioManager::init()
{
	for (int i = 0; i < MAX_BGM_LIST; ++i)
	{
		switch (i)
		{
		case BGM_MAIN:
			break;
		case BGM_PLAY:
			break;
		case BGM_SETTING:
			// 조심해!! 테스트 코드야!
			m_BGMList[i] = "Sound/simpleMusic.mp3";
			break;
		default:
			break;
		}
	}

	for (int j = 0; j < MAX_SE_LIST; ++j)
	{
		switch (j)
		{
		case SE_BUTTON_CLICK:
			// 조심해!! 테스트 코드야!
			m_BGMList[j] = "Sound/PLAYER_3_good.mp3";
			break;
		default:
			break;
		}
	}

	return true;
}

void CAudioManager::SetBGMVolume( float BGMVolume )
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(BGMVolume);
}

void CAudioManager::SetSEVolume( float SEVolume )
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(SEVolume);
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
	m_CurrentMusic = m_BGMList[BGMNumber];
}

void CAudioManager::StopBGM()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
}

void CAudioManager::ChangeSE( SEList SENumber )
{
	m_CurrentSE = m_BGMList[SENumber];
}

void CAudioManager::PlaySE()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(m_CurrentSE.c_str());
}

void CAudioManager::StopAllSE()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
}
