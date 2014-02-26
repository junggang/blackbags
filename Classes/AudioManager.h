#pragma once
#include "cocos2d.h"
#include "config.h"
#include "SimpleAudioEngine.h"

enum MusicList
{
	BGM_MAIN = 0,
	BGM_SETTING,
	BGM_PLAY,
	MAX_BGM_LIST
};

class CAudioManager
{
public:
	CAudioManager(void);
	~CAudioManager(void);

	static CAudioManager*	GetInstance();
	static void				ReleaseInstance();
	
	bool init();

	void ChangeMusic( MusicList BGMNumber );
	void PlayBGM();
	void SetBGMVolume(float BGMVolume);
	void SetSEVolume(float SEVolume);

private:
	static CAudioManager* m_pInstance;

	std::string m_CurrentMusic;
	std::string BGMList[MAX_BGM_LIST];
};

