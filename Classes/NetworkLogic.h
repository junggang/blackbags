#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "rapidjson/document.h"
#include "config.h"
#include <array>

class CNetworkLogic
{
public:
	CNetworkLogic(void);
	~CNetworkLogic(void);

	static CNetworkLogic*	GetInstance();
	static void				ReleaseInstance();

	bool Init();

	void SetCurrentNetworkPhase(NetworkPhase phase) { m_CurrentPhase = phase; }
	NetworkPhase GetCurrentNetworkPhase();

	SceneName			GetCurrentScene();
	const std::string&	GetPlayerName(int playerIdx);
	void				GetPlayerName(std::string name, int playerIdx) { m_PlayerNameList[playerIdx] = name; }
	int					GetMyPlayerId() { return m_MyPlayerId; }
	int					GetCurrentPlayerNumber();
	int					GetPlayerResult(int playerIdx, MO_ITEM item);
	int					GetPlayerTotalScore(int playerIdx);
	const std::string&	GetPlayerResultImage(int playerIdx);
	int					GetPlayerCharacterId(int playerIdx);
	int					GetPlayerIdByTurn(int currentTurn);
	bool				IsEnd();
	MapSelect			GetSelectedMapSize();
	MO_TYPE				GetMapType(IndexedPosition indexedPosition);
	MO_OWNER			GetMapOwner(IndexedPosition indexedPosition);
	MO_ITEM				GetItem(IndexedPosition indexedPosition);
	const std::string&	GetPlayerPlayImage(int playerIdx);
	MO_TYPE				IsConnected(IndexedPosition indexedPosition);
	int					GetPlayerTurnById(int playerId);
	int					GetPlayerIdByCurrentTurn();
	int					GetTileAnimationTurn(IndexedPosition indexedPosition);

	// 내가 방장?
	bool IsChannelMaster(); 
	// 본인이 레디?
	bool IsReady();
	// 나머지 다 레디?
	bool IsAllReady();

	// request functions
	void Login();
	void Logout();
	void SelectCharacter(int characterId);
	void SetMapSize(MapSelect mapSize);
	void DrawLine(IndexedPosition indexedPosition);

	void JoinUpdate(float dt);
	void PlayUpdate(float dt);
	void getInitializedGameData();
	void SettingReady();
	void PlayReady();

	void OnHttpRequestCompleted(cocos2d::CCNode* sender, cocos2d::extension::CCHttpResponse* response);
	
	rapidjson::Document* GetGameData() { return m_NetworkGameData; }

private:
	void GetNetworkInfo();

	static CNetworkLogic*	m_pInstance; //singleton instance
	
	// network game data
	rapidjson::Document*	m_NetworkGameData;

	std::string				m_ServerAddr;
	
	cocos2d::extension::CCHttpRequest*			m_Request;

	NetworkPhase			m_CurrentPhase;

	int						m_MyPlayerId;
	
	std::string				m_TokenId;
	std::string				m_UserName;

	bool					m_TwoFlag;
	bool					m_ThreeFlag;
	bool					m_FourFlag;

	std::array<std::string, MAX_PLAYER_NUM> m_PlayerNameList;
};

