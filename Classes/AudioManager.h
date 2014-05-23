#pragma once
#include "cocos2d.h"
#include "config.h"
#include "SimpleAudioEngine.h"

enum MusicList
{
	BGM_MAIN = 0,
	BGM_RESULT,
	BGM_PLAY,
	MAX_BGM_LIST
};

enum SEList
{
	SE_BUTTON_CLICK = 0,
    SE_LINE_DRAW_FAIL,
	MAX_SE_LIST
};

enum SEDrawLineList
{
    SE_DRAW_LINE_1 = 0,
    SE_DRAW_LINE_2,
    SE_DRAW_LINE_3,
    SE_DRAW_LINE_4,
    SE_DRAW_LINE_5,
    MAX_SE_DRAW_LINE_LIST
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
    void ChangeSE( SEDrawLineList SENumber );
	void PlayBGM();
	void StopBGM();

	void PlaySE();
    void PlayLineDrawRandomSE();
	void StopAllSE();

	void SetBGMVolume(float BGMVolume);
	void SetSEVolume(float SEVolume);
    float GetBGMVolume();
    float GetSEVolume();

private:
	static CAudioManager* m_pInstance;

	std::string m_CurrentMusic;
	std::string m_BGMList[MAX_BGM_LIST];

	std::string m_CurrentSE;
	std::string m_SEList[MAX_SE_LIST];
    std::string m_SEDrawLineList[MAX_SE_DRAW_LINE_LIST];
};

