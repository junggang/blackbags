#include "NetworkLogic.h"
#include "GameLogic.h"
#include <cstdio>
#include "GameManager.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace rapidjson;

CNetworkLogic* CNetworkLogic::m_pInstance = nullptr;

CNetworkLogic::CNetworkLogic(void)
{
	m_Request = nullptr;
	m_networkGameData = nullptr;

	m_TokenId = "";
	m_UserName = "";

	m_ServerAddr = "http://10.73.43.191:5000";

	m_MyPlayerId = -1;

	m_TwoFlag = false;
	m_ThreeFlag = false;
	m_FourFlag = false;

	m_CurrentPhase = NP_NOTHING;
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
	if ( !CCNode::init() )
	{
		return false;
	}

	// init network game data
	if (m_networkGameData == nullptr)
	{
		m_networkGameData = new Document();
	}
	else
	{
		m_networkGameData->Clear();
	}

	GetNetworkInfo();

	return true;
}

void CNetworkLogic::GetNetworkInfo()
{
	// facebook token 값 받아 온다
	m_TokenId.clear();
	m_TokenId = CGameManager::GetInstance()->GetTokenId();

	// shared data에 저장된 이름 가져온다
	m_UserName.clear();
	m_UserName = CGameManager::GetInstance()->GetUsersName();

	// shared data에 저장된 게임 설정을 가져온다
	m_TwoFlag = CGameManager::GetInstance()->GetPlayerNumberSelection(2);
	m_ThreeFlag = CGameManager::GetInstance()->GetPlayerNumberSelection(3);
	m_FourFlag = CGameManager::GetInstance()->GetPlayerNumberSelection(4);
}

std::string CNetworkLogic::GetPlayerName(int playerIdx)
{
	return m_networkGameData[SizeType(GD_PLAYER_LIST)][SizeType(playerIdx)][SizeType(GDP_NAME)].GetString();
}

int CNetworkLogic::GetCurrentPlayerNumber()
{
	return m_networkGameData[SizeType(GD_PLAYER_NUMBER)].GetInt();
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

	return m_networkGameData[SizeType(GD_PLAYER_LIST)][SizeType(playerIdx)][SizeType(tempIdx)].GetInt();
}

int CNetworkLogic::GetPlayerTotalScore(int playerIdx)
{
	return m_networkGameData[SizeType(GD_PLAYER_LIST)][SizeType(playerIdx)][SizeType(GDP_SCORE)].GetInt();
}

const std::string& CNetworkLogic::GetPlayerResultImage(int playerIdx)
{
	int characterId = m_networkGameData[SizeType(GD_PLAYER_LIST)][SizeType(playerIdx)][SizeType(GDP_CHARACTER_ID)].GetInt();

	return CGameLogic::GetInstance()->GetCharacterResultImage(characterId);
}

int CNetworkLogic::GetPlayerCharacterId(int playerIdx)
{
	return m_networkGameData[SizeType(GD_PLAYER_LIST)][SizeType(playerIdx)][SizeType(GDP_CHARACTER_ID)].GetInt();
}

int	CNetworkLogic::GetPlayerIdByTurn(int currentTurn)
{
	return m_networkGameData[SizeType(GD_TURN_LIST)][SizeType(currentTurn)].GetInt();
}

bool CNetworkLogic::IsEnd()
{
	return (m_networkGameData[SizeType(GD_CURRENT_SCENE)].GetInt() == SC_RESULT) ? true : false;
}

MapSelect CNetworkLogic::GetSelectedMapSize()
{
	return static_cast<MapSelect>(m_networkGameData[SizeType(GD_MAP_ID)].GetInt() );
}

MO_TYPE CNetworkLogic::GetMapType(IndexedPosition indexedPosition)
{
	return static_cast<MO_TYPE>(m_networkGameData[SizeType(GD_MAP)][SizeType(indexedPosition.m_PosI)][SizeType(indexedPosition.m_PosJ)][SizeType(GDM_TYPE)].GetInt() );
}

MO_OWNER CNetworkLogic::GetMapOwner(IndexedPosition indexedPosition)
{
	return static_cast<MO_OWNER>(m_networkGameData[SizeType(GD_MAP)][SizeType(indexedPosition.m_PosI)][SizeType(indexedPosition.m_PosJ)][SizeType(GDM_OWNER)].GetInt() );
}

MO_ITEM CNetworkLogic::GetItem(IndexedPosition indexedPosition)
{
	return static_cast<MO_ITEM>(m_networkGameData[SizeType(GD_MAP)][SizeType(indexedPosition.m_PosI)][SizeType(indexedPosition.m_PosJ)][SizeType(GDM_ITEM)].GetInt() );
}

const std::string& CNetworkLogic::GetPlayerPlayImage(int playerIdx)
{
	int characterId = m_networkGameData[SizeType(GD_PLAYER_LIST)][SizeType(playerIdx)][SizeType(GDP_CHARACTER_ID)].GetInt();

	return CGameLogic::GetInstance()->GetCharacterPlayImage(characterId);
}

MO_TYPE CNetworkLogic::IsConnected(IndexedPosition indexedPosition)
{
	return static_cast<MO_TYPE>(m_networkGameData[SizeType(GD_MAP)][SizeType(indexedPosition.m_PosI)][SizeType(indexedPosition.m_PosJ)][SizeType(GDM_TYPE)].GetInt() );
}

int CNetworkLogic::GetPlayerTurnById(int playerId)
{
	return m_networkGameData[SizeType(GD_PLAYER_LIST)][SizeType(GDP_TURN)].GetInt();
}

int CNetworkLogic::GetPlayerIdByCurrentTurn()
{
	int turnIdx = m_networkGameData[SizeType(GD_CURRENT_TURN_IDX)].GetInt();

	return m_networkGameData[SizeType(GD_TURN_LIST)][SizeType(turnIdx)].GetInt();
}

int CNetworkLogic::GetTileAnimationTurn(IndexedPosition indexedPosition)
{
	return m_networkGameData[SizeType(GD_MAP)][SizeType(indexedPosition.m_PosI)][SizeType(indexedPosition.m_PosJ)][SizeType(GDM_ANIMATION_TURN)].GetInt();
}

void CNetworkLogic::Login()
{
	// login
	// make http request
	m_Request = new CCHttpRequest();

	// 요청 보낼 데이터를 최신 상태로 업데이트
	GetNetworkInfo();

	std::string url = m_ServerAddr;
	url.append("/login");

	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );

	// write the post data
	// 조심해!!
	// shared data 만들고 나서 수정할 것
	std::string postData  = "tokenId=";
	postData.append(m_TokenId);

	postData.append("&name=");
	postData.append(m_UserName);
	
	postData.append("&two=");
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

void CNetworkLogic::SelectCharacter(int characterId)
{
	m_Request = new CCHttpRequest();
	
	std::string url = m_ServerAddr;
	url.append("/select_character");

	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );

	// write the post data
	std::string postData  = "tokenId=";
	postData.append(m_TokenId);

	postData.append("&characterId=");
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

	// write the post data
	std::string postData  = "tokenId=";
	postData.append(m_TokenId);

	postData.append("&mapId=");
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

	// write the post data
	std::string postData  = "tokenId=";
	postData.append(m_TokenId);

	postData.append("&posI=");
	postData.append(std::to_string(indexedPosition.m_PosI) );

	postData.append("&posJ=");
	postData.append(std::to_string(indexedPosition.m_PosJ) );

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

	// write the post data
	std::string postData  = "tokenId=";
	postData.append(m_TokenId);

	m_Request->setRequestData(postData.c_str(), postData.length() );

	m_Request->setTag("POST joinUpdate");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}

void CNetworkLogic::PlayUpdate()
{
	m_Request = new CCHttpRequest();
	
	std::string url = m_ServerAddr;
	url.append("/play_update");

	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );

	// write the post data
	std::string postData  = "tokenId=";
	postData.append(m_TokenId);

	m_Request->setRequestData(postData.c_str(), postData.length() );

	m_Request->setTag("POST playUpdate");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}

void CNetworkLogic::SettingReady()
{
	m_Request = new CCHttpRequest();
	
	std::string url = m_ServerAddr;
	url.append("/settingReady");

	m_Request->setUrl(url.c_str() );
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CNetworkLogic::OnHttpRequestCompleted) );

	// write the post data
	std::string postData  = "tokenId=";
	postData.append(m_TokenId);

	m_Request->setRequestData(postData.c_str(), postData.length() );

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

	// write the post data
	std::string postData  = "tokenId=";
	postData.append(m_TokenId);

	m_Request->setRequestData(postData.c_str(), postData.length() );

	m_Request->setTag("POST playReady");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}

void CNetworkLogic::OnHttpRequestCompleted(cocos2d::CCNode* sender, CCHttpResponse* response)
{
	if (!response)
	{
		return;
	}

	int statusCode = response->getResponseCode();
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

	if (strcmp(response->getHttpRequest()->getTag(), "POST login") == 0)
	{
		if (strcmp(stringData.c_str(), "login") == 0)
		{
			// login next phase
			m_CurrentPhase = NP_WAITING_CHANNEL_ID;
			CGameManager::GetInstance()->SetUpdateFlag(true);

			// create loginUpdate schedule
			StartJoinUpdate();
		}
		else
		{
			// return to main menu
			m_CurrentPhase = NP_NOTHING;
			CGameManager::GetInstance()->SetUpdateFlag(true);
		}
	}
	else if (strcmp(response->getHttpRequest()->getTag(), "POST joinUpdate") == 0)
	{
		m_MyPlayerId = atoi(stringData.c_str());

		if (m_MyPlayerId != -1)
		{
			m_CurrentPhase = NP_GAME_SETTING;
			CGameManager::GetInstance()->SetUpdateFlag(true);

			// create update schedule
			StopJoinUpdate();
			StartPlayUpdate();
		}
	}
	else
	{
		// update된 내용 없으니까 그냥 종료
		if (strcmp(stringData.c_str(), "not updated") == 0)
		{
			return;
		}
		else
		{
			// gameData에 있는 자료를 매니저가 가진 자료에 업데이트해주자
			if (m_networkGameData != nullptr)
			{
				m_networkGameData->Clear();
				m_networkGameData->Parse<0>(stringData.c_str() );
			}

			CGameManager::GetInstance()->SetUpdateFlag(true);

			// game end >>> delete the network game data
			StopPlayUpdate();
		}
	}
}

void CNetworkLogic::StartJoinUpdate()
{
	m_pInstance->schedule(schedule_selector(CNetworkLogic::JoinUpdate), 10.0f);
}

void CNetworkLogic::StopJoinUpdate()
{
	m_pInstance->unschedule(schedule_selector(CNetworkLogic::JoinUpdate) );
}

void CNetworkLogic::StartPlayUpdate()
{
	m_pInstance->schedule(schedule_selector(CNetworkLogic::PlayUpdate), 10.0f);
}

void CNetworkLogic::StopPlayUpdate()
{
	m_pInstance->unschedule(schedule_selector(CNetworkLogic::PlayUpdate) );
}