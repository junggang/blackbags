#include "GameManager.h"
#include "GameLogic.h"
//#include <cstdio>

USING_NS_CC_EXT;
using namespace rapidjson;

CGameManager* CGameManager::m_pInstance = nullptr;

CGameManager::CGameManager(void)
{
	m_IsOnlineGame = false;
	m_IsUpdated = false;
	m_Request = false;

	m_Request = nullptr;
	m_networkGameData = nullptr;

	m_TokenId = "";
	m_UserName = "";

	m_Login = false;
	m_LoginFail = false;
	m_InChannel = false;

	m_MyPlayerId = -1;
}

CGameManager::~CGameManager(void)
{
}

CGameManager* CGameManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CGameManager();
	}

	return m_pInstance;
}

void CGameManager::ReleaseInstance()
{
}

bool CGameManager::init()
{
	CGameLogic::GetInstance()->init();

	return true;
}


void CGameManager::SetPlayerName(int playerId,  const std::string& playerName )
{
	if (m_IsOnlineGame)
	{
		// 다른 유저의 이름은 서버에서 받아오고
		// 본인 이름은 shared data에 저장된 것을 사용하므로 이 함수는 사용하지 않음
	}
	else
	{
		SetUpdateFlag(CGameLogic::GetInstance()->SetPlayerName(playerId,playerName) );
	}
}


const std::string& CGameManager::GetPlayerName(int playerIdx)
{
	if (m_IsOnlineGame)
	{
		return m_networkGameData[SizeType(GD_PLAYER_LIST)][SizeType(playerIdx)][SizeType(GDP_NAME)].GetString();
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerName(playerIdx);
	}
}

int CGameManager::GetCurrentPlayerNumber()
{
	if (m_IsOnlineGame)
	{
		return m_networkGameData[SizeType(GD_PLAYER_NUMBER)].GetInt();
	}
	else
	{
		return CGameLogic::GetInstance()->GetCurrentPlayerNumber();
	}
}

//조심해!!
//이거 호출하는 함수 아닌 것 같은데
void CGameManager::SetCurrentPlayerNumber(int PlayerNumber)
{
	if (m_IsOnlineGame)
	{
		// player number는 서버가 matching thread를 통해서 결정하므로 사용되지 않음
	}
	else
	{
		SetUpdateFlag(CGameLogic::GetInstance()->SetCurrentPlayerNumber(PlayerNumber) );
	}
}

int CGameManager::GetWinnerIdx()
{
	if (m_IsOnlineGame)
	{
		//server에서 필요한 정보를 받아 온다.
		// winner idx - 동점 경우도 생각해야 함
	}
	else
	{
		return CGameLogic::GetInstance()->GetWinnerIdx();
	}
}

int CGameManager::GetElementCount(int playerIdx, MO_ITEM item)
{
	if (m_IsOnlineGame)
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
	else
	{
		return CGameLogic::GetInstance()->GetPlayerResult(playerIdx, item);
	}
}

int CGameManager::GetTotalScore(int playerIdx)
{
	if (m_IsOnlineGame)
	{
		return m_networkGameData[SizeType(GD_PLAYER_LIST)][SizeType(playerIdx)][SizeType(GDP_SCORE)].GetInt();
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerTotalScore(playerIdx);
	}
}


const std::string& CGameManager::GetCharacterResultFaceFileName(int playerIdx)
{
	if (m_IsOnlineGame)
	{
		int characterId = m_networkGameData[SizeType(GD_PLAYER_LIST)][SizeType(playerIdx)][SizeType(GDP_CHARACTER_ID)].GetInt();

		return CGameLogic::GetInstance()->GetCharacterResultImage(characterId);
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerResultImage(playerIdx);
	}
}

void CGameManager::SelectCharacter( int characterId )
{
	if (m_IsOnlineGame)
	{
		m_Request = new CCHttpRequest();

		m_Request->setUrl("localhost/select_character");
		m_Request->setRequestType(CCHttpRequest::kHttpPost);
		m_Request->setResponseCallback(m_Request, httpresponse_selector(CGameManager::OnHttpRequestCompleted) );

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
	else
	{
		SetUpdateFlag( CGameLogic::GetInstance()->SetPlayerCharacterId( characterId ) );
	}
}

bool CGameManager::isCharacterSelected( int characterId )
{
	if (m_IsOnlineGame)
	{
		// 필요한가?
		return false;
	}
	else
	{
		return CGameLogic::GetInstance()->isCharacterSelected(characterId);
	}
}

int CGameManager::GetCharacterId( int playerId )
{
	if (m_IsOnlineGame)
	{
		return m_networkGameData[SizeType(GD_PLAYER_LIST)][SizeType(playerId)][SizeType(GDP_CHARACTER_ID)].GetInt();
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerCharacterId( playerId );
	}
}

int CGameManager::GetPlayerIdByTurn( int currentTurn )
{
	if (m_IsOnlineGame)
	{
		return m_networkGameData[SizeType(GD_TURN_LIST)][SizeType(currentTurn)].GetInt();
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerIdByTurn(currentTurn);
	}
}

void CGameManager::StartGame()
{
	if (m_IsOnlineGame)
	{
		m_Request = new CCHttpRequest();

		m_Request->setUrl("localhost/settingReady");
		m_Request->setRequestType(CCHttpRequest::kHttpPost);
		m_Request->setResponseCallback(m_Request, httpresponse_selector(CGameManager::OnHttpRequestCompleted) );

		// write the post data
		std::string postData  = "tokenId=";
		postData.append(m_TokenId);

		m_Request->setRequestData(postData.c_str(), postData.length() );

		m_Request->setTag("POST settingReady");
		CCHttpClient::getInstance()->send(m_Request);
		m_Request->release();
	}
	else
	{
		SetUpdateFlag(CGameLogic::GetInstance()->StartGame() );
	}
}

void CGameManager::SetMapSize( MapSelect mapSize )
{
	if (m_IsOnlineGame)
	{
		m_Request = new CCHttpRequest();

		m_Request->setUrl("localhost/selectMap");
		m_Request->setRequestType(CCHttpRequest::kHttpPost);
		m_Request->setResponseCallback(m_Request, httpresponse_selector(CGameManager::OnHttpRequestCompleted) );

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
	else
	{
		SetUpdateFlag(CGameLogic::GetInstance()->SetSelectedMapSize( mapSize ) );
	}
}

bool CGameManager::IsEnd()
{
	if (m_IsOnlineGame)
	{
		return (m_networkGameData[SizeType(GD_CURRENT_SCENE)].GetInt() == SC_RESULT) ? true : false;
	}
	else
	{
		return CGameLogic::GetInstance()->IsEnd();
	}
}

MapSelect	CGameManager::GetSelectedMapSize()
{
	if (m_IsOnlineGame)
	{
		return static_cast<MapSelect>(m_networkGameData[SizeType(GD_MAP_ID)].GetInt() );
	}
	else
	{
		return CGameLogic::GetInstance()->GetSelectedMapSize();
	}
}

MO_TYPE CGameManager::GetMapType( IndexedPosition indexedPosition )
{
	if (m_IsOnlineGame)
	{
		return static_cast<MO_TYPE>(m_networkGameData[SizeType(GD_MAP)][SizeType(indexedPosition.m_PosI)][SizeType(indexedPosition.m_PosJ)][SizeType(GDM_TYPE)].GetInt() );
	}
	else
	{
		return CGameLogic::GetInstance()->GetMapType(indexedPosition);
	}
}

MO_OWNER CGameManager::GetMapOwner( IndexedPosition indexedPosition )
{
	if (m_IsOnlineGame)
	{
		return static_cast<MO_OWNER>(m_networkGameData[SizeType(GD_MAP)][SizeType(indexedPosition.m_PosI)][SizeType(indexedPosition.m_PosJ)][SizeType(GDM_OWNER)].GetInt() );
	}
	else
	{
		return CGameLogic::GetInstance()->GetMapOwner(indexedPosition);
	}
}

MO_ITEM CGameManager::GetItem( IndexedPosition indexedPosition )
{
	if (m_IsOnlineGame)
	{
		return static_cast<MO_ITEM>(m_networkGameData[SizeType(GD_MAP)][SizeType(indexedPosition.m_PosI)][SizeType(indexedPosition.m_PosJ)][SizeType(GDM_ITEM)].GetInt() );
	}
	else
	{
		return CGameLogic::GetInstance()->GetItem(indexedPosition);
	}
}

void CGameManager::DrawLine( IndexedPosition indexedPosition )
{
	if (m_IsOnlineGame)
	{
		m_Request = new CCHttpRequest();

		m_Request->setUrl("localhost/draw_line");
		m_Request->setRequestType(CCHttpRequest::kHttpPost);
		m_Request->setResponseCallback(m_Request, httpresponse_selector(CGameManager::OnHttpRequestCompleted) );

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
	else
	{
		SetUpdateFlag(CGameLogic::GetInstance()->EventHandle(indexedPosition) );
		CCLOG("draw line : %d, %d",indexedPosition.m_PosI,indexedPosition.m_PosJ);
	}
}

const std::string& CGameManager::GetCharacterPlayFaceById( int playerIdx )
{
	if (m_IsOnlineGame)
	{
		int characterId = m_networkGameData[SizeType(GD_PLAYER_LIST)][SizeType(playerIdx)][SizeType(GDP_CHARACTER_ID)].GetInt();

		return CGameLogic::GetInstance()->GetCharacterPlayImage(characterId);
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerPlayImage(playerIdx);
	}
}

MO_TYPE CGameManager::IsConnected(IndexedPosition indexedPosition)
{
	if (m_IsOnlineGame)
	{
		return static_cast<MO_TYPE>(m_networkGameData[SizeType(GD_MAP)][SizeType(indexedPosition.m_PosI)][SizeType(indexedPosition.m_PosJ)][SizeType(GDM_TYPE)].GetInt() );
	}
	else
	{
		return CGameLogic::GetInstance()->IsConnected(indexedPosition);
	}
}

int CGameManager::GetPlayerTurn( int playerId )
{
	if (m_IsOnlineGame)
	{
		return m_networkGameData[SizeType(GD_PLAYER_LIST)][SizeType(GDP_TURN)].GetInt();
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerTurnById(playerId);
	}
}

int CGameManager::GetCurrentPlayerId()
{
	if (m_IsOnlineGame)
	{
		int turnIdx = m_networkGameData[SizeType(GD_CURRENT_TURN_IDX)].GetInt();

		return m_networkGameData[SizeType(GD_TURN_LIST)][SizeType(turnIdx)].GetInt();
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerIdByCurrentTurn();
	}
}

int	CGameManager::GetTileAnimationTurn(IndexedPosition indexedPosition)
{
	if (m_IsOnlineGame)
	{
		m_networkGameData[SizeType(GD_MAP)][SizeType(indexedPosition.m_PosI)][SizeType(indexedPosition.m_PosJ)][SizeType(GDM_ANIMATION_TURN)].GetInt();
	}
	else
	{
		return CGameLogic::GetInstance()->GetTileAnimationTurn(indexedPosition);
	}
}

bool CGameManager::IsPlayerNumberAndMapSeleted()
{
	if (m_IsOnlineGame)
	{
		// 채널 마스터인 경우 본인을 제외하고 모든 사람이 레디하면 true
		// 마스터가 아닌 경우 자신의 레디 상태 확인해서 true / false
	}
	else
	{
		return CGameLogic::GetInstance()->isPlayerNumberAndMapSeleted();
	}
}

int CGameManager::GetPlayerNumberOfThisGame()
{
	if (m_IsOnlineGame)
	{
		// 필요한가?
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerNumberOfThisGame();
	}
}

void CGameManager::SetPlayerNumberOfThisGame( int PlayerNumber )
{
	if (m_IsOnlineGame)
	{
		// shared data에 player number flags 설정
	}
	else
	{
		CGameLogic::GetInstance()->SetPlayerNumberOfThisGame(PlayerNumber);
	}
}

void CGameManager::OnHttpRequestCompleted(cocos2d::CCNode* sender, CCHttpResponse* response)
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

			// init network game data
			if (m_networkGameData == nullptr)
			{
				m_networkGameData = new Document();
			}

			// create loginUpdate schedule

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

			// create update schedule

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

			SetUpdateFlag(true);

			// game end >>> delete the network game data
		}
	}
}

void CGameManager::Login()
{
	if (!m_IsOnlineGame)
	{
		return;
	}

	// login
	// make http request
	m_Request = new CCHttpRequest();

	m_Request->setUrl("localhost/login");
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CGameManager::OnHttpRequestCompleted) );

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