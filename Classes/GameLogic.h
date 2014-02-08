#pragma once
#include "cocos2d.h"
#include "config.h"
#include <array>

//플레이어 데이터
struct PlayerData
{
	PlayerData() : m_PlayerId(-1), m_PlayerName("GGulHoaDDuk"), m_CharacterId(-1),m_PlayerTurn(-1),m_nextPlayer(nullptr),
						m_MyTile(0), m_MyGold(0), m_MyTrash(0), m_MyTotalScore(0) {}

	//플레이어의 고유 아이디 ( 온라인 모드일 시 clientID를 의미 )
	int m_PlayerId;

	//플레이어 이름은 저장된 것이 있다면 알아서 불러오도록 한다.
	std::string m_PlayerName;
	
	int m_CharacterId;
	
	int m_PlayerTurn;
	PlayerData* m_nextPlayer;

	int m_MyTile;
	int m_MyGold;
	int m_MyTrash;

	int m_MyTotalScore;
};

//몬스터 캐릭터에 관한 자료 ( 추가 필요 )
struct Character
{
	Character() : m_CharacterName(""),m_isCharacterSelected(false) {}

	std::string m_CharacterName;

	cocos2d::ccColor4B m_CharacterColor;

	std::string m_CharacterSettingImage;
	std::string m_CharacterPlayImage;
	std::string m_CharacterResultImage;
	std::string m_CharacterVoice;
	bool m_isCharacterSelected;
};

class CGameLogic
{
public:
	CGameLogic(void);
	~CGameLogic(void);

	static CGameLogic* CGameLogic::GetInstance();
	static void				ReleaseInstance();

	bool init();

	//조심해!!
	//이 함수는 필요 없을 것 같음. m_PlayerId = playerIdx 이므로 이미 알고 있는 정보를 다시 요청하는 것 같음
	int GetPlayerId(int playerIdx) { return m_PlayerData[playerIdx]->m_PlayerId; }
	int GetPlayerTurnById(int playerId) { return m_PlayerData[playerId]->m_PlayerTurn; }
	int GetPlayerIdByTurn(int currentTurn);
	int GetPlayerIdByCurrentTurn() { return GetPlayerIdByTurn(m_currentTurn % m_CurrentPlayerNumber);}
	PlayerData* GetFirstPlayer() { return m_FirstPlayer; }

	//캐릭터를 플레이어에게 짝지어 준다.
	bool SetPlayerCharacterId(int characterId);
	bool isCharacterSelected(int characterId) {return m_Character[characterId].m_isCharacterSelected;}
	int   GetPlayerCharacterId(int playerId) { return m_PlayerData[playerId]->m_CharacterId;}

	bool   SetPlayerName(int playerId, const std::string& playerName);
	const std::string& GetPlayerName(int playerId)				{ return m_PlayerData[playerId]->m_PlayerName; }
	
	const std::string& GetPlayerSettingImage(int playerId)		{ return m_Character[m_PlayerData[playerId]->m_CharacterId].m_CharacterSettingImage; }
	const std::string& GetPlayerPlayImage(int playerId)			{ return m_Character[m_PlayerData[playerId]->m_CharacterId].m_CharacterPlayImage; } 
	const std::string& GetPlayerResultImage(int playerId)		{ return m_Character[m_PlayerData[playerId]->m_CharacterId].m_CharacterResultImage; }
	const cocos2d::ccColor4B& GetPlayerColor(int playerId)		{ return m_Character[m_PlayerData[playerId]->m_CharacterId].m_CharacterColor; }

	const std::string& GetCharacterSettingImage(int characterId)		{ return m_Character[characterId].m_CharacterSettingImage; }
	const std::string& GetCharacterPlayImage(int characterId)			{ return m_Character[characterId].m_CharacterPlayImage; } 
	const std::string& GetCharacterResultImage(int characterId)			{ return m_Character[characterId].m_CharacterResultImage; }
	const cocos2d::ccColor4B& GetCharacterColor(int characterId)		{ return m_Character[characterId].m_CharacterColor; }

	bool			SetSelectedMapSize( MapSelect mapSize );
	MapSelect		GetSelectedMapSize() { return m_SelectedMapSize; }

	bool		SetCurrentPlayerNumber(int playerNumber)			{ if ( playerNumber < m_PlayerNumberOfThisGame ) { m_CurrentPlayerNumber = playerNumber; } return true; }
	int			GetCurrentPlayerNumber()							{ return m_CurrentPlayerNumber; }

	bool IsPossible(IndexedPosition indexedPosition);
	bool IsClosed(IndexedPosition indexedPosition);

	/*	Setting Scene 관련에서 게임 시작까지	*/
	// 플레이어 숫자와 맵 크기를 골랐는지
	bool isPlayerNumberAndMapSeleted() { return ( MapSelected && PlayerNumberSelected ); };
	void SetPlayerNumberOfThisGame( int playerNumber ) { 
		if (playerNumber <= MAX_PLAYER_NUM)
		{
			m_PlayerNumberOfThisGame = playerNumber;
			PlayerNumberSelected = true;
		}
	}
	int GetPlayerNumberOfThisGame() { return m_PlayerNumberOfThisGame; }
	bool StartGame();
	void CreateMap();
	void InitRandomMap();

	/* 주어진 index로 선을 연결한다. */
	bool EventHandle(IndexedPosition indexedPosition);
	void DrawLine(const IndexedPosition& indexedPosition);

	/*	주어진 index의 울타리 주변 타일을 확인 합니다 */
	void CollectClosedTile(IndexedPosition indexedPosition, Direction direction);

	/*	IsClosed함수에서 탐색 중인 타일이 이미 탐색된 곳인지 체크하는 함수입니다 */
	bool IsAlreadyChecked(const IndexedPosition& nextTile);

	void		UpdatePlayerResult(int playerId, MO_ITEM item);
	int			GetPlayerResult(int playerId, MO_ITEM item);

	void		UpdatePlayerScore(int playerId, int score)	{ m_PlayerData[playerId]->m_MyTotalScore += score; }
	int			GetPlayerTotalScore(int playerId)			{ return m_PlayerData[playerId]->m_MyTotalScore; }

	int			GetWinnerIdx();

	bool IsEnd();

	MO_TYPE IsConnected(IndexedPosition indexedPosition);

	/*	애니메이션 상태를 지정, 반환하는 함수들 */
	bool		GetLineAnimationFlag()									{ return m_LineAnimationFlag; }
	int			GetTileAnimationTurnNumber()							{ return m_TileAnimationTurnNumber; }
	void		SetTileAnimationTurnNumber(int turnNumber)				{ m_TileAnimationTurnNumber = turnNumber; }
	void		SetAnimationState(IndexedPosition indexedPosition, int turn, Direction direction);
	void		InitAnimationState(IndexedPosition indexedPosition);
	void		SetTileAnimationTurn(int turn)							{ m_TileAnimationTurn = turn; }
	int			GetTileAnimationTurn(IndexedPosition indexedPosition);

	/* 타일의 타입을 가져오는 함수 */
	MO_TYPE		GetMapType(IndexedPosition indexedPosition) { return m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Type;}
	MO_OWNER	GetMapOwner(IndexedPosition indexedPosition) {return m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Owner; }
	MO_ITEM		GetItem(IndexedPosition indexedPosition)	{ return m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Item; }

private:
	static CGameLogic*	m_pInstance; //singleton instance

	MapSelect				m_SelectedMapSize;
	int						m_CurrentPlayerNumber;
	int						m_PlayerNumberOfThisGame;

	// 플레이어 데이터를 가지고 있는 구조체
	std::array<PlayerData*, MAX_PLAYER_NUM> m_PlayerData;
	std::array<Character, CHARACTER_NUM> m_Character;
	PlayerData* m_FirstPlayer;

	//플레이 순서에 매칭되는 PlayerData의 포인터
	//std::list<PlayerData*> m_PlayerDataByTurn;

	/*	SettingScene 관련 변수들	*/
	bool MapSelected;
	bool PlayerNumberSelected;

	/*	맵 관련 변수들 */

	//맵에 대한 정보를 저장하기 위한 배열 ( 실제 게임 상황이 실시간으로 업데이트 되어야 하는 배열 ) 
	//조심해!! MapObjMap은 이름이 왜 저모양인지?
	template <typename IType, int ROW, int COL>
	struct array2d_
	{
		typedef std::array< std::array<IType, COL>, ROW> type ;
	} ;

	typedef array2d_<MapObject, MAX_MAP_WIDTH, MAX_MAP_HEIGHT>::type MapObjMap ;
	MapObjMap m_Map;

	/*	주인이 없는 타일의 수를 저장하는 변수 : 종료 조건을 쉽게 확인하기 위해서 생성 */
	int	m_VoidTileCount;

	/*	turn관련 변수 */
	int m_currentTurn;

	/* 닫힌 도형 검사용 배열 */
	std::array<IndexedPosition, CHECKLIST_LENGTH> m_ClosedTile;

	/*	타일 탐색 시 탐색 여부를 확인하는 flag 지정 및 확인 */
	void		SetMapFlag(IndexedPosition indexedPosition,bool flag);
	bool		GetMapFlag(IndexedPosition indexedPosition) { return m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Flag; }

	/*	타일의 선을 연결하는 함수	*/
	void DeleteLine( const IndexedPosition& indexedPosition );

	/*	아이템 관련 함수 */
	void		SetItem(IndexedPosition indexedPosition, MO_ITEM item);

	/* 애니메이션 관련 변수들 */
	bool	m_LineAnimationFlag;
	int		m_TileAnimationTurnNumber;
	int		m_TileAnimationTurn;
	bool	m_TileAnimationTurnOver;

	// implement the "static node()" method manually
    //CREATE_FUNC(CGameLogic);
};

