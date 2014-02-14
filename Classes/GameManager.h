#pragma once
#include "cocos2d.h"
#include "config.h"

class CGameManager
{
public:
	CGameManager(void);
	~CGameManager(void);

	static CGameManager* GetInstance();
	static void				ReleaseInstance();
	
	bool init();

	int GetCurrentPlayerNumber();
	void SetCurrentPlayerNumber(int PlayerNumber);

	int GetPlayerNumberOfThisGame();
	bool GetStatusPlayerNumber(int playerNumber);
	void SetPlayerNumberOfThisGame(int PlayerNumber);

	//������ �¶������� ������������ ����
	void SetOnlineMode(bool flag);
	bool IsOnlineMode() { return m_IsOnlineGame; }

	//������ ���� ��Ȳ�� �˾ƺ��� �Լ�
	void SetUpdateFlag(bool flag)	{ m_IsUpdated = flag; }
	bool IsUpdated()				{ return m_IsUpdated; }
	bool IsEnd();

	/* ���� ���� ���� */
	// �÷��̾� ���ڿ� �� ũ�⸦ ������� ���θ� �Ǵ�, NEXT ��ư�� �������� �Ǵ�
	bool IsPlayerNumberAndMapSeleted();
	bool IsNextButtonSelected();
	void SetNextButtonSelected();

	// �̸�
	void SetPlayerName(int playerId, const std::string& playerName);
	const std::string& GetPlayerName(int playerIdx);

	// ĳ����
	void SelectCharacter(int characterId);
	bool isCharacterSelected(int characterId);
	int	  GetCharacterId(int playerId);

	// ��
	void		SetMapSize(MapSelect mapSize);
	MapSelect	GetSelectedMapSize();
	MO_TYPE		GetMapType(IndexedPosition indexedPosition);
	MO_TYPE		GetMapType(const int& i, const int& j) { return GetMapType(IndexedPosition(i, j) );}
	MO_OWNER	GetMapOwner(IndexedPosition indexedPosition); 
	MO_OWNER	GetMapOwner( const int& i , const int& j ) {return GetMapOwner(IndexedPosition(i, j));}
	MO_ITEM		GetItem(IndexedPosition indexedPosition);
	MO_ITEM		GetItem( const int& i , const int& j ) { return GetItem(IndexedPosition(i,j));}
	void		DrawLine(IndexedPosition indexedPosition);
	int			GetTileAnimationTurn(IndexedPosition indexedPosition);

	// �÷��̾� ����
	// ���� �Ͽ� �ش��ϴ� �÷��̾� 'ID'�� ��ȯ�Ѵ�.
	int  GetPlayerIdByTurn(int currentTurn);
	const std::string& GetCharacterPlayFaceById(int playerIdx);
	int  GetPlayerTurn(int playerId);
	int  GetCurrentPlayerId();

	void StartGame();
	
	/* ���� ���� ���� : �ǽð� ���� ����� ���� �ʿ��� �ϵ��� �Ѵ�.*/
	void UpdateGameMap();
	MO_TYPE IsConnected(IndexedPosition indexedPosition);
	void TimeOut();
	
	//������!!
	//�Ʒ��� �Լ����� ȣ���� �ʿ䰡 ����(���� ���ο����� ����ϴ� �Լ���)
	//bool IsPossible(IndexedPosition indexedPosition);
	//bool IsClosed(IndexedPosition indexedPosition);
	
	//result scene ����
	int GetWinnerIdx();
	int GetElementCount (int playerIdx, MO_ITEM item);
	int GetTotalScore(int playerIdx);
	const std::string& GetCharacterResultFaceFileName(int playerIdx);

	// network game ���� Ȯ��
	bool InitNetworkLogic();
	void Login();

	NetworkPhase GetCurrentNetworkPhase();

	// game data ���� ����
	std::string GetUsersName();
	std::string GetTokenId();
	bool		GetPlayerNumberSelection(int number);

	void SetUsersName(std::string name);
	void SetTokenId(std::string tokenId);
	void SetPlayerNumberSelection(int number, bool selection);


private:
	static CGameManager*	m_pInstance; //singleton instance

	cocos2d::CCUserDefault *m_GameData;

	bool m_IsOnlineGame;
	bool m_IsUpdated;
	//CCUserDefault m_SharedData;

	//ĳ���� �̸��̳� �� ���� �������� �Ŵ����� ĳ���ؼ� ������ �ִ� ���� ���� ��
	//��� �� �����͸� ������� ���𰡸� �Ǵ��ϴ� ������ ������ ����(�ϴ� ��ǲ�� ������ �����ϰ� ������� �޴� ��� ����)

	// implement the "static node()" method manually
    //CREATE_FUNC(CGameManager);
};

