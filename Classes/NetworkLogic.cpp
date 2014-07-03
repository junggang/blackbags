#include "NetworkLogic.h"
#include "GameLogic.h"
#include <cstdio>
#include "GameManager.h"
#include <vector>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace rapidjson;

CNetworkLogic* CNetworkLogic::m_pInstance = nullptr;

CNetworkLogic::CNetworkLogic(void)
{
	m_Request = nullptr;
	m_NetworkGameData = nullptr;

	m_UserName = "";

	//m_ServerAddr = "http://10.73.43.187:8080";
	m_ServerAddr = "http://blackbags-mons.appspot.com";

	m_MyPlayerId = -1;

	m_TwoFlag = false;
	m_ThreeFlag = false;
	m_FourFlag = false;

	m_CurrentPhase = NP_NOTHING;
    m_CurrentLoginPhase = LP_WAITING;
	m_CurrentScene = SC_NOSCENE;

	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		m_PlayerNameList[i] = "";
	}
}


CNetworkLogic::~CNetworkLogic(void)
{
}

CNetworkLogic* CNetworkLogic::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CNetworkLogic();
	}

	return m_pInstance;
}

void CNetworkLogic::ReleaseInstance()
{
}

bool CNetworkLogic::Init()
{
	// init network game data
	if (m_NetworkGameData == nullptr)
	{
		m_NetworkGameData = new Document();
	}

	m_CurrentScene = SC_NETWORK_SETTING;
	GetNetworkInfo();

	return true;
}

SceneName CNetworkLogic::GetCurrentScene()
{
	return m_CurrentScene;
}

void CNetworkLogic::SetCurrentScene(SceneName scene)
{
	m_CurrentScene = scene;
}

NetworkPhase CNetworkLogic::GetCurrentNetworkPhase() 
{ 
	return m_CurrentPhase;
}

LoginPhase CNetworkLogic::GetCurrentLoginPhase()
{
    return m_CurrentLoginPhase;
}

void CNetworkLogic::GetNetworkInfo()
{
	// shared dataø° ¿˙¿Âµ» ¿Ã∏ß ∞°¡Æø¬¥Ÿ
	m_UserName.clear();
	m_UserName = CGameManager::GetInstance()->GetUsersName();

	// shared dataø° ¿˙¿Âµ» ∞‘¿” º≥¡§¿ª ∞°¡Æø¬¥Ÿ
	m_TwoFlag = CGameManager::GetInstance()->GetPlayerNumberSelection(2);
	m_ThreeFlag = CGameManager::GetInstance()->GetPlayerNumberSelection(3);
	m_FourFlag = CGameManager::GetInstance()->GetPlayerNumberSelection(4);
}

const std::string& CNetworkLogic::GetPlayerName(int playerIdx)
{
	return m_PlayerNameList[playerIdx];
}

int CNetworkLogic::GetCurrentPlayerNumber()
{
	// return (*m_NetworkGameData)[SizeType(GD_PLAYER_NUMBER)].GetInt();
    return (*m_NetworkGameData)[SizeType(GD_TURN_LIST)].Size();
}

int CNetworkLogic::GetPlayerResult(int playerIdx, MO_ITEM item)
{
	int tempIdx = 0;

	switch (item)
	{
	case ITEM_NOTHING:
		tempIdx = GDP_TILE_COUNT;
		break;
	case ITEM_GOLD:
		tempIdx = GDP_GOLD_COUNT;
		break;
	case ITEM_TRASH:
		tempIdx = GDP_TRASH_COUNT;
		break;
	default:
		break;
	}

	return (*m_NetworkGameData)[SizeType(GD_PLAYER_LIST)][SizeType(playerIdx)][SizeType(tempIdx)].GetInt();
}

int CNetworkLogic::GetPlayerTotalScore(int playerIdx)
{
	return (*m_NetworkGameData)[SizeType(GD_PLAYER_LIST)][SizeType(playerIdx)][SizeType(GDP_SCORE)].GetInt();
}

const std::string& CNetworkLogic::GetPlayerResultImage(int playerIdx)
{
	int characterId = (*m_NetworkGameData)[SizeType(GD_PLAYER_LIST)][SizeType(playerIdx)][SizeType(GDP_CHARACTER_ID)].GetInt();

	return CGameLogic::GetInstance()->GetCharacterResultImage(characterId);
}

int CNetworkLogic::GetPlayerCharacterId(int playerIdx)
{
	return (*m_NetworkGameData)[SizeType(GD_PLAYER_LIST)][SizeType(playerIdx)][SizeType(GDP_CHARACTER_ID)].GetInt();
}

int	CNetworkLogic::GetPlayerIdByTurn(int currentTurn)
{
	return (*m_NetworkGameData)[SizeType(GD_TURN_LIST)][SizeType(currentTurn)].GetInt();
}

bool CNetworkLogic::IsEnd()
{
	return ((*m_NetworkGameData)[SizeType(GD_CURRENT_SCENE)].GetInt() == SC_RESULT) ? true : false;
}

MapSelect CNetworkLogic::GetSelectedMapSize()
{
	return static_cast<MapSelect>((*m_NetworkGameData)[SizeType(GD_MAP_ID)].GetInt() );
}

MO_TYPE CNetworkLogic::GetMapType(IndexedPosition indexedPosition)
{
	return static_cast<MO_TYPE>((*m_NetworkGameData)[SizeType(GD_MAP)][SizeType(indexedPosition.m_PosI)][SizeType(indexedPosition.m_PosJ)][SizeType(GDM_TYPE)].GetInt() );
}

MO_OWNER CNetworkLogic::GetMapOwner(IndexedPosition indexedPosition)
{
	return static_cast<MO_OWNER>((*m_NetworkGameData)[SizeType(GD_MAP)][SizeType(indexedPosition.m_PosI)][SizeType(indexedPosition.m_PosJ)][SizeType(GDM_OWNER)].GetInt() );
}

MO_ITEM CNetworkLogic::GetItem(IndexedPosition indexedPosition)
{
	return static_cast<MO_ITEM>((*m_NetworkGameData)[SizeType(GD_MAP)][SizeType(indexedPosition.m_PosI)][SizeType(indexedPosition.m_PosJ)][SizeType(GDM_ITEM)].GetInt() );
}

const std::string& CNetworkLogic::GetPlayerPlayImage(int playerIdx)
{
	int characterId = (*m_NetworkGameData)[SizeType(GD_PLAYER_LIST)][SizeType(playerIdx)][SizeType(GDP_CHARACTER_ID)].GetInt();

	return CGameLogic::GetInstance()->GetCharacterPlayImage(characterId);
}

MO_TYPE CNetworkLogic::IsConnected(IndexedPosition indexedPosition)
{
	return static_cast<MO_TYPE>((*m_NetworkGameData)[SizeType(GD_MAP)][SizeType(indexedPosition.m_PosI)][SizeType(indexedPosition.m_PosJ)][SizeType(GDM_TYPE)].GetInt() );
}

int CNetworkLogic::GetPlayerTurnById(int playerId)
{
	return (*m_NetworkGameData)[SizeType(GD_PLAYER_LIST)][SizeType(playerId)][SizeType(GDP_TURN)].GetInt();
}

int CNetworkLogic::GetPlayerIdByCurrentTurn()
{
	int turnIdx = (*m_NetworkGameData)[SizeType(GD_CURRENT_TURN_IDX)].GetInt();

	return (*m_NetworkGameData)[SizeType(GD_TURN_LIST)][SizeType(turnIdx)].GetInt();
}

int CNetworkLogic::GetTileAnimationTurn(IndexedPosition indexedPosition)
{
	return (*m_NetworkGameData)[SizeType(GD_MAP)][SizeType(indexedPosition.m_PosI)][SizeType(indexedPosition.m_PosJ)][SizeType(GDM_ANIMATION_TURN)].GetInt();
}

bool CNetworkLogic::IsChannelMaster()
{
	return (*m_NetworkGameData)[SizeType(GD_PLAYER_LIST)][SizeType(m_MyPlayerId)][SizeType(GDP_MASTER_FLAG)].GetBool();
}

bool CNetworkLogic::IsReady()
{
	return (*m_NetworkGameData)[SizeType(GD_PLAYER_LIST)][SizeType(m_MyPlayerId)][SizeType(GDP_READY)].GetBool();
}

bool CNetworkLogic::IsReady(int playerId)
{
	return (*m_NetworkGameData)[SizeType(GD_PLAYER_LIST)][SizeType(playerId)][SizeType(GDP_READY)].GetBool();
}

bool CNetworkLogic::IsAllReady()
{
	int readyCount = 0;

	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		// πÊ¿Â¿Œ æ∆¥—µ• ∑πµ¿Œ ªÛ≈¬¿Ã∏È 
		if ( !(*m_NetworkGameData)[SizeType(GD_PLAYER_LIST)][SizeType(i)][SizeType(GDP_MASTER_FLAG)].GetBool() 
			&& (*m_NetworkGameData)[SizeType(GD_PLAYER_LIST)][SizeType(i)][SizeType(GDP_READY)].GetBool() )
		{
			// ƒ´øÓ∆Æ ¡ı∞°
			++readyCount;
		}
	}

	return (readyCount == GetCurrentPlayerNumber() - 1);
}

bool CNetworkLogic::GetCurrentTimerStatus()
{
	return (*m_NetworkGameData)[SizeType(GD_WAITING_READY)].GetBool();
}

void CNetworkLogic::Login()
{
	// login
	// make http request
	m_Request = new CCHttpRequest();

	// ø‰√ª ∫∏≥æ µ•¿Ã≈Õ∏¶ √÷Ω≈ ªÛ≈¬∑Œ æ˜µ•¿Ã∆Æ
	GetNetworkInfo();

	std::string url = m_ServerAddr;
	url.append("/login");

	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );

	// write cookie
    std::vector<std::string> headers;
    std::string cookieHeader = "Cookie: ACSID=";
    cookieHeader.append(CGameManager::GetInstance()->GetTokenId());
    headers.push_back(cookieHeader);
	m_Request->setHeaders(headers);
	
	// write the post data
	std::string postData = "two=";
	postData.append( (m_TwoFlag) ? "1" : "0" );

	postData.append("&three=");
	postData.append( (m_ThreeFlag) ? "1" : "0" );

	postData.append("&four=");
	postData.append( (m_FourFlag) ? "1" : "0" );

	m_Request->setRequestData(postData.c_str(), postData.length() );

	m_Request->setTag("POST login");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}

void CNetworkLogic::Logout()
{
    CGameManager::GetInstance()->SetOnlineMode(false);
    
	// make http request
	m_Request = new CCHttpRequest();

	// ø‰√ª ∫∏≥æ µ•¿Ã≈Õ∏¶ √÷Ω≈ ªÛ≈¬∑Œ æ˜µ•¿Ã∆Æ
	GetNetworkInfo();

	std::string url = m_ServerAddr;
	url.append("/logout");

	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );

	// write cookie
    std::vector<std::string> headers;
    std::string cookieHeader = "Cookie: ACSID=";
    cookieHeader.append(CGameManager::GetInstance()->GetTokenId());
    headers.push_back(cookieHeader);
	m_Request->setHeaders(headers);

	m_Request->setTag("POST logout");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}

void CNetworkLogic::GameEnd()
{
    // make http request
	m_Request = new CCHttpRequest();
    
	// ø‰√ª ∫∏≥æ µ•¿Ã≈Õ∏¶ √÷Ω≈ ªÛ≈¬∑Œ æ˜µ•¿Ã∆Æ
	GetNetworkInfo();
    
	std::string url = m_ServerAddr;
	url.append("/logout");
    
	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );
    
	// write cookie
    std::vector<std::string> headers;
    std::string cookieHeader = "Cookie: ACSID=";
    cookieHeader.append(CGameManager::GetInstance()->GetTokenId());
    headers.push_back(cookieHeader);
	m_Request->setHeaders(headers);
    
	m_Request->setTag("POST logout");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}

void CNetworkLogic::getInitializedGameData()
{
	// make http request
	m_Request = new CCHttpRequest();

	std::string url = m_ServerAddr;
	url.append("/get_initialized_gamedata");

	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );

	// write cookie
    std::vector<std::string> headers;
    std::string cookieHeader = "Cookie: ACSID=";
    cookieHeader.append(CGameManager::GetInstance()->GetTokenId());
    headers.push_back(cookieHeader);
	m_Request->setHeaders(headers);

	m_Request->setTag("POST getInitializedGameData");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}

void CNetworkLogic::SelectCharacter(int characterId)
{
	m_Request = new CCHttpRequest();
	
	std::string url = m_ServerAddr;
	url.append("/select_character");

	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );

    // write cookie
    std::vector<std::string> headers;
    std::string cookieHeader = "Cookie: ACSID=";
    cookieHeader.append(CGameManager::GetInstance()->GetTokenId());
    headers.push_back(cookieHeader);
	m_Request->setHeaders(headers);
    
	// write the post data
	std::string postData = "characterId=";
	postData.append(std::to_string(characterId) );

	m_Request->setRequestData(postData.c_str(), postData.length() );

	m_Request->setTag("POST selectCharacter");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}

void CNetworkLogic::SetMapSize(MapSelect mapSize)
{
	m_Request = new CCHttpRequest();
	
	std::string url = m_ServerAddr;
	url.append("/selectMap");

	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );

    // write cookie
    std::vector<std::string> headers;
    std::string cookieHeader = "Cookie: ACSID=";
    cookieHeader.append(CGameManager::GetInstance()->GetTokenId());
    headers.push_back(cookieHeader);
	m_Request->setHeaders(headers);
    
	// write the post data
	std::string postData = "mapId=";
	postData.append(std::to_string(mapSize) );

	m_Request->setRequestData(postData.c_str(), postData.length() );

	m_Request->setTag("POST setMapSize");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}

void CNetworkLogic::DrawLine(IndexedPosition indexedPosition)
{
	m_Request = new CCHttpRequest();
	
	std::string url = m_ServerAddr;
	url.append("/draw_line");

	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );

    // write cookie
    std::vector<std::string> headers;
    std::string cookieHeader = "Cookie: ACSID=";
    cookieHeader.append(CGameManager::GetInstance()->GetTokenId());
    headers.push_back(cookieHeader);
	m_Request->setHeaders(headers);
    
	// write the post data
	std::string postData = "posI=";
	postData.append(std::to_string(indexedPosition.m_PosI) );

	postData.append("&posJ=");
	postData.append(std::to_string(indexedPosition.m_PosJ) );
    
    CCLOG("%d / %d", indexedPosition.m_PosI, indexedPosition.m_PosJ);

	m_Request->setRequestData(postData.c_str(), postData.length() );

	m_Request->setTag("POST drawLine");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}

void CNetworkLogic::JoinUpdate(float dt)
{
	m_Request = new CCHttpRequest();
	
	std::string url = m_ServerAddr;
	url.append("/join_update");

	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );

	// write cookie
    std::vector<std::string> headers;
    std::string cookieHeader = "Cookie: ACSID=";
    cookieHeader.append(CGameManager::GetInstance()->GetTokenId());
    headers.push_back(cookieHeader);
	m_Request->setHeaders(headers);

	m_Request->setTag("POST joinUpdate");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}

void CNetworkLogic::PlayUpdate(float dt)
{
	m_Request = new CCHttpRequest();
	
	std::string url = m_ServerAddr;
	url.append("/play_update");

	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );

	// write cookie
    std::vector<std::string> headers;
    std::string cookieHeader = "Cookie: ACSID=";
    cookieHeader.append(CGameManager::GetInstance()->GetTokenId());
    headers.push_back(cookieHeader);
	m_Request->setHeaders(headers);

	m_Request->setTag("POST playUpdate");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}

void CNetworkLogic::SettingReady()
{
	m_Request = new CCHttpRequest();
	
	std::string url = m_ServerAddr;
	url.append("/setting_ready");

	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );

	// write cookie
    std::vector<std::string> headers;
    std::string cookieHeader = "Cookie: ACSID=";
    cookieHeader.append(CGameManager::GetInstance()->GetTokenId());
    headers.push_back(cookieHeader);
	m_Request->setHeaders(headers);

	m_Request->setTag("POST settingReady");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}

void CNetworkLogic::PlayReady()
{
	m_Request = new CCHttpRequest();
	
	std::string url = m_ServerAddr;
	url.append("/play_ready");

	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );

	// write cookie
    std::vector<std::string> headers;
    std::string cookieHeader = "Cookie: ACSID=";
    cookieHeader.append(CGameManager::GetInstance()->GetTokenId());
    headers.push_back(cookieHeader);
	m_Request->setHeaders(headers);

	m_Request->setTag("POST playReady");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}

void CNetworkLogic::AuthenticationCheck()
{
    CGameManager::GetInstance()->SetCurrentLoginPhase(LP_WAITING);
    
    m_Request = new CCHttpRequest();
	
	std::string url = m_ServerAddr;
	url.append("/authentication_check");
    
	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpGet);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );
	
    // write cookie
    std::vector<std::string> headers;
    std::string cookieHeader = "Cookie: ACSID=";
    cookieHeader.append(CGameManager::GetInstance()->GetTokenId());
    headers.push_back(cookieHeader);
	m_Request->setHeaders(headers);
    
	m_Request->setTag("GET authenticationCheck");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}

void CNetworkLogic::GetGoogleNick()
{
    // CGameManager::GetInstance()->SetCurrentLoginPhase(LP_WAITING);
    
    m_Request = new CCHttpRequest();
	
	std::string url = m_ServerAddr;
	url.append("/get_google_nick");
    
	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpGet);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );
	
    // write cookie
    std::vector<std::string> headers;
    std::string cookieHeader = "Cookie: ACSID=";
    cookieHeader.append(CGameManager::GetInstance()->GetTokenId());
    headers.push_back(cookieHeader);
	m_Request->setHeaders(headers);
    
	m_Request->setTag("GET googleNick");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}

void CNetworkLogic::OnHttpRequestCompleted(cocos2d::CCNode* sender, CCHttpResponse* response)
{
	if (!response)
	{
		return;
	}
    
    if (!CGameManager::GetInstance()->IsOnlineMode()
        && strcmp(response->getHttpRequest()->getTag(), "GET googleNick") != 0)
    {
        return;
    }
    
    rapidjson::Document* gameData = CNetworkLogic::GetInstance()->GetGameData();

	//int statusCode = response->getResponseCode();
	
    if (!response->isSucceed() )
	{
		CCLOG("response failed");
		CCLOG("error buffer: %s", response->getErrorBuffer() );
		return;
	}

	// dump data
	std::vector<char> *buffer = response->getResponseData();
	std::stringstream streamData;

	for (unsigned int i = 0; i < buffer->size(); ++i)
	{
		streamData << (*buffer)[i];
	}

	std::string stringData = streamData.str();
    
    // CCLog(stringData.c_str());
    
    // disconnected
    if (strcmp(stringData.c_str(), "disconnected") == 0)
    {
        CGameManager::GetInstance()->SetConnectionStatus(false);
        CGameManager::GetInstance()->SetUpdateFlag(true);
    }

	if (strcmp(response->getHttpRequest()->getTag(), "POST login") == 0)
	{
		if (strcmp(stringData.c_str(), "login") == 0)
		{
			// login next phase
			CNetworkLogic::GetInstance()->SetCurrentNetworkPhase(NP_WAITING_CHANNEL_ID);
			CGameManager::GetInstance()->SetUpdateFlag(true);
		}
		else
		{
			// return to main menu
			CNetworkLogic::GetInstance()->SetCurrentNetworkPhase(NP_NOTHING);
			CGameManager::GetInstance()->SetUpdateFlag(true);
		}
	}
	else if (strcmp(response->getHttpRequest()->getTag(), "POST logout") == 0)
	{
		if (strcmp(stringData.c_str(), "logout") == 0)
		{
			// logout«“ ∂ß networkLogicø°º≠ √≥∏Æ «“ ¿œ ¿÷¿∏∏È √ﬂ∞°
		}
	}
	else if (strcmp(response->getHttpRequest()->getTag(), "POST joinUpdate") == 0)
	{
        CCLog("%s", stringData.c_str());
        
        if (strcmp(stringData.c_str(), "channel not found") == 0)
		{
			// 대기열에 있다가 타임 아웃된 경우
            // 연결 끊고 타임 아웃 플래그 설정하고, 업데이트 할 수 있도록 플래그 변경
            CGameManager::GetInstance()->SetConnectionStatus(false);
            CGameManager::GetInstance()->SetFindingChannelTimeOut(true);
            CGameManager::GetInstance()->SetUpdateFlag(true);
		}
        else
        {
            CNetworkLogic::GetInstance()->SetMyPlayerId(atoi(stringData.c_str() ) );

            if (CNetworkLogic::GetInstance()->GetMyPlayerId() != -1)
            {
                // send getInitializedGameData request
                CNetworkLogic::GetInstance()->getInitializedGameData();
            }
        }
	}
	else if (strcmp(response->getHttpRequest()->getTag(), "POST getInitializedGameData") == 0)
	{
		//CNetworkLogic::GetInstance()->m_NetworkGameData->Clear();
		gameData->Parse<0>(stringData.c_str() );

		// name check
		for (int i = 0; i < MAX_PLAYER_NUM; ++i)
		{
			CNetworkLogic::GetInstance()->GetPlayerName( (*gameData)[SizeType(GD_PLAYER_LIST)][SizeType(i)][SizeType(GDP_NAME)].GetString(), i);
			CNetworkLogic::GetInstance()->SetCurrentScene(static_cast<SceneName>( (*gameData)[SizeType(GD_CURRENT_SCENE)].GetInt() ) );
		}
		
		CNetworkLogic::GetInstance()->SetCurrentNetworkPhase(NP_GAME_SETTING);
		CGameManager::GetInstance()->SetUpdateFlag(true);
	}
    else if (strcmp(response->getHttpRequest()->getTag(), "GET authenticationCheck") == 0)
	{
        if (strcmp(stringData.c_str(), "ok") == 0)
        {
            // CCLOG("OK!");
            CGameManager::GetInstance()->SetCurrentLoginPhase(LP_OK);
		}
        else
        {
            // CCLOG("failed");
            CGameManager::GetInstance()->SetCurrentLoginPhase(LP_FAIL);
        }
        // change flag status
	}
    else if (strcmp(response->getHttpRequest()->getTag(), "GET googleNick") == 0)
	{
        CGameManager::GetInstance()->SetUsersName(stringData);
        CGameManager::GetInstance()->SetUpdateFlag(true);
	}
	else
	{
		// updateµ» ≥ªøÎ æ¯¿∏¥œ±Ó ±◊≥… ¡æ∑·
		if (strcmp(stringData.c_str(), "not updated") == 0)
		{
			return;
		}
		else if(strcmp(stringData.c_str(), "disconnected") == 0)
		{
			// ¡¢º” ¡æ∑·¿« ∞ÊøÏø° ¥Î«— √≥∏Æ

			CGameManager::GetInstance()->SetUpdateFlag(true);
		}
		else if(strcmp(stringData.c_str(), "ready") == 0)
		{
			// ∑πµ º∫∞¯«œ∏È «“ ¿œ 
			// ¡ˆ±›¿∫ æ¯¿Ω
		}
		else
		{
			// gameDataø° ¿÷¥¬ ¿⁄∑·∏¶ ∏≈¥œ¿˙∞° ∞°¡¯ ¿⁄∑·ø° æ˜µ•¿Ã∆Æ«ÿ¡÷¿⁄
			if (m_NetworkGameData != nullptr)
			{
				//CNetworkLogic::GetInstance()->m_NetworkGameData->Clear();
				gameData->Parse<0>(stringData.c_str() );
				CNetworkLogic::GetInstance()->SetCurrentScene(static_cast<SceneName>( (*gameData)[SizeType(GD_CURRENT_SCENE)].GetInt() ) );
			}

			CGameManager::GetInstance()->SetUpdateFlag(true);
		}
	}
}