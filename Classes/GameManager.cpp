#include "GameManager.h"
#include "GameLogic.h"
#include "rapidjson\document.h"

USING_NS_CC_EXT;

CGameManager* CGameManager::m_pInstance = nullptr;

CGameManager::CGameManager(void)
{
	m_IsOnlineGame = false;
	m_IsUpdated = false;
	m_Request = false;

	m_Request = nullptr;
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


	// make data repository
	// json 뭐 만든다 치고...

	return true;
}


void CGameManager::SetPlayerName(int playerId,  const std::string& playerName )
{
	if (m_IsOnlineGame)
	{
		//온라인인 경우
		return;
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
		//server에서 필요한 정보를 받아 온다.
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerName(playerIdx);
	}
}

int CGameManager::GetPlayerNumber()
{
	if (m_IsOnlineGame)
	{
		//server에서 필요한 정보를 받아 온다.
	}
	else
	{
		return CGameLogic::GetInstance()->GetplayerNumber();
	}
}

//조심해!!
//이거 호출하는 함수 아닌 것 같은데
void CGameManager::SetPlayerNumber(int PlayerNumber)
{
	if (m_IsOnlineGame)
	{
		//server로 패킷을 보낸다.
	}
	else
	{
		SetUpdateFlag(CGameLogic::GetInstance()->SetPlayerNumber(PlayerNumber) );
	}
}

int CGameManager::GetWinnerIdx()
{
	if (m_IsOnlineGame)
	{
		//server에서 필요한 정보를 받아 온다.
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
		//server에서 필요한 정보를 받아 온다.
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
		//server에서 필요한 정보를 받아 온다.
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
		//server에서 필요한 정보를 받아 온다.
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
		//온라인
		return;
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
		//온라인
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
		//온라인
		return -1;
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

	}
	else
	{
		return CGameLogic::GetInstance()->GetTileAnimationTurn(indexedPosition);
	}
}

void CGameManager::onHttpRequestCompleted(cocos2d::CCNode* sender, CCHttpResponse* response)
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
		// 성공 / 실패 확인 가능
		// 확인해서 만약 성공이면 네트웍 대기 화면 보여주고
		// 실패이면 실패 메시지 표시하고 확인 누르면 메인으로 돌아가게
		// buffer ~~~
	}
	else if (strcmp(response->getHttpRequest()->getTag(), "POST loginUpdate") == 0)
	{
		// 수신한 데이터가 -1이면 계속 대기 >>> return
		// 아니면 해당 숫자를 내 아이디로 설정
		// 세팅씬 호출하고 update 주기적으로 실행되게 설정
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
			rapidjson::Document gameData;
			gameData.Parse<0>(stringData.c_str() );

			// gameData에 있는 자료를 매니저가 가진 자료에 업데이트해주자
		}
	}
}

void CGameManager::SetOnlineMode(bool flag) 
{ 
	m_IsOnlineGame = flag;

	// login
	// make http request
	m_Request = new CCHttpRequest();

	m_Request->setUrl("localhost/login");
	m_Request->setRequestType(CCHttpRequest::kHttpPost);
	m_Request->setResponseCallback(m_Request, httpresponse_selector(CGameManager::onHttpRequestCompleted) );

	// write the post data
	const char* postData = "tokenId=tempId&name=tempName&two=1&three=1&four=1";
	m_Request->setRequestData(postData, strlen(postData));

	m_Request->setTag("POST login");
	CCHttpClient::getInstance()->send(m_Request);
	m_Request->release();
}