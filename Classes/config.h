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
const float DEFAULT_TILE_DIAGONAL = 144.0f;

const float DEFAULT_CHARACTER_MARGIN_H = 100.0f;
const float DEFAULT_CHARACTER_MARGIN_V = 100.0f;

/*	게임 맵 크기입니다 */
const int MAX_MAP_WIDTH = 23;
const int MAX_MAP_HEIGHT = 23;

/*	지도 초기화 할 때 맵 탐사하는 배열 길이 (함수 구조 변경 후 삭제 예정) */
const int CHECKLIST_LENGTH = 100;

/*	터치 인식 범위 */
const float TOUCH_AREA = 60.0f;

/*	결과 화면 오브젝트들의 기본 크기입니다 */
// gold and trash add 2 (because if has tile)
const int	SC_RT_SCORE_TILE = 2;
const int	SC_RT_SCORE_GOLD = 7;
const int	SC_RT_SCORE_TRASH = -8;

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

enum LoginPhase
{
	LP_WAITING,
    LP_FAIL,
    LP_OK
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

enum MO_ITEM	//Item
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
	MS_6X6,
	MS_7X7
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
    
    bool operator==(const IndexedPosition& rhs)
    {
        if ( m_PosI == rhs.m_PosI && m_PosJ == rhs.m_PosJ )
            return true;
        
        return false;
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


/*	credit scene */
#define CREDIT_TITLE_IMAGE "image/credit_title.png"
#define CREDIT_TITLE_POSITION 842,1317

#define CREDIT_MEMBER_IMAGE "image/credit_members.png"
#define CREDIT_MEMBER_POSITION 96,200

#define CREDIT_BACK_BUTTON_POSITION 90,94

/* contact scene */
const std::string CONTACT_TITLE="image/contact_title.png";
#define CONTACT_TITLE_POS 812,1317
const std::string CONTACT_MAIL = "image/contact_mail.png";


// waiting gamechannel
#define WAITING_CHANNEL_MONSTER_IMAGE "image/searching_monster.png"
#define WAITING_CHANNEL_MONSTER_POSITION 875,601

const std::string WAITING_CHANNEL_TEXT_IMAGE="image/searching_text.png";
const std::string WAITING_CHANNEL_TEXT_IMAGE_PLIST="image/searching_text.plist";
#define WAITING_CHANNEL_TEXT_POSITION 1051,511

const std::string WAITING_CHANNEL_MAGNIFIER_IMAGE ="image/searching_eye_ani.png";
const std::string WAITING_CHANNEL_MAGNIFIER_IMAGE_PLIST ="image/searching_eye_ani.plist";
#define WAITING_CHANNEL_MAGNIFIER_POSITION 500,500

#define WAITING_CHANNEL_BACK_BUTTON_POSITION 90,94

const std::string WAITING_ONLINE_IMAGE = "image/searching_online.png";

/* play scene	*/
const std::string lineImageFileList[5] =
{
	"image/playscene_line_unconnected_v.png",
	"image/playscene_line_unconnected.png",
	"image/playscene_line_connected_v.png",
	"image/playscene_line_connected.png",
	"image/playscene_line_recent.png"
};

const std::string LineAnimationFileList[2] =
{
    "image/ani_playscene_line_recent_v.png",
    "image/ani_playscene_line_recent.png"
};

const std::string LineAnimationFileListPlist[2] =
{
    "image/ani_playscene_line_recent_v.plist",
    "image/ani_playscene_line_recent.plist"
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
const std::string MAIN_MENU1_ANI = "image/main_menu01_img_ani.png";
const std::string MAIN_MENU2_ANI = "image/main_menu02_img_ani.png";
const std::string MAIN_MENU3_ANI = "image/main_menu03_img_ani.png";
const std::string MAIN_MENU1_ANI_PLIST = "image/main_menu01_img_ani.plist";
const std::string MAIN_MENU2_ANI_PLIST = "image/main_menu02_img_ani.plist";
const std::string MAIN_MENU3_ANI_PLIST = "image/main_menu03_img_ani.plist";


/*	game setting scene	*/
const std::string PLAYER_NUMBER_TITLE = "image/gameset01_title.png";
#define PLAYER_NUMBER_TITLE_POS 1022,1390

const std::string GAMESET01_ONLINE_DES = "image/gameset01_description_eng.png";
#define GAMESET01_ONLINE_DES_POS 1231

const std::string PLAYER_NUMBER_TWO_TXT = "image/gameset01_menu01_img.png";
const std::string PLAYER_NUMBER_THREE_TXT = "image/gameset01_menu02_img.png";
const std::string PLAYER_NUMBER_FOUR_TXT = "image/gameset01_menu03_img.png";
#define PLAYER_NUMBER_TWO_IMG_POS 94,446
#define PLAYER_NUMBER_TWO_TXT_POS 167,512
#define PLAYER_NUMBER_THREE_IMG_POS 763,459
#define PLAYER_NUMBER_THREE_TXT_POS 804,524
#define PLAYER_NUMBER_FOUR_IMG_POS 1360,476
#define PLAYER_NUMBER_FOUR_TXT_POS 1407,515
#define PLAYER_NUMBER_NEXT_IMG_POS 1403,94

const std::string CHARACTER_SELECT_TITLE = "image/gameset02_title.png";
const std::string CHARACTER_SELECT_TITLE_KOR = "image/gameset02_title_korean.png";
#define GAME_SETTING_CHARACTER_SELECT_TITLE_POS 519,1025
#define GAME_SETTING_CHARACTER_SELECT_TITLE_KOR_POS 795,925
#define GAME_SETTING_PLAYER_ONE_STATUS_POS 44,20
#define GAME_SETTING_PLAYER_TWO_STATUS_POS 1337,20
#define GAME_SETTING_PLAYER_THREE_STATUS_POS 18,1091
#define GAME_SETTING_PLAYER_FOUR_STATUS_POS 1337,1091

const std::string CHARACTER_UNSELECT_01 = "image/gameset02_character01_unselected.png";
const std::string CHARACTER_SELECT_01 = "image/gameset02_character01_selected.png";
const std::string CHARACTER_UNSELECT_02 = "image/gameset02_character02_unselected.png";
const std::string CHARACTER_SELECT_02 = "image/gameset02_character02_selected.png";
const std::string CHARACTER_UNSELECT_03 = "image/gameset02_character03_unselected.png";
const std::string CHARACTER_SELECT_03 = "image/gameset02_character03_selected.png";
const std::string CHARACTER_UNSELECT_04 = "image/gameset02_character04_unselected.png";
const std::string CHARACTER_SELECT_04 = "image/gameset02_character04_selected.png";
#define GAME_SETTING_CHARACTER_POS_01 488,461
#define GAME_SETTING_CHARACTER_POS_02 811,474
#define GAME_SETTING_CHARACTER_POS_03 1053,470
#define GAME_SETTING_CHARACTER_POS_04 1393,485

const std::string GAME_SETTING_PLAYER_READY_STATE_LEFT = "image/playscene_character_ready_03.png";
const std::string GAME_SETTING_PLAYER_READY_STATE_RIGHT = "image/playscene_character_ready_04.png";

const std::string GAME_SETTING_READY_BTN_UNSELECT = "image/gameset02_readyBtn_unselected.png";
const std::string GAME_SETTING_READY_BTN_SELECT = "image/gameset02_readyBtn_selected.png";
#define GAME_SETTING_READY_BTN_POS 820,248

const std::string PLAYER_STATUS_READY_IMG = "image/playscene_character_ready.png";

/*	result scene */
const std::string RESULT_TITLE = "image/result_title.png";
#define RESULT_TITLE_POSITION 1022,1390

#define RESULT_OK_BUTTON_POSITION 1403,94

const std::string RESULT_BACKGROUND_IMAGE[MAX_PLAYER_NUM] =
{
	"image/result_bg01.png",
	"image/result_bg02.png",
	"image/result_bg03.png",
	"image/result_bg04.png",
};
#define RESULT_BACKGROUND_WIDTH 497
#define RESULT_BACKGROUND_HEIGHT 1100
#define RESULT_BACKGROUND_POSITION_Y 246

#define RESULT_PLAYER_NAME_POSITION_X 243
#define RESULT_PLAYER_NAME_POSITION_Y 950

#define RESULT_PLAYER_SCORE_POSITION_X_MARGIN 243
#define RESULT_PLAYER_SCORE_POSITION_Y_MARGIN 410

const std::string RESULT_CHARACTER_WIN_IMAGE[MAX_PLAYER_NUM] =
{
	"image/result_character01.png",
	"image/result_character02.png",
	"image/result_character03.png",
	"image/result_character04.png",
};
const std::string RESULT_CHARACTER_LOSE_IMAGE[MAX_PLAYER_NUM] =
{
	"image/result_character01.png",
	"image/result_character02.png",
	"image/result_character03.png",
	"image/result_character04.png",
};
#define RESULT_CHARACTER_IMAGE_POSITION_X_MARGIN 248
#define RESULT_CHARACTER_IMAGE_POSITION_Y_MARGIN 450

const std::string RESULT_WINNER = "image/result_winner_ani.png";
const std::string RESULT_WINNER_PLIST = "image/result_winner_ani.plist";

#define RESULT_ITEM_IMAGE_Y_MARGIN 175
const std::string RESULT_FLOWER_IMAGE[MAX_PLAYER_NUM] =
{
	"image/result_flower_01.png",
	"image/result_flower_02.png",
	"image/result_flower_03.png",
	"image/result_flower_04.png",
};
#define RESULT_FLOWER_IMAGE_X_MARGIN 100

const std::string RESULT_GOLD_IMAGE[1] =
{
	"image/result_item_cake.png",
};
#define RESULT_GOLD_IMAGE_X_MARGIN 248

const std::string ResultTrashImage[3] =
{
	"image/result_item_trash01.png",
	"image/result_item_trash02.png",
	"image/result_item_trash03.png",
};
#define RESULT_TRASH_IMAGE_X_MARGIN 414

#define RESULT_ITEM_COUNT_Y_MARGIN 105
#define RESULT_FLOWER_COUNT_X_MARGIN 100
#define RESULT_GOLD_COUNT_X_MARGIN 248
#define RESULT_TRASH_COUNT_X_MARGIN 414

/*	setting scene */
const std::string SETTING_TITLE = "image/setting_title.png";
#define SETTING_TITLE_POS 811,1277

const std::string SETTING_BG = "image/setting_menu_background.png";
#define SETTING_BG_POS 113,200

const std::string SETTING_MENU_GOOGLE = "image/setting_menu_google.png";
const std::string SETTING_MENU_SOUND = "image/setting_menu_sound.png";
const std::string SETTING_MENU_TUTORIAL = "image/setting_menu_tutorial.png";
const std::string SETTING_MENU_CONTACT= "image/setting_menu_contact.png";
const std::string SETTING_MENU_CREDIT = "image/setting_menu_credit.png";
const std::string SETTING_LOGIN= "image/setting_menu_google_login.png";

#define SETTING_MENU_GOOGLE_POS 463,1063
#define SETTING_MENU_SOUND_POS 463,902
#define SETTING_MENU_TUTORIAL_POS 1153,607
#define SETTING_MENU_CREDIT_POS 1153,487
#define SETTING_MENU_CONTACT_POS 1153,366
#define SETTING_LOGIN_POS 1153,1063
#define SETTING_NAME_POS 1153,926

const std::string SETTING_ICON_MUSIC = "image/setting_icon_music.png";
const std::string SETTING_ICON_SOUND = "image/setting_icon_sound.png";
const std::string SETTING_BAR = "image/setting_sound_bar.png";
const std::string SETTING_CONTROLLER = "image/setting_sound_controller.png";
#define SETTING_ICON_MUSIC_POS 1042,923
#define SETTING_ICON_SOUND_POS 1042,792
#define SETTING_MUSIC_BAR_POS 1153,953
#define SETTING_SOUND_BAR_POS 1153,811

/* tutorial scene */
const std::string TUTORIAL_TITLE = "image/tutorial_title.png";
#define TUTORIAL_TITLE_POS 794,1317
const std::string TUTORIAL_BOARD = "image/tutorial_board.png";
const std::string TUTORIAL_TURN = "image/tutorial_cindy.png";
const std::string TUTORIAL_TIMER = "image/tutorial_timer.png";
const std::string TUTORIAL_TEXT_DRAW0 = "image/tutorial_text_draw0.png";
const std::string TUTORIAL_TEXT_DRAW1 = "image/tutorial_text_draw1.png";
const std::string TUTORIAL_TEXT_MENU = "image/tutorial_text_menu.png";
const std::string TUTORIAL_TEXT_SCORE0 = "image/tutorial_text_score0.png";
const std::string TUTORIAL_TEXT_SCORE1 = "image/tutorial_text_score1.png";
const std::string TUTORIAL_TEXT_SCORE2 = "image/tutorial_text_score2.png";
const std::string TUTORIAL_TEXT_SCORE3 = "image/tutorial_text_score3.png";
const std::string TUTORIAL_TEXT_TIMER0 = "image/tutorial_text_timer0.png";
const std::string TUTORIAL_TEXT_TIMER1 = "image/tutorial_text_timer1.png";
#define TUTORIAL_BOARD_POS 324,276
#define TUTORIAL_TURN_POS 1402,519
#define TUTORIAL_TIMER_POS 859,1074
#define TUTORIAL_TEXT_TIMER_POS 1142,1134
#define TUTORIAL_TEXT_DRAW_POS 283,826
#define TUTORIAL_TEXT_SCORE_POS 1260,723
#define TUTORIAL_TEXT_MENU_POS 496,422
#define TUTORIAL_TURN_POS 1402,519
#define TUTORIAL_DRAW_ANIMATION_POS 856,643

const std::string TUTORIAL_ANI_TIMER = "image/tutorial_animation_timer.png";
const std::string TUTORIAL_ANI_TIMER_PLIST = "image/tutorial_animation_timer.plist";
const std::string TUTORIAL_ANI_DRAW = "image/tutorial_ani_draw.png";
const std::string TUTORIAL_ANI_DRAW_PLIST = "image/tutorial_ani_draw.plist";
const std::string TUTORIAL_ANI_LAND = "image/tutorial_animation_land.png";
const std::string TUTORIAL_ANI_LAND_PLIST = "image/tutorial_animation_land.plist";



// troubleshooting layer
#define TROUBLESHOOTING_BACKGROUND_IMAGE "image/login_troubleshooting.png"
#define TROUBLESHOOTING_BACKGROUND_POS 555,248

#define TROUBLESHOOTING_SIGNUP_IMAGE "image/login_signUp.png"
#define TROUBLESHOOTING_SIGNUP_POS 674,790

#define TROUBLESHOOTING_VISIT_IMAGE "image/login_visit.png"
#define TROUBLESHOOTING_VISIT_POS 674,549

#define TROUBLESHOOTING_CLOSE_IMAGE "image/login_exitBtn.png"
#define TROUBLESHOOTING_CLOSE_POS 1337,1221


/* playscene */
const std::string PLAYSCENE_TIMER_BG = "image/playscene_timer_background.png";
const std::string PLAYSCENE_TIMER_BAR = "image/playscene_timer_bar.png";
const std::string PLAYSCENE_TIMER_MONSTER = "image/playscene_timer_monster.png";
#define PLAYSCENE_TIMER_POS 728,1322
#define PLAYSCENE_TIMER_MONSTER_POS 900,1380

const std::string PLAYSCENE_TIMER_OUT = "image/playscene_timer_out.png";
#define PLAYSCENE_TIMER_OUT_POS 678,1236

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

const std::string PLAYSCENE_GAMEOVER = "image/playscene_gameover.png";
const std::string PLAYSCENE_GAMEOVER_TITLE = "image/playscene_gameover_text.png";

const float PLAYSCENE_ANIMATION_TIME = 0.8f;

const std::string PLAYSCENE_SCORE_LAND = "image/playscene_score_land.png";
const std::string PLAYSCENE_SCORE_CAKE = "image/playscene_score_cake.png";
const std::string PLAYSCENE_SCORE_TRASH = "image/playscene_score_trash.png";


/* shared images */
const std::string SHARED_BACKGROUND = "image/shared_background.png";
const std::string SHARED_BACKGROUND_DRAW = "image/shared_background_draw.png";
const std::string SHARED_PLAYERUI_GREY = "image/shared_playerui_background_unselected.png";
const std::string SHARED_PLAYERUI_BLUE = "image/shared_playerui_background_selected.png";

const std::string PlayerUiCharacterUpperLeft[5] =
{
	"image/shared_player_character01_01.png",
	"image/shared_player_character02_01.png",
	"image/shared_player_character03_01.png",
	"image/shared_player_character04_01.png",
	"image/shared_player_empty_01_on.png"
};

const std::string PlayerUiCharacterUpperLeftOffline[5] =
{
	"image/shared_player_character01_01_off.png",
	"image/shared_player_character02_01_off.png",
	"image/shared_player_character03_01_off.png",
	"image/shared_player_character04_01_off.png",
	"image/shared_player_empty_01.png"
};

const std::string PlayerUiNameUpperLeftOffline[4] =
{
    "image/shared_player_character01_01_name.png",
    "image/shared_player_character02_01_name.png",
    "image/shared_player_character03_01_name.png",
    "image/shared_player_character04_01_name.png",
};

const std::string PlayerUiCharacterUpperRight[5] =
{
	"image/shared_player_character01_02.png",
	"image/shared_player_character02_02.png",
	"image/shared_player_character03_02.png",
	"image/shared_player_character04_02.png",
	"image/shared_player_empty_02_on.png"
};

const std::string PlayerUiCharacterUpperRightOffline[5] =
{
	"image/shared_player_character01_02_off.png",
	"image/shared_player_character02_02_off.png",
	"image/shared_player_character03_02_off.png",
	"image/shared_player_character04_02_off.png",
	"image/shared_player_empty_02.png"
};

const std::string PlayerUiNameUpperRightOffline[4] =
{
    "image/shared_player_character01_02_name.png",
    "image/shared_player_character02_02_name.png",
    "image/shared_player_character03_02_name.png",
    "image/shared_player_character04_02_name.png",
};

const std::string PlayerUiCharacterBelowLeft[5] =
{
	"image/shared_player_character01_03.png",
	"image/shared_player_character02_03.png",
	"image/shared_player_character03_03.png",
	"image/shared_player_character04_03.png",
	"image/shared_player_empty_03.png"
};

const std::string PlayerUiCharacterBelowLeftOffline[5] =
{
	"image/shared_player_character01_03_off.png",
	"image/shared_player_character02_03_off.png",
	"image/shared_player_character03_03_off.png",
	"image/shared_player_character04_03_off.png",
	"image/shared_player_empty_03.png"
};

const std::string PlayerUiNameBelowLeftOffline[4] =
{
    "image/shared_player_character01_03_name.png",
    "image/shared_player_character02_03_name.png",
    "image/shared_player_character03_03_name.png",
    "image/shared_player_character04_03_name.png",
};

const std::string PlayerUiCharacterBelowRight[5] =
{
	"image/shared_player_character01_04.png",
	"image/shared_player_character02_04.png",
	"image/shared_player_character03_04.png",
	"image/shared_player_character04_04.png",
	"image/shared_player_empty_04.png"
};

const std::string PlayerUiCharacterBelowRightOffline[5] =
{
	"image/shared_player_character01_04_off.png",
	"image/shared_player_character02_04_off.png",
	"image/shared_player_character03_04_off.png",
	"image/shared_player_character04_04_off.png",
	"image/shared_player_empty_04.png"
};

const std::string PlayerUiNameBelowRightOffline[4] =
{
    "image/shared_player_character01_04_name.png",
    "image/shared_player_character02_04_name.png",
    "image/shared_player_character03_04_name.png",
    "image/shared_player_character04_04_name.png",
};

const std::string SHARED_PLAYERUI_CHARACTERS[16] =
{
	"image/shared_player_character01_01.png",
	"image/shared_player_character02_01.png",
	"image/shared_player_character03_01.png",
	"image/shared_player_character04_01.png",
	"image/shared_player_character01_02.png",
	"image/shared_player_character02_02.png",
	"image/shared_player_character03_02.png",
	"image/shared_player_character04_02.png",
	"image/shared_player_character01_03.png",
	"image/shared_player_character02_03.png",
	"image/shared_player_character03_03.png",
	"image/shared_player_character04_03.png",
	"image/shared_player_character01_04.png",
	"image/shared_player_character02_04.png",
	"image/shared_player_character03_04.png",
	"image/shared_player_character04_04.png",	
};

//for animation
const std::string SHARED_PLAYERUI_CHARACTERS_ANI[16] =
{
    "image/ani_player_character01_01.png",
	"image/ani_player_character02_01.png",
	"image/ani_player_character03_01.png",
	"image/ani_player_character04_01.png",
    "image/ani_player_character01_02.png",
	"image/ani_player_character02_02.png",
	"image/ani_player_character03_02.png",
	"image/ani_player_character04_02.png",
    "image/ani_player_character01_03.png",
	"image/ani_player_character02_03.png",
	"image/ani_player_character03_03.png",
	"image/ani_player_character04_03.png",
    "image/ani_player_character01_04.png",
	"image/ani_player_character02_04.png",
	"image/ani_player_character03_04.png",
	"image/ani_player_character04_04.png"
};

const std::string SHARED_PLAYERUI_CHARACTERS_ANI_PLIST[16] =
{
    "image/ani_player_character01_01.plist",
	"image/ani_player_character02_01.plist",
	"image/ani_player_character03_01.plist",
	"image/ani_player_character04_01.plist",
    "image/ani_player_character01_02.plist",
	"image/ani_player_character02_02.plist",
	"image/ani_player_character03_02.plist",
	"image/ani_player_character04_02.plist",
    "image/ani_player_character01_03.plist",
	"image/ani_player_character02_03.plist",
	"image/ani_player_character03_03.plist",
	"image/ani_player_character04_03.plist",
    "image/ani_player_character01_04.plist",
	"image/ani_player_character02_04.plist",
	"image/ani_player_character03_04.plist",
	"image/ani_player_character04_04.plist"
};

const std::string SHARED_PLAYERUI_CHARACTERS_ANI_OFF[16] =
{
    "image/ani_player_character01_01_off.png",
    "image/ani_player_character02_01_off.png",
    "image/ani_player_character03_01_off.png",
    "image/ani_player_character04_01_off.png",
    "image/ani_player_character01_02_off.png",
    "image/ani_player_character02_02_off.png",
    "image/ani_player_character03_02_off.png",
    "image/ani_player_character04_02_off.png",
    "image/ani_player_character01_03.png",
	"image/ani_player_character02_03.png",
	"image/ani_player_character03_03.png",
	"image/ani_player_character04_03.png",
    "image/ani_player_character01_04.png",
	"image/ani_player_character02_04.png",
	"image/ani_player_character03_04.png",
	"image/ani_player_character04_04.png"
    
};

const std::string SHARED_PLAYERUI_NAME_OFF[16]=
{
    "image/shared_player_character01_01_name.png",
    "image/shared_player_character02_01_name.png",
    "image/shared_player_character03_01_name.png",
    "image/shared_player_character04_01_name.png",
    "image/shared_player_character01_02_name.png",
    "image/shared_player_character02_02_name.png",
    "image/shared_player_character03_02_name.png",
    "image/shared_player_character04_02_name.png",
    "image/shared_player_character01_03_name.png",
    "image/shared_player_character02_03_name.png",
    "image/shared_player_character03_03_name.png",
    "image/shared_player_character04_03_name.png",
    "image/shared_player_character01_04_name.png",
    "image/shared_player_character02_04_name.png",
    "image/shared_player_character03_04_name.png",
    "image/shared_player_character04_04_name.png",
};
const std::string SHARED_PLAYERUI_CHARACTERS_ANI_OFF_PLIST[16] =
{
    "image/ani_player_character01_01_off.plist",
    "image/ani_player_character02_01_off.plist",
    "image/ani_player_character03_01_off.plist",
    "image/ani_player_character04_01_off.plist",
    "image/ani_player_character01_02_off.plist",
    "image/ani_player_character02_02_off.plist",
    "image/ani_player_character03_02_off.plist",
    "image/ani_player_character04_02_off.plist",
    "image/ani_player_character01_03.plist",
	"image/ani_player_character02_03.plist",
	"image/ani_player_character03_03.plist",
	"image/ani_player_character04_03.plist",
    "image/ani_player_character01_04.plist",
	"image/ani_player_character02_04.plist",
	"image/ani_player_character03_04.plist",
	"image/ani_player_character04_04.plist"
};

const int SHARED_PLAYERUI_CHARACTERS_ANI_FRAME[4] = {22,40,30,25};

const std::string SHARED_PLAYERUI_CHARACTERS_OFF_EMPTY[4] =
{
	"image/shared_player_empty_01.png",
	"image/shared_player_empty_02.png",
	"image/shared_player_empty_03.png",
	"image/shared_player_empty_04.png"
};

const std::string SHARED_PLAYERUI_CHARACTERS_OFF[16] =
{
	"image/shared_player_character01_01_off.png",
	"image/shared_player_character02_01_off.png",
	"image/shared_player_character03_01_off.png",
	"image/shared_player_character04_01_off.png",
	"image/shared_player_character01_02_off.png",
	"image/shared_player_character02_02_off.png",
	"image/shared_player_character03_02_off.png",
	"image/shared_player_character04_02_off.png",
	"image/shared_player_character01_03_off.png",
	"image/shared_player_character02_03_off.png",
	"image/shared_player_character03_03_off.png",
	"image/shared_player_character04_03_off.png",
	"image/shared_player_character01_04_off.png",
	"image/shared_player_character02_04_off.png",
	"image/shared_player_character03_04_off.png",
	"image/shared_player_character04_04_off.png",
};

////********this will be deleted**************
const std::string SHARED_PLAYERUI_BACKGROUND[8] =
{
	"image/shared_playerui_bg_unselected01.png",
	"image/shared_playerui_bg_unselected02.png",
	"image/shared_playerui_bg_unselected03.png",
	"image/shared_playerui_bg_unselected04.png",
	"image/shared_playerui_bg_selected01.png",
	"image/shared_playerui_bg_selected02.png",
	"image/shared_playerui_bg_selected03.png",
	"image/shared_playerui_bg_selected04.png",
};
///


const std::string SHARED_PLAYERUI_BG_WAIT[4] =
{
    "image/shared_playerui_bg_unselected01.png",
    "image/shared_playerui_bg_unselected02.png",
	"image/shared_playerui_bg_unselected03.png",
	"image/shared_playerui_bg_unselected04.png"
};

const std::string SHARED_PLAYERUI_BG_TURN[4] =
{
    "image/shared_playerui_bg_selected01.png",
	"image/shared_playerui_bg_selected02.png",
	"image/shared_playerui_bg_selected03.png",
	"image/shared_playerui_bg_selected04.png"
};

/*added animation*/

const std::string PLAYSCENE_LAND_ANI[4] =
{
    "image/PLAYSCENE_ani_land_1.png",
    "image/PLAYSCENE_ani_land_2.png",
    "image/PLAYSCENE_ani_land_3.png",
    "image/PLAYSCENE_ani_land_4.png"
};

const int PLAYSCENE_LAND_FRAME = 48;

const std::string PLAYSCENE_LAND_ANI_PLIST[4] =
{
    "image/PLAYSCENE_ani_land_1.plist",
    "image/PLAYSCENE_ani_land_2.plist",
    "image/PLAYSCENE_ani_land_3.plist",
    "image/PLAYSCENE_ani_land_4.plist"
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
const std::string SHARED_POPUP_BG_OPA = "image/shared_popup_background_opa.png";
const std::string SHARED_POPUP_TITLE = "image/shared_popup_paused.png";
const std::string SHARED_POPUP_RESUME = "image/shared_popup_resume.png";
const std::string SHARED_POPUP_HELP = "image/shared_popup_help.png";
const std::string SHARED_POPUP_SETTING = "image/shared_popup_setting.png";
const std::string SHARED_POPUP_QUIT = "image/shared_popup_quit.png";
#define SHARED_POPUP_BG_POS 197,223
#define SHARED_POPUP_TITLE_POS 1045
#define SHARED_POPUP_MENU_MARGIN 130
#define SHARED_POPUP_BOTTOM_MARGIN 533

const std::string SHARED_POPUP_HELP_TITLE = "image/shared_popup_help_title.png";
const std::string SHARED_POPUP_HELP_CON = "image/shared_popup_help_con.png";
const std::string SHARED_POPUP_HELP_ANI = "image/ani_help_hand.png";
const std::string SHARED_POPUP_HELP_ANI_PLIST = "image/ani_help_hand.plist";
#define SHARED_POPUP_HELP_TITLE_POS 888,1045
#define SHARED_POPUP_HELP_CON_POS 460,454


const std::string SHARED_MENU1_UNSELECTED = "image/shared_menu01_unselected.png";
const std::string SHARED_MENU2_UNSELECTED = "image/shared_menu02_unselected.png";
const std::string SHARED_MENU3_UNSELECTED = "image/shared_menu03_unselected.png";

const std::string SHARED_MENU1_SELECTED = "image/shared_menu01_selected.png";
const std::string SHARED_MENU2_SELECTED = "image/shared_menu02_selected.png";
const std::string SHARED_MENU3_SELECTED = "image/shared_menu03_selected.png";

const std::string SHARED_PLAYER_UI_UPPER_LEFT_SELECTED = "image/shared_playerui_background_upper_left_selected.png";
const std::string SHARED_PLAYER_UI_UPPER_LEFT_UNSELECTED = "image/shared_playerui_background_upper_left_unselected.png";
const std::string SHARED_PLAYER_UI_UPPER_RIGHT_SELECTED = "image/shared_playerui_background_upper_right_selected.png";
const std::string SHARED_PLAYER_UI_UPPER_RIGHT_UNSELECTED = "image/shared_playerui_background_upper_right_unselected.png";
const std::string SHARED_PLAYER_UI_BELOW_LEFT_SELECTED = "image/shared_playerui_background_below_left_selected.png";
const std::string SHARED_PLAYER_UI_BELOW_LEFT_UNSELECTED = "image/shared_playerui_background_below_left_unselected.png";
const std::string SHARED_PLAYER_UI_BELOW_RIGHT_SELECTED = "image/shared_playerui_background_below_right_selected.png";
const std::string SHARED_PLAYER_UI_BELOW_RIGHT_UNSELECTED = "image/shared_playerui_background_below_right_unselected.png";

#define SHARED_PLAYER_UI_UPPER_LEFT_POS 20,1091
#define SHARED_PLAYER_UI_UPPER_RIGHT_POS 1337,1091
#define SHARED_PLAYER_UI_BELOW_LEFT_POS 20,20
#define SHARED_PLAYER_UI_BELOW_RIGHT_POS 1337,20
// window에서 실행할 때는 해당 폰트를 설치해주세요 'Paper Johnny Eineinhalb.ttf'
#define GAME_FONT "Paper Johnny Eineinhalb"