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

enum SEList
{
	SE_BUTTON_CLICK = 0,
	MAX_SE_LIST
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
	void ChangeSE( SEList SENumber );
	void PlayBGM();
	void StopBGM();

	void PlaySE();
	void StopAllSE();

	void SetBGMVolume(float BGMVolume);
	void SetSEVolume(float SEVolume);

private:
	static CAudioManager* m_pInstance;

	std::string m_CurrentMusic;
	std::string m_BGMList[MAX_BGM_LIST];

	std::string m_CurrentSE;
	std::string m_SEList[MAX_SE_LIST];
};

