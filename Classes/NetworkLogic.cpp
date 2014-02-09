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

	m_Login = false;
	m_LoginFail = false;
	m_InChannel = false;

	m_MyPlayerId = -1;
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

bool CNetworkLogic::init()
{
	return true;
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

	m_Request->setUrl("localhost/login");
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

	m_Request->setUrl("localhost/select_character");
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

	m_Request->setUrl("localhost/selectMap");
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

	m_Request->setUrl("localhost/draw_line");
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

	m_Request->setUrl("localhost/join_update");
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

	m_Request->setUrl("localhost/play_update");
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

	m_Request->setUrl("localhost/settingReady");
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

	m_Request->setUrl("localhost/play_ready");
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
		if (i != 0)
		{
			streamData << ",";
			streamData << (*buffer)[i];
		}
	}

	std::string stringData = streamData.str();

	if (strcmp(response->getHttpRequest()->getTag(), "POST login") == 0)
	{
		if (strcmp(stringData.c_str(), "login") == 0)
		{
			// login 성공이므로 플래그 설정
			m_Login = true;
			CGameManager::GetInstance()->SetUpdateFlag(true);

			// init network game data
			if (m_networkGameData == nullptr)
			{
				m_networkGameData = new Document();
			}

			// create loginUpdate schedule
			this->schedule(schedule_selector(CNetworkLogic::JoinUpdate), 10.0f);
		}
		else
		{
			m_LoginFail = true;
		}
	}
	else if (strcmp(response->getHttpRequest()->getTag(), "POST joinUpdate") == 0)
	{
		m_MyPlayerId = atoi(stringData.c_str());

		if (m_MyPlayerId != -1)
		{
			m_InChannel = true;
			CGameManager::GetInstance()->SetUpdateFlag(true);

			// create update schedule
			this->unschedule(schedule_selector(CNetworkLogic::JoinUpdate) );
			this->schedule(schedule_selector(CNetworkLogic::PlayUpdate), 10.0f);
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
			this->unschedule(schedule_selector(CNetworkLogic::PlayUpdate) );
		}
	}
}
