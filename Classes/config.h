#pragma once
#include "ccTypes.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    typedef unsigned long DWORD;
#endif

/*	게임 화면 기본 크기입니다 */
const int WINDOW_WIDTH = 2048;
const int WINDOW_HEIGHT = 1536;


/*	최대 플레이 가능 인원입니다 */
const int MAX_PLAYER_NUM= 4;

/* 캐릭터 수 입니다 */
const int CHARACTER_NUM = 4;

/*	게임 맵 오브젝트들의 기본 크기입니다 */
const float DEFAULT_TILE_WIDTH = 240.0f;
const float DEFAULT_TILE_HEIGHT = 160.0f;

const float DEFAULT_CHARACTER_MARGIN_H = 100.0f;
const float DEFAULT_CHARACTER_MARGIN_V = 100.0f;

/*	게임 맵 크기입니다 */
const int MAX_MAP_WIDTH = 23;
const int MAX_MAP_HEIGHT = 23;

/*	지도 초기화 할 때 맵 탐사하는 배열 길이 (함수 구조 변경 후 삭제 예정) */
const int CHECKLIST_LENGTH = 100;

/*	터치 인식 범위 */
const float TOUCH_AREA = 20.0f;

/*	결과 화면 오브젝트들의 기본 크기입니다 */
const int	SC_RT_SCORE_TILE = 2;
const int	SC_RT_SCORE_GOLD = 5;
const int	SC_RT_SCORE_TRASH = -10;

/* 캐릭터 색상입니다 */
#define _COLOR_CHARACTER_1_  26,196,98,255
#define _COLOR_CHARACTER_2_  28,171,203,255
#define _COLOR_CHARACTER_3_  206, 62,5,255
#define _COLOR_CHARACTER_4_  241,196,15,255


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
	SC_NETWORK_SETTING,
};

enum NetworkPhase
{
	NP_NOTHING,
	NP_PLAYER_NUMBER_SETTING,
	NP_WAITING_CHANNEL_ID,
	NP_GAME_SETTING
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
	MS_5X5,
	MS_8X8
};

struct MapSize //맵 크기값을 위한 구조체입니다
{
	int m_Width;
	int m_Height;
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
	GD_MAP = 11,
	GD_TURN_START_TIME = 12,
	GD_WAITING_READY = 13
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
	GDP_PLAYER_IDX = 10,
	GDP_UPDATE_FLAG = 11
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


/*
	***********
	image files
	***********
*/


/*	shared images */
const std::string BackgroundImage = "shared_background.png";

/*	loading scene */

/*	main scene */

/*	gameSetting scene */

/* play scene	*/
const std::string lineImageFileList[5] =
{
	"image/playscene_line_unconnected_v.png",
	"image/playscene_line_unconnected.png",
	"image/playscene_line_connected_v.png",
	"image/playscene_line_connected.png",
	"image/playscene_line_recent.png"
};

const std::string TileImageFileList[5] =
	{
		"image/playscene_land_occupied.png",
		"image/playscene_land_occupied.png",
		"image/playscene_land_occupied.png",
		"image/playscene_land_occupied.png",
		"image/playscene_land_unoccupied.png"
	};

const std::string LandImageFileList[4] =
{
	"image/plascene_land_character01.png",
	"image/plascene_land_character02.png",
	"image/plascene_land_character03.png",
	"image/plascene_land_character04.png",
};

const std::string ItemImageFileList[3] =
{
	"image/playscene_item_cake.png",
	"image/playscene_item_trash.png",
	"image/playscene_item_gift01.png"
};

const std::string ResultCharacterWinImage[4] =
{
	"image/RESULT_PLAYER1_win.png",
	"image/RESULT_PLAYER2_win.png",
	"image/RESULT_PLAYER3_win.png",
	"image/RESULT_PLAYER4_win.png",
};

const std::string ResultCharacterLoseImage[4] =
{
	"image/RESULT_PLAYER1_lose.png",
	"image/RESULT_PLAYER2_lose.png",
	"image/RESULT_PLAYER3_lose.png",
	"image/RESULT_PLAYER4_lose.png",
};

/* intro scene */
#define INTRO_BACKGROUND_COLOR  241,196,14,255
#define INTRO_LOGO_POS 412,665
const std::string INTRO_LOGO = "image/loading_logo.png";

/* main scene */
const std::string MAIN_TITLE = "image/main_title.png";
#define MAIN_TITLE_POS 419,926
#define MAIN_MENU1_POS 116,115
#define MAIN_MENU2_POS 785,129
#define MAIN_MENU3_POS 1382,146
const std::string MAIN_MENU1_IMG = "image/main_menu01_img.png";
const std::string MAIN_MENU2_IMG = "image/main_menu02_img.png";
const std::string MAIN_MENU3_IMG = "image/main_menu03_img.png";
#define MAIN_MENU1_IMG_POS 200,168
#define MAIN_MENU2_IMG_POS 856,194
#define MAIN_MENU3_IMG_POS 1394,244
const std::string MAIN_MENU_TITLE = "image/main_menu_title.png";
#define MAIN_MENU_TITLE_POS 140,712




/*	result scene */
const std::string ResultTitle = "result_title.png";

/*	setting scene */

/* playscene */
const std::string PLAYSCENE_TIMER_BG = "image/playscene_timer_background.png";
const std::string PLAYSCENE_TIMER_BAR = "image/playscene_timer_bar.png";
const std::string PLAYSCENE_TIMER_MONSTER = "image/playscene_timer_monster.png";
#define PLAYSCENE_TIMER_POS 728,1322
#define PLAYSCENE_TIMER_MONSTER_POS 900,1380

const std::string PLAYSCENE_BOARD = "image/playscene_board.png";

const std::string PLAYSCENE_LAND_01 = "image/playscene_land_character01.png";
const std::string PLAYSCENE_LAND_02 = "image/playscene_land_character02.png";
const std::string PLAYSCENE_LAND_03 = "image/playscene_land_character03.png";
const std::string PLAYSCENE_LAND_04 = "image/playscene_land_character04.png";

const std::string PLAYSCENE_EFFECT_GOOD = "image/playscene_character_effect01.png";
const std::string PLAYSCENE_EFFECT_GREAT = "image/playscene_character_effect02.png";
const std::string PLAYSCENE_EFFECT_BAD = "image/playscene_character_effect03.png";

const std::string PLAYSCENE_DOT = "image/playscene_dot.png";

const std::string PLAYSCENE_LAND_UNOCCUPIED = "image/playscene_land_unoccupied.png";
const std::string PLAYSCENE_LAND_OCCUPIED = "image/playscene_land_occupied.png";

/* shared images */
const std::string SHARED_BACKGROUND = "image/shared_background.png";
const std::string SHARED_PLAYERUI_GREY = "image/shared_playerui_background_unselected.png";
const std::string SHARED_PLAYERUI_BLUE = "image/shared_playerui_background_selected.png";

const std::string PlayerUiCharacterUpper[5] =
{
	"image/shared_player_character01_01.png",
	"image/shared_player_character02_01.png",
	"image/shared_player_character03_01.png",
	"image/shared_player_character04_01.png",
	"image/shared_player_empty_01.png"
};

const std::string PlayerUiCharacterBelow[5] =
{
	"image/shared_player_character01_02.png",
	"image/shared_player_character02_02.png",
	"image/shared_player_character03_02.png",
	"image/shared_player_character04_02.png",
	"image/shared_player_empty_02.png"
};

const std::string SHARED_BTN_HOME = "image/shared_icon_home.png";
const std::string SHARED_BTN_BACK = "image/shared_backButton.png";
const std::string SHARED_BTN_NEXT = "image/shared_nextButton.png";
const std::string SHARED_BTN_OK = "image/shared_okButton.png";
#define SHARED_BTN_HOME_POS 940,51
#define SHARED_BTN_BACK_POS 90,94
#define SHARED_BTN_NEXT_POS 1403,94
#define SHARED_BTN_OK_POS 1403,94

const std::string SHARED_POPUP_BG = "image/shared_popup_background.png";
const std::string SHARED_POPUP_TITLE = "image/shared_popup_paused.png";
const std::string SHARED_POPUP_RESUME = "image/shared_popup_resume.png";
const std::string SHARED_POPUP_HELP = "image/shared_popup_help.png";
const std::string SHARED_POPUP_SETTING = "image/shared_popup_setting.png";
const std::string SHARED_POPUP_QUIT = "image/shared_popup_quit.png";
#define SHARED_POPUP_BG_POS 197,223
#define SHARED_POPUP_TITLE_POS 907
#define SHARED_POPUP_MENU_MARGIN 130
#define SHARED_POPUP_BOTTOM_MARGIN 310

const std::string SHARED_MENU1_UNSELECTED = "image/shared_menu01_unselected.png";
const std::string SHARED_MENU2_UNSELECTED = "image/shared_menu02_unselected.png";
const std::string SHARED_MENU3_UNSELECTED = "image/shared_menu03_unselected.png";

const std::string SHARED_MENU1_SELECTED = "image/shared_menu01_selected.png";
const std::string SHARED_MENU2_SELECTED = "image/shared_menu02_selected.png";
const std::string SHARED_MENU3_SELECTED = "image/shared_menu03_selected.png";
