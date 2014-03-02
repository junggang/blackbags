#include "GameManager.h"
#include "GameLogic.h"
#include "NetworkLogic.h"

CGameManager* CGameManager::m_pInstance = nullptr;

CGameManager::CGameManager(void)
{
	m_IsOnlineGame = false;
	m_IsUpdated = false;
	m_GameData = nullptr;
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
	m_GameData = cocos2d::CCUserDefault::sharedUserDefault();

	// 만약 현재 저장 된 게임데이터가 없으면 초기값으로 설정해서 생성한다.
	if (!m_GameData->getBoolForKey("initialized") )
	{
		m_GameData->setStringForKey("tokenId", "token jg");

		m_GameData->setStringForKey("usersName", "jg");

		m_GameData->setBoolForKey("two", true);
		m_GameData->setBoolForKey("three", true);
		m_GameData->setBoolForKey("four", true);

		m_GameData->setBoolForKey("initialized", true);
	}

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
		return CNetworkLogic::GetInstance()->GetPlayerName(playerIdx);
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerName(playerIdx);
	}
}

std::string CGameManager::GetPlayerNameByCharacterId(int characterId)
{
	if (m_IsOnlineGame)
	{
		for (int i =0; i < MAX_PLAYER_NUM; ++i)
		{
			if ( CNetworkLogic::GetInstance()->GetPlayerCharacterId(i) == characterId )
			{
				return CNetworkLogic::GetInstance()->GetPlayerName(i);
			}
		}
	}
	else
	{
		for (int i =0; i < MAX_PLAYER_NUM; ++i)
		{
			if ( CGameLogic::GetInstance()->GetCharacterIdByPlayerId(i) == characterId )
			{
				return CGameLogic::GetInstance()->GetPlayerName(i);
			}
		}
	}

	return NULL;
}

int CGameManager::GetCurrentPlayerNumber()
{
	if (m_IsOnlineGame)
	{
		return CNetworkLogic::GetInstance()->GetCurrentPlayerNumber();
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
		// server에서 필요한 정보를 받아 온다.
		// winner idx - 동점 경우도 생각해야 함
		return 0;
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
		return CNetworkLogic::GetInstance()->GetPlayerResult(playerIdx, item);
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
		return CNetworkLogic::GetInstance()->GetPlayerTotalScore(playerIdx);
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
		return CNetworkLogic::GetInstance()->GetPlayerResultImage(playerIdx);
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
		CNetworkLogic::GetInstance()->SelectCharacter(characterId);
	}
	else
	{
		SetUpdateFlag( CGameLogic::GetInstance()->SetPlayerCharacterId( characterId ) );
	}
}

void CGameManager::SelectCharacter( int playerId, int characterId )
{
	if (m_IsOnlineGame)
	{
		CNetworkLogic::GetInstance()->SelectCharacter(characterId);
	}
	else
	{
		SetUpdateFlag( CGameLogic::GetInstance()->SetPlayerCharacterId( playerId, characterId ) );
	}
}

bool CGameManager::IsCharacterSelected( int characterId )
{
	if (m_IsOnlineGame)
	{
		for (int i = 0; i < MAX_PLAYER_NUM; ++i)
		{
			if (CNetworkLogic::GetInstance()->GetPlayerCharacterId(i) == characterId)
			{
				return true;
			}
		}

		return false;
	}
	else
	{
		return CGameLogic::GetInstance()->IsCharacterSelected(characterId);
	}
}

int CGameManager::GetCharacterIdByPlayerId( int playerId )
{
	if (m_IsOnlineGame)
	{
		return CNetworkLogic::GetInstance()->GetPlayerCharacterId( playerId );
	}
	else
	{
		return CGameLogic::GetInstance()->GetCharacterIdByPlayerId( playerId );
	}
}

int CGameManager::GetPlayerIdByTurn( int currentTurn )
{
	if (m_IsOnlineGame)
	{
		return CNetworkLogic::GetInstance()->GetPlayerIdByTurn(currentTurn);
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
		CNetworkLogic::GetInstance()->SettingReady();
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
		CNetworkLogic::GetInstance()->SetMapSize(mapSize);
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
		return CNetworkLogic::GetInstance()->IsEnd();
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
		return CNetworkLogic::GetInstance()->GetSelectedMapSize();
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
		return CNetworkLogic::GetInstance()->GetMapType(indexedPosition);
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
		return CNetworkLogic::GetInstance()->GetMapOwner(indexedPosition);
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
		return CNetworkLogic::GetInstance()->GetItem(indexedPosition);
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
		return CNetworkLogic::GetInstance()->DrawLine(indexedPosition);
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
		return CNetworkLogic::GetInstance()->GetPlayerPlayImage(playerIdx);
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
		return CNetworkLogic::GetInstance()->IsConnected(indexedPosition);
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
		return CNetworkLogic::GetInstance()->GetPlayerTurnById(playerId);
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
		return CNetworkLogic::GetInstance()->GetPlayerIdByCurrentTurn();
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
		return CNetworkLogic::GetInstance()->GetTileAnimationTurn(indexedPosition);
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

		// 멀티에서는 NEXT 버튼을 누르기 전에는 무조건 return false
		return false;
	}
	else
	{
		return CGameLogic::GetInstance()->IsPlayerNumberAndMapSeleted();
	}
}

int CGameManager::GetPlayerNumberOfThisGame()
{
	if (m_IsOnlineGame)
	{
		// 필요한가?
		CNetworkLogic::GetInstance()->GetCurrentPlayerNumber();
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerNumberOfThisGame();
	}
}

bool CGameManager::GetStatusPlayerNumber(int playerNumber)
{
	std::string key = "";

	switch (playerNumber)
	{
	case 2:
		key = "two";
		break;
	case 3:
		key = "three";
		break;
	case 4:
		key = "four";
		break;
	default:
		break;
	}

	return m_GameData->getBoolForKey(key.c_str() );
}

void CGameManager::SetPlayerNumberOfThisGame( int PlayerNumber )
{
	if (m_IsOnlineGame)
	{
		// shared data에 player number flags 설정
		std::string key = "";
		switch (PlayerNumber)
		{
		case 2:
			key = "two";
			break;
		case 3:
			key = "three";
			break;
		case 4:
			key = "four";
			break;
		default:
			break;
		}

		bool value = m_GameData->getBoolForKey(key.c_str() );
		
		m_GameData->setBoolForKey(key.c_str(), !value);
		SetUpdateFlag(true);
	}
	else
	{
		CGameLogic::GetInstance()->SetPlayerNumberOfThisGame(PlayerNumber);
	}
}

void CGameManager::SetOnlineMode(bool flag)	
{ 
	m_IsOnlineGame = flag; 

	if (m_IsOnlineGame)
	{
		CNetworkLogic::GetInstance()->SetCurrentNetworkPhase(NP_PLAYER_NUMBER_SETTING);
	}
}

SceneName CGameManager::GetCurrentScene()
{
	if (m_IsOnlineGame)
	{
		// Logic
		// 조심해!! Single과 같은 로직으로 만들어뒀어!
		return CNetworkLogic::GetInstance()->GetCurrentScene();
	}
	else
	{
		// 쓸 일은 없음
		return SC_MAIN;
	}
}

NetworkPhase CGameManager::GetCurrentNetworkPhase()
{
	return CNetworkLogic::GetInstance()->GetCurrentNetworkPhase();
}

bool CGameManager::InitNetworkLogic()
{
	return CNetworkLogic::GetInstance()->Init();
}

void CGameManager::Login()
{
	CNetworkLogic::GetInstance()->Login();
}

void CGameManager::Logout()
{
	CNetworkLogic::GetInstance()->Logout();
}

void CGameManager::JoinUpdate(float dt)
{
	CNetworkLogic::GetInstance()->JoinUpdate(dt);
}

void CGameManager::PlayUpdate(float dt)
{
	CNetworkLogic::GetInstance()->PlayUpdate(dt);
}

void CGameManager::PlayReady()
{
	CNetworkLogic::GetInstance()->PlayReady();
}

bool CGameManager::IsNextButtonSelected()
{
	if (m_IsOnlineGame)
	{
		// Logic
		// 조심해!! Single과 같은 로직으로 만들어뒀어!
		return CGameLogic::GetInstance()->IsNextButtonSelected();
	}
	else
	{
		return CGameLogic::GetInstance()->IsNextButtonSelected();
	}
}

void CGameManager::SetNextButtonSelected()
{
	if (m_IsOnlineGame)
	{
		// Logic
	}
	else
	{
		CGameLogic::GetInstance()->SetNextButtonSelected();
	}
}

void CGameManager::TimeOut()
{
	if (m_IsOnlineGame)
	{
		// Logic
	}
	else
	{
		SetUpdateFlag(CGameLogic::GetInstance()->TimeOut());
	}
}

std::string CGameManager::GetUsersName()
{
	return m_GameData->getStringForKey("usersName");
}

std::string CGameManager::GetTokenId()
{
	return m_GameData->getStringForKey("tokenId");
}

bool CGameManager::GetPlayerNumberSelection(int number)
{
	switch (number)
	{
	case 2:
		return m_GameData->getBoolForKey("two");
		break;
	case 3:
		return m_GameData->getBoolForKey("three");
		break;
	case 4:
		return m_GameData->getBoolForKey("four");
		break;
	default:
		break;
	}

	return false;
}

void CGameManager::SetUsersName(std::string name)
{
	m_GameData->setStringForKey("usersName", name);
}

void CGameManager::SetTokenId(std::string tokenId)
{
	m_GameData->setStringForKey("tokenId", tokenId);
}

void CGameManager::SetPlayerNumberSelection(int number, bool selection)
{
	switch (number)
	{
	case 2:
		return m_GameData->setBoolForKey("two", selection);
		break;
	case 3:
		return m_GameData->setBoolForKey("three", selection);
		break;
	case 4:
		return m_GameData->setBoolForKey("four", selection);
		break;
	default:
		break;
	}
}

int CGameManager::GetPlayerIdByCharactyerId( int characterId )
{
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		if ( characterId == GetCharacterIdByPlayerId(i) )
		{
			return i;
		}
	}
	// err
	return -1;
}

bool CGameManager::IsPlayerJoinedGame( int characterId )
{
	if ( m_IsOnlineGame )
	{
		// 조심해! Test Code
		return false;
	}
	else
	{
		return CGameLogic::GetInstance()->IsPlayerJoinedGame(characterId);
	}
}

bool CGameManager::IsChannelMaster()
{
	return CNetworkLogic::GetInstance()->IsChannelMaster();
}

bool CGameManager::IsReady()
{
	return CNetworkLogic::GetInstance()->IsReady();
}

bool CGameManager::IsReady( int playerId )
{
	return CNetworkLogic::GetInstance()->IsReady(playerId);
}

bool CGameManager::IsAllReady()
{
	return CNetworkLogic::GetInstance()->IsAllReady();
}

int CGameManager::GetMyPlayerId()
{
	return CNetworkLogic::GetInstance()->GetMyPlayerId();
}

bool CGameManager::GetCurrentTimerStatus()
{
	if ( m_IsOnlineGame )
	{
		return CNetworkLogic::GetInstance()->GetCurrentTimerStatus();
	}
	else
	{
		return false;
	}
	
}

void CGameManager::SetAnimationDelay(int time)
{
	if (m_AnimationDelay < time)
	{
		m_AnimationDelay = time;
	}
}