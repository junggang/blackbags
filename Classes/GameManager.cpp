#include "GameManager.h"
#include "GameLogic.h"
#include "NetworkLogic.h"

CGameManager* CGameManager::m_pInstance = nullptr;

CGameManager::CGameManager(void)
{
	m_IsOnlineGame = false;
	m_IsUpdated = false;
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
		// �ٸ� ������ �̸��� �������� �޾ƿ���
		// ���� �̸��� shared data�� ����� ���� ����ϹǷ� �� �Լ��� ������� ����
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

//������!!
//�̰� ȣ���ϴ� �Լ� �ƴ� �� ������
void CGameManager::SetCurrentPlayerNumber(int PlayerNumber)
{
	if (m_IsOnlineGame)
	{
		// player number�� ������ matching thread�� ���ؼ� �����ϹǷ� ������ ����
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
		//server���� �ʿ��� ������ �޾� �´�.
		// winner idx - ���� ��쵵 �����ؾ� ��
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

bool CGameManager::isCharacterSelected( int characterId )
{
	if (m_IsOnlineGame)
	{
		// �ʿ��Ѱ�?
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
		return CNetworkLogic::GetInstance()->GetPlayerCharacterId( playerId );
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
		// ä�� �������� ��� ������ �����ϰ� ��� ����� �����ϸ� true
		// �����Ͱ� �ƴ� ��� �ڽ��� ���� ���� Ȯ���ؼ� true / false

		// ��Ƽ������ NEXT ��ư�� ������ ������ ������ return false
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
		// �ʿ��Ѱ�?
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
		// shared data�� player number flags ����
	}
	else
	{
		CGameLogic::GetInstance()->SetPlayerNumberOfThisGame(PlayerNumber);
	}
}

bool CGameManager::IsLogin()
{
	return CNetworkLogic::GetInstance()->IsLogin();
}

bool CGameManager::IsLoginFail()
{
	return CNetworkLogic::GetInstance()->IsLoginFail();
}

bool CGameManager::IsInChannel()
{
	return CNetworkLogic::GetInstance()->IsInChannel();
}

bool CGameManager::InitNetworkLogic()
{
	return CNetworkLogic::GetInstance()->init();
}

bool CGameManager::IsNextButtonSelected()
{
	if (m_IsOnlineGame)
	{
		// Logic
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
