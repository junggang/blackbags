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

	//게임이 온라인인지 오프라인인지 설정
	void SetOnlineMode(bool flag);
	bool IsOnlineMode() { return m_IsOnlineGame; }

	//게임의 현재 상황을 알아보는 함수
	SceneName	GetCurrentScene();
	void		SetUpdateFlag(bool flag)	{ m_IsUpdated = flag; }
	bool		IsUpdated()				{ return m_IsUpdated; }
	bool		IsEnd();

	/* 게임 셋팅 관련 */
	// 플레이어 숫자와 맵 크기를 골랐는지 여부를 판단, NEXT 버튼을 눌렀는지 판단
	bool IsPlayerNumberAndMapSeleted();
	bool IsNextButtonSelected();
	void SetNextButtonSelected();

	// 이름
	void SetPlayerName(int playerId, const std::string& playerName);
	const std::string& GetPlayerName(int playerIdx);
	std::string GetPlayerNameByCharacterId(int characterId);

	// 캐릭터
	void SelectCharacter(int characterId);
	void SelectCharacter(int playerId, int characterId);
	bool IsCharacterSelected(int characterId);
	int GetCharacterIdByPlayerId(int playerId);
	int GetPlayerIdByCharactyerId(int characterId);

	void SetPlayerFrameSelected(int playerId, bool status);
	int GetPlayerFrameSelected();

	// 플레이어
	bool IsPlayerJoinedGame(int characterId);

	// 맵
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

	// 플레이어 관련
	// 현재 턴에 해당하는 플레이어 'ID'를 반환한다.
	int  GetPlayerIdByTurn(int currentTurn);
	const std::string& GetCharacterPlayFaceById(int playerIdx);
	int  GetPlayerTurn(int playerId);
	int  GetCurrentPlayerId();

	void StartGame();
	
	/* 게임 진행 관련 : 실시간 점수 계산은 로직 쪽에서 하도록 한다.*/
	void UpdateGameMap();
	MO_TYPE IsConnected(IndexedPosition indexedPosition);
	void TimeOut();
    void SetPlayReady();
    void PausePlayReady();
	
	//조심해!!
	//아래의 함수들은 호출할 필요가 없다(로직 내부에서만 사용하는 함수들)
	//bool IsPossible(IndexedPosition indexedPosition);
	//bool IsClosed(IndexedPosition indexedPosition);
	
	//result scene 관련
	bool IsWinner(int idx);
	int GetElementCount (int playerIdx, MO_ITEM item);
	int GetTotalScore(int playerIdx);
	const std::string& GetCharacterResultFaceFileName(int playerIdx);

	// network 관련 함수
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

	// network::playReady 전송을 위한 함수
	void	SetAnimationDelay(int time);
	float	GetAnimationDelay() { return m_AnimationDelay; }
    void    InitAnimationDelay();

	// game data 접근 관련
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

	//캐릭터 이름이나 맵 상태 정보들은 매니저가 캐싱해서 가지고 있는 것이 좋을 듯
	//대신 그 데이터를 기반으로 무언가를 판단하는 로직은 없도록 주의(일단 인풋이 있으면 전송하고 결과값만 받는 방식 유지)

	// implement the "static node()" method manually
    //CREATE_FUNC(CGameManager);
};

