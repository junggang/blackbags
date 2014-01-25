#pragma once
#include "ccTypes.h"

/*	���� ȭ�� �⺻ ũ���Դϴ� */
const int WINDOW_WIDTH = 1250;
const int WINDOW_HEIGHT = 700;


/*	�ִ� �÷��� ���� �ο��Դϴ� */
const int MAX_PLAYER_NUM= 4;

/* ĳ���� �� �Դϴ� */
const int CHARACTER_NUM = 4;


/*	���� �޴� ������Ʈ���� �⺻ ũ���Դϴ� */
const float SC_M_DEFAULT_MENU_BUTTON_WIDTH = 225.0f;
const float SC_M_DEFAULT_MENU_BUTTON_HEIGHT = 60.0f;
const float SC_M_DEFAULT_TITLE_WIDTH = 500.0F;
const float SC_M_DEFAULT_TITLE_HEIGHT = 220.0F;
const float SC_M_DEFAULT_TITLE_MARGIN = 20.0F;
const float SC_M_DEFAULT_MENU_MARGIN = 40.0F;

/*	��Ʈ��ũ �̸� �Է� �޴� ������Ʈ���� �⺻ ũ���Դϴ�	*/
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

/*	���� �޴� ������Ʈ���� �⺻ ũ���Դϴ�	*/
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

/*	settingScene �ʻ�ȭ ũ��	*/
const float SC_S_DEFAULT_PORTRAIT_WIDTH = 190.f;
const float SC_S_DEFAULT_PORTRAIT_HEIGHT = 230.f;

/*	������ ���ؼ� ��׵��� y �������� �޾ƵӴϴ� */
const int	SC_S_DEFAULT_PLAYER_BUTTON_Y_POSITION_SCALE = 5;
const int   SC_S_DEFAULT_NEXT_BUTTON_Y_POSITION_SCALE = 9;
const int   SC_S_DEFAULT_MAP_BUTTON_Y_POSITION_SCALE = 8;

/*	� �÷��̾ ���õǾ����� �˱� ���� MASK ����	*/
const int	MASK_PLAYER_1 = 1;
const int	MASK_PLAYER_2 = 2;
const int	MASK_PLAYER_3 = 4;
const int	MASK_PLAYER_4 = 8;

/*	���� �� ������Ʈ���� �⺻ ũ���Դϴ� */
const float DEFAULT_TILE_SIZE = 80.0f;
const float DEFAULT_LINE_WEIGHT = 10.0f;
const float DEFAULT_DOT_RADIUS = 6.0f;
const float DEFAULT_ITEM_RADIUS = 4.0f;

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

/*	���� �� ũ���Դϴ� */
const int MAX_MAP_WIDTH = 23;
const int MAX_MAP_HEIGHT = 23;

/* ���� �� ������Ʈ�� ���� �Դϴ� */
const int MO_TYPE_NUMBER = 6;

/*	���� �ʱ�ȭ �� �� �� Ž���ϴ� �迭 ���� (�Լ� ���� ���� �� ���� ����) */
const int CHECKLIST_LENGTH = 100;

/*	��ġ �ν� ���� */
const float TOUCH_AREA = 30.0f;

/*	��� ȭ�� ������Ʈ���� �⺻ ũ���Դϴ� */
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

/*	ũ���� �ſ��� �ҷ��� ��������Դϴ�	*/
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


/*	��Ʈ���Դϴ�	*/
#define _DEBUG_FONT L"Consolas"
#define _MENU_FONT L"Segoe UI"
#define _UI_FONT L"Comic Sans MS"

/*	�÷��̾� �����Դϴ�	*/
#define _COLOR_PLAYER_1_ 26.0f/255, 196.0f/255, 98.0f/255, 0.75f
#define _COLOR_PLAYER_2_ 28.0f/255, 171.0f/255, 203.0f/255, 0.75f
#define _COLOR_PLAYER_3_ 206.0f/255, 62.0f/255, 5.0f/255, 0.6f
#define _COLOR_PLAYER_4_ 241.0f/255, 196.0f/255, 15.0f/255, 0.75f

/* ĳ���� �����Դϴ� */
#define _COLOR_CHARACTER_1_  26,196,98,255
#define  _COLOR_CHARACTER_2_  28,171,203,255
#define  _COLOR_CHARACTER_3_  206, 62,5,255
#define  _COLOR_CHARACTER_4_  241,196,15,255


/*	enum Ÿ�Ե��Դϴ�. */
enum SceneName	//Scene �̸���
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

enum SOUND_BGMList
{
	BGM_MAIN,
	BGM_SETTING,
	BGM_PLAY,
	BGM_RESULT
};

enum MO_TYPE	//���� �� �⺻ �ڷ���
{
	MO_SENTINEL,
	MO_DOT = 10,
	MO_LINE_UNCONNECTED = 20,
	MO_LINE_CONNECTED,
	MO_LINE_HIDDEN,
	MO_TILE = 30,
};

enum MO_OWNER	//���� �� �� Ÿ�� ������
{
	MO_NOBODY = -1,
	MO_PLAYER1,
	MO_PLAYER2,
	MO_PLAYER3,
	MO_PLAYER4
};

enum MO_ITEM	//Ÿ�Ͽ� ������ ������
{
	ITEM_NOTHING,
	ITEM_GOLD,
	ITEM_TRASH
};

enum Direction	//���� �� Ž�� �� Ȱ��Ǵ� ����
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

struct MapSize //�� ũ�Ⱚ�� ���� ����ü�Դϴ�
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

/*	���� ���� Ÿ�� ��ǥ�� ǥ���ϱ� ���� ����ü */
struct IndexedPosition
{
	IndexedPosition() : m_PosI(0), m_PosJ(0) {}

	IndexedPosition(const IndexedPosition& inputIndexedPosition)
	{
		m_PosI = inputIndexedPosition.m_PosI;
		m_PosJ = inputIndexedPosition.m_PosJ;
	}

	/*	���� ���� ������ �������̵�
		queue���� ���� push�ص� ���縦 �� ���ݴϴ� */
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
	"image/MO_line_vertical.png",
	"image/MO_line_horizontal.png",
	"image/MO_line_vertical_c.png",
	"image/MO_line_horizontal_c.png",
};

const std::string TileImageFileList[5] =
	{
		"image/MO_tile0.png",
		"image/MO_tile1.png",
		"image/MO_tile2.png",
		"image/MO_tile3.png",
		"image/MO_tile_void.png"
	};