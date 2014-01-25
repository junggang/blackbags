#pragma once
#include "cocos2d.h"
#include "config.h"
#include <array>

//�÷��̾� ������
struct PlayerData
{
	PlayerData() : m_PlayerId(-1), m_PlayerName("��ȣ��"), m_CharacterId(-1),m_PlayerTurn(-1),m_nextPlayer(nullptr),
						m_MyTile(0), m_MyGold(0), m_MyTrash(0), m_MyTotalScore(0) {}

	//�÷��̾��� ���� ���̵� ( �¶��� ����� �� clientID�� �ǹ� )
	int m_PlayerId;

	//�÷��̾� �̸��� ����� ���� �ִٸ� �˾Ƽ� �ҷ������� �Ѵ�.
	std::string m_PlayerName;
	
	int m_CharacterId;
	
	int m_PlayerTurn;
	PlayerData* m_nextPlayer;

	int m_MyTile;
	int m_MyGold;
	int m_MyTrash;

	int m_MyTotalScore;
};

//���� ĳ���Ϳ� ���� �ڷ� ( �߰� �ʿ� )
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

	//������!!
	//�� �Լ��� �ʿ� ���� �� ����. m_PlayerId = playerIdx �̹Ƿ� �̹� �˰� �ִ� ������ �ٽ� ��û�ϴ� �� ����
	int GetPlayerId(int playerIdx) { return m_PlayerData[playerIdx]->m_PlayerId; }
	int GetPlayerTurnById(int playerId) { return m_PlayerData[playerId]->m_PlayerTurn; }
	int GetPlayerIdByTurn(int currentTurn);
	PlayerData* GetFirstPlayer() { return m_FirstPlayer; }

	//ĳ���͸� �÷��̾�� ¦���� �ش�.
	bool SetPlayerCharacterId(int characterId);
	bool isCharacterSelected(int characterId) {return m_Character[characterId].m_isCharacterSelected;}
	int   GetPlayerCharacterId(int playerId) { return m_PlayerData[playerId]->m_CharacterId;}

	bool   SetPlayerName(int playerId, const std::string& playerName);
	const std::string& GetPlayerName(int playerId)				{ return m_PlayerData[playerId]->m_PlayerName; }
	
	const std::string& GetPlayerSettingImage(int playerId)		{ return m_Character[m_PlayerData[playerId]->m_CharacterId].m_CharacterSettingImage; }
	const std::string& GetPlayerPlayImage(int playerId)			{ return m_Character[m_PlayerData[playerId]->m_CharacterId].m_CharacterPlayImage; } 
	const std::string& GetPlayerResultImage(int playerId)		{ return m_Character[m_PlayerData[playerId]->m_CharacterId].m_CharacterResultImage; }
	const cocos2d::ccColor4B& GetPlayerColor(int playerId)		{ return m_Character[m_PlayerData[playerId]->m_CharacterId].m_CharacterColor; }

	bool			SetSelectedMapSize( MapSelect mapSize );
	MapSelect		GetSelectedMapSize() { return m_SelectedMapSize; }

	bool		SetPlayerNumber(int playerNumber)			{ m_PlayerNumber = playerNumber; return true; }
	int			GetplayerNumber()							{ return m_PlayerNumber; }

	bool IsPossible(IndexedPosition indexedPosition);
	bool IsClosed(IndexedPosition indexedPosition);

	/*	Setting Scene ���ÿ��� ���� ���۱���	*/
	bool StartGame();
	void CreateMap();
	void InitRandomMap();

	/* �־��� index�� ���� �����Ѵ�. */
	bool EventHandle(IndexedPosition indexedPosition);
	void DrawLine(const IndexedPosition& indexedPosition);

	/*	�־��� index�� ��Ÿ�� �ֺ� Ÿ���� Ȯ�� �մϴ� */
	void CollectClosedTile(IndexedPosition indexedPosition, Direction direction);

	/*	IsClosed�Լ����� Ž�� ���� Ÿ���� �̹� Ž���� ������ üũ�ϴ� �Լ��Դϴ� */
	bool IsAlreadyChecked(const IndexedPosition& nextTile);

	void		UpdatePlayerResult(int playerId, MO_ITEM item);
	int			GetPlayerResult(int playerId, MO_ITEM item);

	void		UpdatePlayerScore(int playerId, int score)	{ m_PlayerData[playerId]->m_MyTotalScore += score; }
	int			GetPlayerTotalScore(int playerId)			{ return m_PlayerData[playerId]->m_MyTotalScore; }

	int			GetWinnerIdx();

	bool IsEnd();

	MO_TYPE IsConnected(IndexedPosition indexedPosition);

	/*	�ִϸ��̼� ���¸� ����, ��ȯ�ϴ� �Լ��� */
	bool		GetLineAnimationFlag()									{ return m_LineAnimationFlag; }
	int			GetTileAnimationTurnNumber()							{ return m_TileAnimationTurnNumber; }
	void		SetTileAnimationTurnNumber(int turnNumber)				{ m_TileAnimationTurnNumber = turnNumber; }
	void		SetAnimationState(IndexedPosition indexedPosition, int turn, Direction direction);
	void		InitAnimationState(IndexedPosition indexedPosition);
	void		SetTileAnimationTurn(int turn)							{ m_TileAnimationTurn = turn; }
	int			GetTileAnimationTurn(IndexedPosition indexedPosition);

	/* Ÿ���� Ÿ���� �������� �Լ� */
	MO_TYPE		GetMapType(IndexedPosition indexedPosition) { return m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Type;}
	MO_OWNER	GetMapOwner(IndexedPosition indexedPosition) {return m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Owner; }
	MO_ITEM		GetItem(IndexedPosition indexedPosition)	{ return m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Item; }

private:
	static CGameLogic*	m_pInstance; //singleton instance

	MapSelect				m_SelectedMapSize;
	int						m_PlayerNumber;
	int						m_CurrentTurn;

	// �÷��̾� �����͸� ������ �ִ� ����ü
	std::array<PlayerData*, MAX_PLAYER_NUM> m_PlayerData;
	std::array<Character, CHARACTER_NUM> m_Character;
	PlayerData* m_FirstPlayer;

	//�÷��� ������ ��Ī�Ǵ� PlayerData�� ������
	//std::list<PlayerData*> m_PlayerDataByTurn;

	/*	�� ���� ������ */

	//�ʿ� ���� ������ �����ϱ� ���� �迭 ( ���� ���� ��Ȳ�� �ǽð����� ������Ʈ �Ǿ�� �ϴ� �迭 ) 
	//������!! MapObjMap�� �̸��� �� ���������?
	template <typename IType, int ROW, int COL>
	struct array2d_
	{
		typedef std::array< std::array<IType, COL>, ROW> type ;
	} ;

	typedef array2d_<MapObject, MAX_MAP_WIDTH, MAX_MAP_HEIGHT>::type MapObjMap ;
	MapObjMap m_Map;

	/*	������ ���� Ÿ���� ���� �����ϴ� ���� : ���� ������ ���� Ȯ���ϱ� ���ؼ� ���� */
	int	m_VoidTileCount;

	/*	turn���� ���� */
	int m_currentTurn;

	/* ���� ���� �˻�� �迭 */
	std::array<IndexedPosition, CHECKLIST_LENGTH> m_ClosedTile;

	/*	Ÿ�� Ž�� �� Ž�� ���θ� Ȯ���ϴ� flag ���� �� Ȯ�� */
	void		SetMapFlag(IndexedPosition indexedPosition,bool flag);
	bool		GetMapFlag(IndexedPosition indexedPosition) { return m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Flag; }

	/*	Ÿ���� ���� �����ϴ� �Լ�	*/
	void DeleteLine( const IndexedPosition& indexedPosition );

	/*	������ ���� �Լ� */
	void		SetItem(IndexedPosition indexedPosition, MO_ITEM item);


	/* �ִϸ��̼� ���� ������ */
	bool	m_LineAnimationFlag;
	int		m_TileAnimationTurnNumber;
	int		m_TileAnimationTurn;
	bool	m_TileAnimationTurnOver;

	// implement the "static node()" method manually
    //CREATE_FUNC(CGameLogic);
};

