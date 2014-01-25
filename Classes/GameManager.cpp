#include "GameManager.h"
#include "GameLogic.h"

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
		//�¶����� ���
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
		//server���� �ʿ��� ������ �޾� �´�.
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
		//server���� �ʿ��� ������ �޾� �´�.
	}
	else
	{
		return CGameLogic::GetInstance()->GetplayerNumber();
	}
}

//������!!
//�̰� ȣ���ϴ� �Լ� �ƴ� �� ������
void CGameManager::SetPlayerNumber(int PlayerNumber)
{
	if (m_IsOnlineGame)
	{
		//server�� ��Ŷ�� ������.
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
		//server���� �ʿ��� ������ �޾� �´�.
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
		//server���� �ʿ��� ������ �޾� �´�.
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
		//server���� �ʿ��� ������ �޾� �´�.
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
		//server���� �ʿ��� ������ �޾� �´�.
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
		//�¶���
		return;
	}
	else
	{
		SetUpdateFlag(CGameLogic::GetInstance()->SetPlayerCharacterId( characterId ) );
	}
}

bool CGameManager::isCharacterSelected( int characterId )
{
	if (m_IsOnlineGame)
	{
		//�¶���
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
		//�¶���
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