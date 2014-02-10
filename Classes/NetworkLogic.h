#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "rapidjson\document.h"
#include "config.h"

class CNetworkLogic : public cocos2d::CCNode
{
public:
	CNetworkLogic(void);
	~CNetworkLogic(void);

	static CNetworkLogic*	GetInstance();
	static void				ReleaseInstance();

	bool Init();

	bool IsLogin()				{ return m_Login; }
	bool IsLoginFail()			{ return m_LoginFail; }
	bool IsInChannel()			{ return m_InChannel; }

	std::string			GetPlayerName(int playerIdx);
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

	// request functions
	void Login();
	void SelectCharacter(int characterId);
	void SetMapSize(MapSelect mapSize);
	void DrawLine(IndexedPosition indexedPosition);

	void JoinUpdate(float dt);
	void PlayUpdate();
	void SettingReady();
	void PlayReady();

	void OnHttpRequestCompleted(cocos2d::CCNode* sender, cocos2d::extension::CCHttpResponse* response);

private:
	static CNetworkLogic*	m_pInstance; //singleton instance
	
	// network game data
	cocos2d::extension::CCHttpRequest*			m_Request;

	bool					m_Login;
	bool					m_LoginFail;
	bool					m_InChannel;

	int						m_MyPlayerId;
	
	std::string				m_TokenId;
	std::string				m_UserName;

	bool					m_TwoFlag;
	bool					m_ThreeFlag;
	bool					m_FourFlag;

	rapidjson::Document*	m_networkGameData;
};

