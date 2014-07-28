#pragma once
#include "cocos2d.h"
#include "config.h"

class CGameManager
{
public:
	CGameManager(void);
	~CGameManager(void);

	static CGameManager*	GetInstance();
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
	SceneName	GetCurrentScene();
	void		SetUpdateFlag(bool flag)	{ m_IsUpdated = flag; }
	bool		IsUpdated()				{ return m_IsUpdated; }
	bool		IsEnd();

	/* ���� ���� ���� */
	// �÷��̾� ���ڿ� �� ũ�⸦ ������� ���θ� �Ǵ�, NEXT ��ư�� �������� �Ǵ�
	bool IsPlayerNumberAndMapSeleted();
	bool IsNextButtonSelected();
	void SetNextButtonSelected();

	// �̸�
	void SetPlayerName(int playerId, const std::string& playerName);
	const std::string& GetPlayerName(int playerIdx);
	std::string GetPlayerNameByCharacterId(int characterId);

	// ĳ����
	void SelectCharacter(int characterId);
	void SelectCharacter(int playerId, int characterId);
	bool IsCharacterSelected(int characterId);
	int GetCharacterIdByPlayerId(int playerId);
	int GetPlayerIdByCharactyerId(int characterId);

	void SetPlayerFrameSelected(int playerId, bool status);
	int GetPlayerFrameSelected();

	// �÷��̾�
	bool IsPlayerJoinedGame(int characterId);

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
    void SetPlayReady();
    void PausePlayReady();
	
	//������!!
	//�Ʒ��� �Լ����� ȣ���� �ʿ䰡 ����(���� ���ο����� ����ϴ� �Լ���)
	//bool IsPossible(IndexedPosition indexedPosition);
	//bool IsClosed(IndexedPosition indexedPosition);
	
	//result scene ����
	bool IsWinner(int idx);
	int GetElementCount (int playerIdx, MO_ITEM item);
	int GetTotalScore(int playerIdx);
	const std::string& GetCharacterResultFaceFileName(int playerIdx);

	// network ���� �Լ�
	bool InitNetworkLogic();
    void SetConnectionStatus(bool status) { m_ConnectionStatus = status; }
    bool GetConnectionStatus() { return m_ConnectionStatus; }
    
    void AuthenticationCheck();
    void GetGoogleNick();

	void Login();
	void Logout();
    void EndGame();

	void JoinUpdate(float dt);
	void PlayUpdate(float dt);
	void PlayReady();

	NetworkPhase    GetCurrentNetworkPhase();
    LoginPhase      GetCurrentLoginPhase();
    void            SetCurrentLoginPhase(LoginPhase phase);

	// network::playReady ������ ���� �Լ�
	void	SetAnimationDelay(int time);
	float	GetAnimationDelay() { return m_AnimationDelay; }
    void    InitAnimationDelay();

	// game data ���� ����
	std::string GetUsersName();
	std::string GetTokenId();
	bool		GetPlayerNumberSelection(int number);
	int			GetMyPlayerId();

	void SetUsersName(std::string name);
	void SetTokenId(std::string tokenId);
	void SetPlayerNumberSelection(int number, bool selection);
    
	bool IsChannelMaster();
	bool IsReady();
	bool IsReady(int playerId);
	bool IsAllReady();
	bool GetCurrentTimerStatus();
    
    void SetSeenFirstTutorialFlag(bool flag);
    bool GetSeenFirstTutorialFlag();
    
    void SetFindingChannelTimeOut(bool flag) { m_IsFindingChannelTimeOut = flag; }
    bool GetFindingChannelTimeOut() { return m_IsFindingChannelTimeOut; }
    
    void SetLineStateChanged(bool flag) { m_IsLineStateChanged = flag; }
    bool GetLineStateChanged() { return m_IsLineStateChanged; }
    
    void SetRecentConnectedLine( IndexedPosition position ) { m_RecentConnectedLine = position; m_IsLineStateChanged = true; }
    IndexedPosition GetRecentConnectedLine() { return m_RecentConnectedLine; }
    
    // void SetGameEndFlag(bool flag) { m_IsGameEnd = flag; }
    // bool GetGameEndFlag() { return m_IsGameEnd; }

private:
	static CGameManager*	m_pInstance; //singleton instance

	cocos2d::CCUserDefault *m_GameData;

	bool m_IsOnlineGame;
	bool m_IsUpdated;
    bool m_ConnectionStatus;

	float m_AnimationDelay;
    
    bool m_IsFindingChannelTimeOut;
    IndexedPosition m_RecentConnectedLine;
    bool m_IsLineStateChanged;
    
    // bool m_IsGameEnd;
    
	//CCUserDefault m_SharedData;

	//ĳ���� �̸��̳� �� ���� �������� �Ŵ����� ĳ���ؼ� ������ �ִ� ���� ���� ��
	//��� �� �����͸� ������� ���𰡸� �Ǵ��ϴ� ������ ������ ����(�ϴ� ��ǲ�� ������ �����ϰ� ������� �޴� ��� ����)

	// implement the "static node()" method manually
    //CREATE_FUNC(CGameManager);
};

