#pragma once
#include "ccTypes.h"
typedef unsigned long DWORD;

/*	게임 화면 기본 크기입니다 */
const int WINDOW_WIDTH = 1250;
const int WINDOW_HEIGHT = 700;


/*	최대 플레이 가능 인원입니다 */
const int MAX_PLAYER_NUM= 4;

/* 캐릭터 수 입니다 */
const int CHARACTER_NUM = 4;


/*	메인 메뉴 오브젝트들의 기본 크기입니다 */
const float SC_M_DEFAULT_MENU_BUTTON_WIDTH = 225.0f;
const float SC_M_DEFAULT_MENU_BUTTON_HEIGHT = 60.0f;
const float SC_M_DEFAULT_TITLE_WIDTH = 500.0F;
const float SC_M_DEFAULT_TITLE_HEIGHT = 220.0F;
const float SC_M_DEFAULT_TITLE_MARGIN = 20.0F;
const float SC_M_DEFAULT_MENU_MARGIN = 40.0F;

/*	네트워크 이름 입력 메뉴 오브젝트들의 기본 크기입니다	*/
const float SC_NS_DEFAULT_TITLE_POSITION_H = 470.0f;
const float SC_NS_DEFAULT_TITLE_POSITION_V = 150.0f;
const float SC_NS_DEFAULT_TITLE_WIDTH = 470.0f;
const float SC_NS_DEFAULT_TITLE_HEIGHT = 60.0f;

const float SC_NS_DEFAULT_BUTTON_POSITION_H = 470.0f;
const float SC_NS_DEFAULT_BUTTON_POSITION_V = 150.0f;
const float SC_NS_DEFAULT_BUTTON_WIDTH = 240.0f;
const float SC_NS_DEFAULT_BUTTON_HEIGHT = 80.0f;

const float SC_NS_DEFAULT_TEXT_SIZE = 25.0f;
const float SC_NS_DEFAULT_TEXT_WIDTH = 200.0f;
const float SC_NS_DEFAULT_TEXT_HEIGHT = 200.0f;

const int SC_NS_TEXT_INPUT_LIMIT = 32;

/*	세팅 메뉴 오브젝트들의 기본 크기입니다	*/
const float SC_S_DEFAULT_PLAYER_BUTTON_WIDTH = 290.0f;
const float SC_S_DEFAULT_PLAYER_BUTTON_HEIGHT = 40.0f;

const float SC_S_DEFAULT_PLAYER_TEXT_MARGIN = 35.0F;
const float SC_S_DEFAULT_PLAYER_TEXT_SIZE = 15.0F;

const float SC_S_DEFAULT_MAP_BUTTON_WIDTH = 110.0f;
const float SC_S_DEFAULT_MAP_BUTTON_HEIGHT = 65.0f;

const float SC_S_DEFAULT_MAP_TEXT_MARGIN = 15.0F;
const float SC_S_DEFAULT_MAP_TEXT_SIZE = 20.0F;

const float SC_S_DEFAULT_NEXT_BUTTON_WIDTH = 240.0f;
const float SC_S_DEFAULT_NEXT_BUTTON_HEIGHT = 80.0f;

const float SC_S_DEFAULT_NEXT_TEXT_MARGIN = 15.0f;
const float SC_S_DEFAULT_NEXT_TEXT_SIZE = 15.0f;

const float SC_S_DEFAULT_SUBTITLE_LAYER_WIDTH = 300.0f;
const float SC_S_DEFAULT_SUBTITLE_LAYER_HEIGHT = 40.f;

const float SC_S_DEFAULT_SUBTITLE_TEXT_SIZE = 40.0f;
const float SC_S_DEFAULT_SUBTITLE_TEXT_MARGIN = 15.0f;

const float SC_S_DEFAULT_MAINTITLE_LAYER_WIDTH = 470.0f;
const float SC_S_DEFAULT_MAINTITLE_LAYER_HEIGHT = 60.f;

const float SC_S_DEFAULT_MAINTITLE_TEXT_SIZE = 60.0f;
const float SC_S_DEFAULT_MAINTITLE_TEXT_MARGIN = 20.0f;

const float SC_S_DEFAULT_CHECKICON_WIDTH = 160.0f;
const float SC_S_DEFAULT_CHECKICON_HEIGHT = 65.0f;

/*	settingScene 초상화 크기	*/
const float SC_S_DEFAULT_PORTRAIT_WIDTH = 190.f;
const float SC_S_DEFAULT_PORTRAIT_HEIGHT = 230.f;

/*	판정을 위해서 얘네들의 y 포지션을 받아둡니다 */
const int	SC_S_DEFAULT_PLAYER_BUTTON_Y_POSITION_SCALE = 5;
const int   SC_S_DEFAULT_NEXT_BUTTON_Y_POSITION_SCALE = 9;
const int   SC_S_DEFAULT_MAP_BUTTON_Y_POSITION_SCALE = 8;

/*	어떤 플레이어가 선택되었는지 알기 위한 MASK 값들	*/
const int	MASK_PLAYER_1 = 1;
const int	MASK_PLAYER_2 = 2;
const int	MASK_PLAYER_3 = 4;
const int	MASK_PLAYER_4 = 8;

/*	게임 맵 오브젝트들의 기본 크기입니다 */
const float DEFAULT_TILE_WIDTH = 120.0f;
const float DEFAULT_TILE_HEIGHT = 80.0f;
const float DEFAULT_LINE_WEIGHT = 10.0f;
const float DEFAULT_DOT_RADIUS = 6.0f;
const float DEFAULT_ITEM_SIZE = 60.0f;

const float DEFAULT_CHARACTER_WIDTH = 190.0f;
const float DEFAULT_CHARACTER_HEIGHT = 230.0f;
const float DEFAULT_CHARACTER_MARGIN_H = 100.0f;
const float DEFAULT_CHARACTER_MARGIN_V = 100.0f;
const float DEFAULT_CHARACTER_NAME_TEXT_SIZE = 30.0f;
const float DEFAULT_CHARACTER_NAME_MARGIN_H = 10.0f;
const float DEFAULT_CHARACTER_NAME_MARGIN_V = 8.0f;

const float SC_P_TIMER_POSITION_HEIGHT = 5.0f;
const float SC_P_TIMER_HEIGHT = 12.0f;

const DWORD TIME_LIMIT = 20 * 1000;

const float SC_P_CLICK_BUFFER = 7.0f;

const DWORD SC_P_LINE_ANIMATION_TIME = 500;
const DWORD SC_P_TILE_ANIMATION_TIME = 500;

/*	게임 맵 크기입니다 */
const int MAX_MAP_WIDTH = 23;
const int MAX_MAP_HEIGHT = 23;

/* 게임 맵 오브젝트의 종류 입니다 */
const int MO_TYPE_NUMBER = 6;

/*	지도 초기화 할 때 맵 탐사하는 배열 길이 (함수 구조 변경 후 삭제 예정) */
const int CHECKLIST_LENGTH = 100;

/*	터치 인식 범위 */
const float TOUCH_AREA = 20.0f;

/*	결과 화면 오브젝트들의 기본 크기입니다 */
const float SC_RT_HORIZONTAL_MARGIN = 70.0f;
const float SC_RT_VERTICAL_MARGIN = 50.0f;
const float SC_RT_VOID_SPACE = 40.0f;

const float SC_RT_TITLE_WIDTH = 180.0f;
const float SC_RT_TITLE_HEIGHT = 70.0f;

const float SC_RT_PLAYER_POSITION_H = 120.0f;
const float SC_RT_PLAYER_POSITION_MARGIN = 15.0f;

const float SC_RT_PLAYER_FACE_HEIGHT = 100.0f;
const float SC_RT_PLAYER_FACE_WIDTH= 100.0f;

const float SC_RT_PLAYER_NAME_TEXT_SIZE = 30.0f;
const float SC_RT_PLAYER_NAME_TEXT_WIDTH = 270.0f;

const float SC_RT_PLAYER_SCORE_TEXT_SIZE = 40.0f;
const float SC_RT_PLAYER_SCORE_WIDTH = 270.0f;

const float SC_RT_PLAYER_ITEM_POSITION = 70.0f;
const float SC_RT_PLAYER_ITEM_HEIGHT = 100.0f;
const float SC_RT_PLAYER_ITEM_WIDTH = 100.0f;
const float SC_RT_PLAYER_ITEM_MARGIN = 10.0f;

const float SC_RT_MULTIPLY_HEIGHT = 100.0f;
const float SC_RT_MULTIPLY_WIDTH = 37.0f;

const float SC_RT_CROWN_POSITION = 30.0f;
const float SC_RT_CROWN_WIDTH = 100.0f;
const float SC_RT_CROWN_HEIGHT = 60.0f;

const float SC_RT_PLAYER_ITEM_COUNT_POSITION = 48.0f;
const float SC_RT_PLAYER_ITEM_COUNT_SIZE = 50.0f;
const float SC_RT_PLAYER_ITEM_COUNT_WIDTH = 70.0f;

const float SC_RT_FINISH_POSITION_H = 1000.0f;
const float SC_RT_FINISH_POSITION_V = 595.0f;
const float SC_RT_FINISH_WIDTH = 180.0f;
const float SC_RT_FINISH_HEIGHT = 70.0f;

const int	SC_RT_SCORE_TILE = 2;
const int	SC_RT_SCORE_GOLD = 5;
const int	SC_RT_SCORE_TRASH = -10;

#define _COLOR_RESULT_TEXT_ 99.0f/255, 99.0f/255, 99.0f/255
//#define _COLOR_RESULT_SCORE_TEXT_ 28.0f/255,171.0f/255,204.0f/255
#define _COLOR_RESULT_SCORE_TEXT_ 230.0f/255,126.0f/255,34.0f/255

/*	크레딧 신에서 불러올 동영상들입니다	*/
#define _CREDIT_MOVIE "Resource/Video/credit.avi"
#define _OPENING_MOVIE "Resource/Video/opening.avi"

/*	BMG list	*/
#define _BGM_MAIN "Resource/Sound/Nujabes/MAIN.mp3"
#define _BGM_SETTING "Resource/Sound/Nujabes/SETTING.mp3"
#define _BGM_PLAY "Resource/Sound/Nujabes/PLAY.mp3"
#define _BGM_RESULT "Resource/Sound/Nujabes/RESULT.mp3"

/*	sound effect */
#define _SE_DRAW_LINE "Resource/Sound/temp/line2.wav" //line2
#define _SE_SELECT "Resource/Sound/button_pop.mp3"
#define _SE_LAUGH "Resource/Sound/SE_laugh.mp3"
#define _SE_FILL_TILE "Resource/Sound/temp/slide.wav"
#define _SE_PLAYER1 "Resource/Sound/PLAYER_1_good.mp3"
#define _SE_PLAYER2 "Resource/Sound/PLAYER_2_good.mp3"
#define _SE_PLAYER3 "Resource/Sound/PLAYER_3_good.mp3"
#define _SE_PLAYER4 "Resource/Sound/PLAYER_4_good.mp3"


/*	폰트들입니다	*/
#define _DEBUG_FONT L"Consolas"
#define _MENU_FONT L"Segoe UI"
#define _UI_FONT L"Comic Sans MS"

/*	플레이어 색상입니다	*/
#define _COLOR_PLAYER_1_ 26.0f/255, 196.0f/255, 98.0f/255, 0.75f
#define _COLOR_PLAYER_2_ 28.0f/255, 171.0f/255, 203.0f/255, 0.75f
#define _COLOR_PLAYER_3_ 206.0f/255, 62.0f/255, 5.0f/255, 0.6f
#define _COLOR_PLAYER_4_ 241.0f/255, 196.0f/255, 15.0f/255, 0.75f

/* 캐릭터 색상입니다 */
#define _COLOR_CHARACTER_1_  26,196,98,255
#define  _COLOR_CHARACTER_2_  28,171,203,255
#define  _COLOR_CHARACTER_3_  206, 62,5,255
#define  _COLOR_CHARACTER_4_  241,196,15,255


/*	enum 타입들입니다. */
enum SceneName	//Scene 이름들
{
	SC_OPENING,
	SC_MAIN,
	SC_SETTING,
	SC_PLAY,
	SC_RESULT,
	SC_CREDIT,
	SC_NOSCENE,
	SC_EXIT,
	SC_NETWORK_NAMESETTING,
	SC_NETWORK_SETTING,
	SC_NETWORK_PLAY,
	SC_NETWORK_RESULT
};

enum NetworkPhase
{
	NP_NOTHING,
	NP_PLAYER_NUMBER_SETTING,
	NP_WAITING_CHANNEL_ID,
	NP_GAME_SETTING
};

enum SOUND_BGMList
{
	BGM_MAIN,
	BGM_SETTING,
	BGM_PLAY,
	BGM_RESULT
};

enum MO_TYPE	//게임 맵 기본 자료형
{
	MO_SENTINEL,
	MO_DOT = 10,
	MO_LINE_UNCONNECTED = 20,
	MO_LINE_CONNECTED,
	MO_LINE_HIDDEN,
	MO_TILE = 30,
};

enum MO_OWNER	//게임 맵 각 타일 소유주
{
	MO_NOBODY = -1,
	MO_PLAYER1,
	MO_PLAYER2,
	MO_PLAYER3,
	MO_PLAYER4
};

enum MO_ITEM	//타일에 지정된 아이템
{
	ITEM_NOTHING = -1,
	ITEM_GOLD,
	ITEM_TRASH
};

enum Direction	//게임 맵 탐색 시 활용되는 방향
{
	DI_UP,
	DI_RIGHT,
	DI_DOWN,
	DI_LEFT
};

enum MapSelect
{
	MS_NOT_SELECTED,
	MS_6X5,
	MS_8X7
};

struct MapSize //맵 크기값을 위한 구조체입니다
{
	int m_Width;
	int m_Height;
};

enum PlayerType
{
	PT_PLAYER,
	PT_AI
};

struct Coordinate
{
	int m_PosX;
	int m_PosY;
};

/*	network data */
enum GameDataIndex
{
	GD_CURRENT_SCENE = 0,
	GD_CHANNEL_ID = 1,
	GD_MAP_ID = 2,
	GD_CURRENT_TURN_IDX = 3,
	GD_TURN_LIST = 4,
	GD_TURN_START_FLAG = 5,
	GD_RECENTLY_CONNECTED_LINE = 6,
	GD_VOID_TILE_COUNT = 7,
	GD_PLAYER_NUMBER = 8,
	GD_PLAYER_LIST = 9,
	GD_MAP_SIZE = 10,
	GD_MAP = 11
};

enum GameDataPlayerData
{
	GDP_NAME = 0,
	GDP_MASTER_FLAG = 1,
	GDP_CONNECTED_FLAG = 2,
	GDP_READY = 3,
	GDP_CHARACTER_ID = 4,
	GDP_TURN = 5,
	GDP_TILE_COUNT = 6,
	GDP_GOLD_COUNT = 7,
	GDP_TRASH_COUNT = 8,
	GDP_SCORE = 9,
	GDP_PLAYER_IDX = 10
};

enum MapDataIndex
{
	GDM_TYPE = 0,
	GDM_OWNER = 1,
	GDM_ITEM = 2,
	GDM_CHECKED_FLAG = 3,
	GDM_ANIMATION_TURN = 4,
	GDM_DIRECTION = 5
};

/*	게임 맵의 타일 좌표를 표현하기 위한 구조체 */
struct IndexedPosition
{
	IndexedPosition() : m_PosI(0), m_PosJ(0) {}

	IndexedPosition(const IndexedPosition& inputIndexedPosition)
	{
		m_PosI = inputIndexedPosition.m_PosI;
		m_PosJ = inputIndexedPosition.m_PosJ;
	}

	/*	복사 대입 연산자 오버라이딩
		queue같은 곳에 push해도 복사를 잘 해줍니당 */
	IndexedPosition& operator=(const IndexedPosition& inputIndexedPosition) 
	{
		m_PosI = inputIndexedPosition.m_PosI;
		m_PosJ = inputIndexedPosition.m_PosJ;
		return *this ;
	}

	IndexedPosition(int PosI, int PosJ)
	{
		m_PosI = PosI;
		m_PosJ = PosJ;
	}

	int m_PosI;
	int m_PosJ;
};

struct MapObject
{
	MapObject () :
		m_Type(MO_SENTINEL),
		m_Owner(MO_NOBODY),
		m_Item(ITEM_NOTHING),
		m_Flag(false),
		m_AnimationFlag(false),
		m_StartTime(0),
		m_AnimationTurn(0),
		m_Direction(DI_UP)
		{}

	MO_TYPE		m_Type;
	MO_OWNER	m_Owner;
	MO_ITEM		m_Item;
	
	bool m_Flag;
	bool m_MouseOverFlag;	

	bool		m_AnimationFlag;
	DWORD		m_StartTime;
	int			m_AnimationTurn;
	Direction	m_Direction;
};

const std::string lineImageFileList[4] =
{
	"image/linev0.png",
	"image/line0.png",
	"image/line_connectedv_4.png",
	"image/line_connected4.png",
};

const std::string TileImageFileList[5] =
	{
		"image/tile_occupied.png",
		"image/tile_occupied.png",
		"image/tile_occupied.png",
		"image/tile_occupied.png",
		"image/tile_void.png"
	};

const std::string ItemImageFileList[2] =
{
	"image/PLAY_gold.png",
	"image/PLAY_trash.png"
};