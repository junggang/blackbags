#include "GameLogic.h"
#include <queue>

USING_NS_CC;

CGameLogic* CGameLogic::m_pInstance = nullptr;

CGameLogic::CGameLogic(void)
{
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		m_PlayerData[i] = nullptr;
	}

	m_currentTurn = 0;
	m_VoidTileCount = 0;
	m_PlayerNumber = 0;
}


CGameLogic::~CGameLogic(void)
{
}

CGameLogic* CGameLogic::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CGameLogic();
	}

	return m_pInstance;
}

void CGameLogic::ReleaseInstance()
{
}

bool CGameLogic::init()
{
	m_SelectedMapSize = MS_NOT_SELECTED;

	for (int i = 0; i < MAX_MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAX_MAP_WIDTH; ++j)
		{
			m_Map[i][j].m_AnimationFlag = false;
			m_Map[i][j].m_AnimationTurn = 0;
			m_Map[i][j].m_Direction = DI_UP;
			m_Map[i][j].m_Flag = false;
			m_Map[i][j].m_Item = ITEM_NOTHING;
			m_Map[i][j].m_MouseOverFlag = false;
			m_Map[i][j].m_Owner = MO_NOBODY;
			m_Map[i][j].m_StartTime = 0;
			m_Map[i][j].m_Type = MO_SENTINEL;
		}
	}

	// PlayerData�� ���� �Ҵ�
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		if ( m_PlayerData[i] != nullptr )
		{
			delete m_PlayerData[i];
			m_PlayerData[i] = nullptr;
		}

		m_PlayerData[i] = new PlayerData();
	}

	//ĳ���� ���� �ڷḦ �־��ش�.
	for (int i = 0; i < CHARACTER_NUM; ++i)
	{
		switch (i)
		{
		case 0:
			m_Character[0].m_CharacterName = "Green";
			m_Character[0].m_CharacterColor = ccc4(_COLOR_CHARACTER_1_) ;
			m_Character[0].m_CharacterSettingImage = "image/CHARACTER_1_Play.png";
			m_Character[0].m_CharacterPlayImage = "image/CHARACTER_1_Play.png";
			m_Character[0].m_CharacterResultImage = "image/PLAYER_face1.png";
			m_Character[0].m_CharacterVoice = "Sound/PLAYER_1_good.mp3";
			break;
		case 1:
			m_Character[1].m_CharacterName = "Blue";
			m_Character[1].m_CharacterColor = ccc4(_COLOR_CHARACTER_2_ );
			m_Character[1].m_CharacterSettingImage = "image/CHARACTER_2_Play.png";
			m_Character[1].m_CharacterPlayImage = "image/CHARACTER_2_Play.png";
			m_Character[1].m_CharacterResultImage = "image/PLAYER_face2.png";
			m_Character[1].m_CharacterVoice = "Sound/PLAYER_2_good.mp3";			
			break;
		case 2:
			m_Character[2].m_CharacterName = "Red";
			m_Character[2].m_CharacterColor = ccc4(_COLOR_CHARACTER_3_ );
			m_Character[2].m_CharacterSettingImage = "image/CHARACTER_3_Play.png";
			m_Character[2].m_CharacterPlayImage = "image/CHARACTER_3_Play.png";
			m_Character[2].m_CharacterResultImage = "image/PLAYER_face3.png";
			m_Character[2].m_CharacterVoice = "Sound/PLAYER_3_good.mp3";
			break;
		case 3:
			m_Character[3].m_CharacterName = "Yellow";
			m_Character[3].m_CharacterColor =ccc4( _COLOR_CHARACTER_4_) ;
			m_Character[3].m_CharacterSettingImage = "image/CHARACTER_4_Play.png";
			m_Character[3].m_CharacterPlayImage = "image/CHARACTER_4_Play.png";
			m_Character[3].m_CharacterResultImage = "image/PLAYER_face4.png";
			m_Character[3].m_CharacterVoice = "Sound/PLAYER_4_good.mp3";	
			break;

		}
	}

	return true;
}

bool CGameLogic::SetSelectedMapSize( MapSelect mapSize )
{
	m_SelectedMapSize = mapSize;

	return true;
}

void CGameLogic::UpdatePlayerResult( int playerId, MO_ITEM item )
{
	++m_PlayerData[playerId]->m_MyTile;

	switch (item)
	{
	case ITEM_GOLD:
		++m_PlayerData[playerId]->m_MyGold;
		break;
	case ITEM_TRASH:
		++m_PlayerData[playerId]->m_MyTrash;
		break;
	default:
		break;
	}
}

int CGameLogic::GetPlayerResult(int playerId, MO_ITEM item)
{
	switch (item)
	{
	case ITEM_NOTHING:
		return m_PlayerData[playerId]->m_MyTile;
		break;
	case ITEM_GOLD:
		return m_PlayerData[playerId]->m_MyGold;
		break;
	case ITEM_TRASH:
		return m_PlayerData[playerId]->m_MyTrash;
		break;
	default:
		break;
	}
}

bool CGameLogic::IsPossible(IndexedPosition indexedPosition)
{
	if (m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Type == MO_LINE_UNCONNECTED 
		|| m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Type == MO_LINE_HIDDEN)
	{
		int tileVoidCount = 0;

		//�Էµ� ��Ÿ�� �ֺ��� Ȯ���ؼ� �����ְ� ���� Ÿ�ϰ� ��Ƽ���� ���ڸ� ����
		if (m_Map[indexedPosition.m_PosI + 1][indexedPosition.m_PosJ].m_Owner == MO_NOBODY) { ++tileVoidCount; }

		if (m_Map[indexedPosition.m_PosI - 1][ indexedPosition.m_PosJ].m_Owner == MO_NOBODY) { ++tileVoidCount; }

		if (m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ + 1].m_Owner == MO_NOBODY) { ++tileVoidCount; }

		if (m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ - 1].m_Owner == MO_NOBODY) { ++tileVoidCount; }

		//Ȯ�ε� Ÿ���� ���� 4�� �Ǹ� �Էµ� ��Ÿ���� ���� Ÿ�ϵ� ���̿� �����Ƿ� ���� �� ����
		if (tileVoidCount == 4)
		{
			return true;
		}
	}

	return false;
}

bool CGameLogic::IsClosed( IndexedPosition indexedPosition )
{
	//���õ� ��Ÿ���� ���� Ȯ��
	CollectClosedTile(indexedPosition, DI_UP);
	if (m_ClosedTile[0].m_PosI != 0 && m_ClosedTile[0].m_PosJ != 0)
		return true;

	//���õ� ��Ÿ���� ������ Ȯ��
	CollectClosedTile(indexedPosition, DI_RIGHT);
	if (m_ClosedTile[0].m_PosI != 0 && m_ClosedTile[0].m_PosJ != 0)
		return true;

	//���õ� ��Ÿ���� �Ʒ��� Ȯ��
	CollectClosedTile(indexedPosition, DI_DOWN);
	if (m_ClosedTile[0].m_PosI != 0 && m_ClosedTile[0].m_PosJ != 0)
		return true;

	//���õ� ��Ÿ���� ���� Ȯ��
	CollectClosedTile(indexedPosition, DI_LEFT);
	if (m_ClosedTile[0].m_PosI != 0 && m_ClosedTile[0].m_PosJ != 0)
		return true;

	return false;
}

bool CGameLogic::IsEnd()
{
	return (m_VoidTileCount == 0);
}

void CGameLogic::CollectClosedTile( IndexedPosition indexedPosition, Direction direction )
{
	std::queue<IndexedPosition> searchTiles;

	IndexedPosition currentTile;
	IndexedPosition nextTile;

	//Ȯ�� �� ������ ����
	switch (direction)
	{
	case DI_UP:
		currentTile.m_PosI = indexedPosition.m_PosI - 1;
		currentTile.m_PosJ = indexedPosition.m_PosJ;
		break;
	case DI_RIGHT:
		currentTile.m_PosI = indexedPosition.m_PosI;
		currentTile.m_PosJ = indexedPosition.m_PosJ + 1;
		break;
	case DI_DOWN:
		currentTile.m_PosI = indexedPosition.m_PosI + 1;
		currentTile.m_PosJ = indexedPosition.m_PosJ;
		break;
	case DI_LEFT:
		currentTile.m_PosI = indexedPosition.m_PosI;
		currentTile.m_PosJ = indexedPosition.m_PosJ - 1;
		break;
	default:
		break;
	}

	//Ȯ�� �� ������ ������� ���̸� Ȯ�� �� ��
	if (m_Map[currentTile.m_PosI][currentTile.m_PosJ].m_Type != MO_DOT)
	{
		//Ÿ�Ͽ� �ִϸ��̼� �����ϴ� ���� ��Ÿ���� ���� ����
		int animationTurn = 1;
		SetAnimationState(currentTile, animationTurn, direction);

		//�տ��� ������ Ž�� ��� ������ ť�� �迭�� �ִ´�.
		int i = 0;

		searchTiles.push(currentTile);
		m_ClosedTile[i++] = currentTile;
		m_Map[currentTile.m_PosI][currentTile.m_PosJ].m_Flag = true;

		while (!searchTiles.empty() )
		{
			currentTile.m_PosI = searchTiles.front().m_PosI;
			currentTile.m_PosJ = searchTiles.front().m_PosJ;
			searchTiles.pop();

			//currentTile�� sentinel�̸� ���ݱ��� Ȯ���� �������δ� ������ ���������Ƿ� Ȯ���� Ÿ���� �����ϴ� �迭�� �ʱ�ȭ�ϰ� Ȯ�� ����
			if (m_Map[currentTile.m_PosI][currentTile.m_PosJ].m_Type == MO_SENTINEL)
			{
				for (int tempI = 0 ; tempI < MAX_MAP_WIDTH; ++tempI)
				{
					for (int tempJ = 0 ; tempJ < MAX_MAP_HEIGHT; ++tempJ)
					{
						m_Map[tempI][tempJ].m_Flag = false;

						if (m_Map[currentTile.m_PosI][currentTile.m_PosJ].m_Type == MO_TILE)
						{
							//�ִϸ��̼� ����� ���� �����͵� �ʱ�ȭ
							InitAnimationState(IndexedPosition(tempI, tempJ));
						}

						//����� �ִϸ��̼��� �����Ƿ� 0���� ����
						animationTurn = 0;
					}
				}
				//memset(m_ClosedTile, 0, sizeof(IndexedPosition) * CHECKLIST_LENGTH);

				for (int idx = 0; idx < m_ClosedTile.size(); ++idx)
				{
					m_ClosedTile[idx].m_PosI = 0;
					m_ClosedTile[idx].m_PosJ = 0;
				}
#ifdef _DEBUG
				CCLOG("sentinel !!!");
#endif
				break;
			}
#ifdef _DEBUG
			CCLOG("idx I : %d / idx J : %d", currentTile.m_PosI, currentTile.m_PosJ);
#endif
			//���� Ÿ���� ���� Ȯ��
			if (m_Map[currentTile.m_PosI - 1][currentTile.m_PosJ].m_Type == MO_LINE_UNCONNECTED)
			{
				nextTile.m_PosI = currentTile.m_PosI - 2;
				nextTile.m_PosJ = currentTile.m_PosJ;
				if (!IsAlreadyChecked(nextTile) )
				{
					searchTiles.push(nextTile);
					m_ClosedTile[i++] = nextTile;
					m_Map[nextTile.m_PosI][nextTile.m_PosJ].m_Flag = true;

					//�ִϸ��̼� ����� ���� ������ ���� ����
					animationTurn = GetTileAnimationTurn(currentTile) + 1;
					SetAnimationState(nextTile, animationTurn, DI_UP);
				}				
			}

			//���� Ÿ���� ������ Ȯ��
			if (m_Map[currentTile.m_PosI][currentTile.m_PosJ + 1].m_Type == MO_LINE_UNCONNECTED)
			{
				nextTile.m_PosI = currentTile.m_PosI;
				nextTile.m_PosJ = currentTile.m_PosJ + 2;
				if (!IsAlreadyChecked(nextTile) )
				{
					searchTiles.push(nextTile);
					m_ClosedTile[i++] = nextTile;
					m_Map[nextTile.m_PosI][nextTile.m_PosJ].m_Flag = true;

					//�ִϸ��̼� ����� ���� ������ ���� ����
					animationTurn = GetTileAnimationTurn(currentTile) + 1;
					SetAnimationState(nextTile, animationTurn, DI_RIGHT);
				}				
			}

			//���� Ÿ���� �Ʒ��� Ȯ��
			if (m_Map[currentTile.m_PosI + 1][currentTile.m_PosJ].m_Type == MO_LINE_UNCONNECTED)
			{
				nextTile.m_PosI = currentTile.m_PosI + 2;
				nextTile.m_PosJ = currentTile.m_PosJ;
				if (!IsAlreadyChecked(nextTile) )
				{
					searchTiles.push(nextTile);
					m_ClosedTile[i++] = nextTile;
					m_Map[nextTile.m_PosI][nextTile.m_PosJ].m_Flag = true;

					//�ִϸ��̼� ����� ���� ������ ���� ����
					animationTurn = GetTileAnimationTurn(currentTile) + 1;
					SetAnimationState(nextTile, animationTurn, DI_DOWN);
				}				
			}

			//���� Ÿ���� ���� Ȯ��
			if (m_Map[currentTile.m_PosI][currentTile.m_PosJ - 1].m_Type == MO_LINE_UNCONNECTED)
			{
				nextTile.m_PosI = currentTile.m_PosI;
				nextTile.m_PosJ = currentTile.m_PosJ - 2;
				if (!IsAlreadyChecked(nextTile) )
				{
					searchTiles.push(nextTile);
					m_ClosedTile[i++] = nextTile;
					m_Map[nextTile.m_PosI][nextTile.m_PosJ].m_Flag = true;

					//�ִϸ��̼� ����� ���� ������ ���� ����
					animationTurn = GetTileAnimationTurn(currentTile) + 1;
					SetAnimationState(nextTile, animationTurn, DI_LEFT);
				}				
			}
		}

		//���� Ÿ���� �����Ƿ� �ִϸ��̼� �����϶�� �÷��� ����
		SetTileAnimationTurnNumber(animationTurn);
	}
}

bool CGameLogic::IsAlreadyChecked( const IndexedPosition& nextTile )
{
	return m_Map[nextTile.m_PosI][nextTile.m_PosJ].m_Flag;
}

void CGameLogic::SetAnimationState(IndexedPosition indexedPosition, int turn, Direction direction)
{
	assert(indexedPosition.m_PosI < MAX_MAP_WIDTH && indexedPosition.m_PosJ<MAX_MAP_HEIGHT) ;

	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_AnimationFlag = true;
	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_AnimationTurn = turn;
	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Direction = direction;
}

void CGameLogic::InitAnimationState(IndexedPosition indexedPosition)
{
	assert(indexedPosition.m_PosI < MAX_MAP_WIDTH && indexedPosition.m_PosJ<MAX_MAP_HEIGHT) ;

	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_AnimationTurn = 0;
	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_AnimationFlag = false;
	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Direction = DI_UP;
}

int	CGameLogic::GetTileAnimationTurn(IndexedPosition indexedPosition)
{
	assert(indexedPosition.m_PosI < MAX_MAP_WIDTH && indexedPosition.m_PosJ<MAX_MAP_HEIGHT) ;

	return m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_AnimationTurn;
}

int	CGameLogic::GetWinnerIdx()
{
	int result = -1;

	for (int i = 1; i < CGameLogic::GetInstance()->GetplayerNumber(); ++i)
	{
		if (CGameLogic::GetInstance()->GetPlayerTotalScore(i - 1) > CGameLogic::GetInstance()->GetPlayerTotalScore(i) )
		{
			result = i -1;
		}
		else
		{
			result = i;
		}
	}

	return result;
}

void CGameLogic::SetMapFlag( IndexedPosition indexedPosition,bool flag )
{
	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Flag = flag;
}

bool CGameLogic::SetPlayerName(int playerId,  const std::string& playerName )
{
	m_PlayerData[playerId]->m_PlayerName = playerName;

	return true;
}

bool CGameLogic::SetPlayerCharacterId( int characterId )
{
	// IsCharacterSelected �˻縦 �ؼ� ���õǾ� ������ �� �ϰ�
	// 	if ( isCharacterSelected(characterId) )
	// 	{
	// 		return;
	// 	}

	// Single �� ��
	// �̹� ���õ� ĳ�������� Ȯ���ؼ� ���õǾ� �ִٸ� ��ҽ�Ű�� ����
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		if ( m_PlayerData[i]->m_CharacterId == characterId 
			&& m_PlayerData[i]->m_PlayerId != -1 )
		{
			m_PlayerData[i]->m_CharacterId = -1;
			m_PlayerData[i]->m_PlayerId = -1;
			--m_PlayerNumber;

			return false;
		}
	}

	// ���� ���õ��� ���� ĳ���Ͷ�� �߰����ش�
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		if (m_PlayerData[i]->m_PlayerId == -1)
		{
			m_PlayerData[i]->m_PlayerId = i;
			m_PlayerData[i]->m_CharacterId = characterId;
			++m_PlayerNumber;

			return true;
		}
	}

	return true;
	// �� ���� �ڵ�� �� ����!
	//�̹� �����ߴ� ĳ���Ͱ� �ִٸ� ���� ĳ���ʹ� Ǯ���ش�.
	// 	if (m_PlayerData[playerId]->m_CharacterId != -1)
	// 	{
	// 		m_Character[m_PlayerData[playerId]->m_CharacterId].m_isCharacterSelected = false;
	// 	}
	// 	m_PlayerData[playerId]->m_CharacterId = characterId;
}

bool CGameLogic::StartGame()
{
	/*
	//////////////////////�׽�Ʈ�� �÷��̾� ����/////////////////////////////////////////////
	m_PlayerData[0]= new PlayerData();
	m_PlayerData[0]->m_CharacterId=1;
	m_PlayerData[0]->m_PlayerId=0;
	m_PlayerData[0]->m_PlayerName="���̵�0";
	m_PlayerData[1]= new PlayerData();
	m_PlayerData[1]->m_CharacterId=0;
	m_PlayerData[1]->m_PlayerId=1;
	m_PlayerData[1]->m_PlayerName="���̵�1";
	m_PlayerData[2]= new PlayerData();
	m_PlayerData[2]->m_CharacterId=3;
	m_PlayerData[2]->m_PlayerId=2;
	m_PlayerData[2]->m_PlayerName="���̵�2";
	m_PlayerNumber=3;
	///////////////////////////////////////////////////////////////////////////////////////////
	*/
	// �� ���� & �÷��̾�� �� ����

	//������ �ٲ� ��
	std::array<int,4> tempTurn = {0, 1, 2, 3};
	srand( static_cast<unsigned int>(time(NULL)) );
	std::random_shuffle(tempTurn.begin(), tempTurn.end());

	PlayerData* current;
	int tempT = 0;
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		if (m_PlayerData[i]->m_PlayerId == -1)
			continue;

		while (tempTurn[tempT] >= m_PlayerNumber)
			++tempT;

		m_PlayerData[i]->m_PlayerTurn = tempTurn[tempT];

		if (tempTurn[tempT] == 0)
			current = m_PlayerData[i];

		++tempT;
	}

	//�ϴ� current�� ã��, current->playerTurn + 1�� tempPlayer�� ã��
	//current->next = tempPlayer
	//current = tempPlayer
	//�ٽ� �ݺ�

	//���� ��ũ�� ����Ʈ�� ���������!
	m_FirstPlayer = current;

	for (int i = 0; i < m_PlayerNumber; i++)
	{
		for (int j = 0; j < m_PlayerNumber; ++j)
		{
			if (m_PlayerData[i]->m_PlayerTurn+1 == m_PlayerData[j]->m_PlayerTurn)
				m_PlayerData[i]->m_nextPlayer = m_PlayerData[j];
		}

		if (m_PlayerData[i]->m_nextPlayer == nullptr)
			tempT = i;
	}

	m_PlayerData[tempT]->m_nextPlayer = m_FirstPlayer;

	CCLOG("player number : %d", m_PlayerNumber);



// 	for (int i = 0 ; i < MAX_PLAYER_NUM; ++i)
// 	{
// 		// PlayerId�� -1�� �ƴ� ��쿡�� TurnList�� ������ ������ �־��ش�.
// 		if ( m_PlayerData[i]->m_PlayerId != -1 )
// 		{
// 			int currentListSize = m_PlayerDataByTurn.size();
// 
// 			int randomPosition = rand() % ( currentListSize + 1 );
// 
// 			std::list<PlayerData*>::iterator iterInsertPos = m_PlayerDataByTurn.begin();
// 
// 			for (int j = 0 ; j < randomPosition; ++j)
// 			{
// 				++iterInsertPos;
// 			}
// 
// 			m_PlayerDataByTurn.insert(iterInsertPos, m_PlayerData[i]);
// 		}
// 	}

	// �� ����
	CreateMap();

	// �ʿ� �������� ��, ������ �Ѹ��� (ũ�� �ݿ�)
	//InitRandomMap();

	return true;
}

void CGameLogic::CreateMap()
{
	/*	������ ���ӿ� ���Ǵ� Ÿ�� �ܿ��� ��Ÿ���� ���� ǥ���ϱ� ���� ĭ�� �ʿ�
	������ ���� �ֺ��� �⺻���� MO_SENTINEL�� �ξ IsClosed()�� ���� �۾��� Ȱ���� �� �ֵ��� �� */
	int targetRow, targetColumn;

	MapSize mapSize;

	// MapSelect���� MapSize�� ����� ����
	switch(m_SelectedMapSize)
	{
	case MS_6X5:
		mapSize.m_Width = 6;
		mapSize.m_Height = 5;
		break;
	case MS_8X7:
		mapSize.m_Width = 8;
		mapSize.m_Height = 7;
		break;
	default:
		// ������!! ����ڵ带 �־����!! ���� ������ ���� �߸��ȰŴ�
		return;
	}

	m_VoidTileCount = mapSize.m_Width * mapSize.m_Height;

	for (targetRow = 1; targetRow <= mapSize.m_Height*2 + 1; ++targetRow)
	{  		
		for (targetColumn = 1; targetColumn <= mapSize.m_Width*2 + 1; ++targetColumn) 
		{ 
			if (targetRow % 2 == 1)
			{
				// dot - line - dot - line
				if (targetColumn % 2 == 1)
				{
					m_Map[targetRow][targetColumn].m_Type = MO_DOT;
				} 
				else 
				{
					m_Map[targetRow][targetColumn].m_Type = MO_LINE_UNCONNECTED;
				}
			} 
			else 
			{
				// line - tile - line - tile
				if (targetColumn % 2 == 1)
				{
					m_Map[targetRow][targetColumn].m_Type = MO_LINE_UNCONNECTED;
				} 
				else 
				{
					m_Map[targetRow][targetColumn].m_Type = MO_TILE;
				}
			}
		}
	}

	return;
}

void CGameLogic::InitRandomMap()
{
	// ��Ÿ��, ���, ���� ������ ���� ������
	int startLineNumber = 0;
	int startGoldNumber = 0;
	int startTrashNumber = 0;

	switch (m_SelectedMapSize)
	{
	case MS_6X5: 
		startLineNumber = 13;
		startGoldNumber = 5;
		startTrashNumber = 4;
		break;
	case MS_8X7:
		startLineNumber = 27;
		startGoldNumber = 8;
		startTrashNumber = 7;
		break;
	default:
		break;
	}

	// IsClosed���� ����� �������Դϴ�.
	IndexedPosition RandomTargetPosition;

	// �������� �õ尪�� �ʿ��� ��� �Ʒ� �õ带 �Ẹ�ñ� �ٶ��ϴ�.
	//srand(1383706550);

	// ��Ÿ���� �ѷ��ִ� �Լ��Դϴ�.
	while (startLineNumber)
	{
		// ��Ÿ���� (2,1), (1,2) ���� �����ϹǷ�
		RandomTargetPosition.m_PosI = rand() % MAX_MAP_HEIGHT;
		RandomTargetPosition.m_PosJ = rand() % MAX_MAP_WIDTH;

		// ���� ������ ���� ��ǥ�� MO_LINE_UNCONNECTED�� ��쿡
		if ( GetMapType(RandomTargetPosition) == MO_LINE_UNCONNECTED )
		{
			// IsPossible�� �����ϸ�
			if ( IsPossible(RandomTargetPosition) )
			{
				// �ϴ� �׸��ϴ�(IsClosed �˻縦 ���ؼ�)
				//printf("random %d , %d\n",RandomTargetPosition.m_PosI,RandomTargetPosition.m_PosJ);
				DrawLine(RandomTargetPosition);
				--startLineNumber;

				// ���� �� �׷��� ���� IsClosed() ������ �������� ������ �״�� ����
				if ( IsClosed(RandomTargetPosition) )
				{
					// ���� ���� �� �׷��� ���� � ������ �ݴ´ٸ� �ش� ���� �����ϰ� ���� ī���͸� ����
					DeleteLine(RandomTargetPosition);
					++startLineNumber;
				}
			}
		}

	}

	while (startGoldNumber != 0)
	{
		RandomTargetPosition.m_PosI = rand() % MAX_MAP_HEIGHT;
		RandomTargetPosition.m_PosJ = rand() % MAX_MAP_WIDTH;
		if (GetMapType(RandomTargetPosition) == MO_TILE 
			&& GetItem(RandomTargetPosition) == ITEM_NOTHING)
		{
			SetItem(RandomTargetPosition, ITEM_GOLD);
			startGoldNumber--;
		}
	}

	while (startTrashNumber != 0)
	{
		RandomTargetPosition.m_PosI = rand() % MAX_MAP_HEIGHT;
		RandomTargetPosition.m_PosJ = rand() % MAX_MAP_WIDTH;
		if (GetMapType(RandomTargetPosition) == MO_TILE 
			&& GetItem(RandomTargetPosition) == ITEM_NOTHING)
		{
			SetItem(RandomTargetPosition, ITEM_TRASH);
			startTrashNumber--;
		}
	}

	return;
}

void CGameLogic::DrawLine( const IndexedPosition& indexedPosition )
{
	// ������ ��� ��� ���� ó��
	assert(indexedPosition.m_PosI < MAX_MAP_WIDTH && indexedPosition.m_PosJ < MAX_MAP_HEIGHT) ;

	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Type = MO_LINE_CONNECTED;

	//animaiton start
	m_LineAnimationFlag = true;
	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_AnimationFlag = true;
}

void CGameLogic::DeleteLine( const IndexedPosition& indexedPosition )
{
	// ������ ��� ��� ���� ó��
	assert(indexedPosition.m_PosI < MAX_MAP_WIDTH && indexedPosition.m_PosJ < MAX_MAP_HEIGHT) ;

	//���� ���� �ߴ� ���������� �ִϸ��̼� ���� ��ȭ �ǵ�����
	for (int tempI = 0 ; tempI < MAX_MAP_WIDTH; ++tempI)
	{
		for (int tempJ = 0 ; tempJ < MAX_MAP_HEIGHT; ++tempJ)
		{
			SetMapFlag(IndexedPosition(tempI, tempJ), false);

			if (GetMapType(IndexedPosition(tempI, tempJ) ) == MO_TILE)
			{
				//�ִϸ��̼� ����� ���� �����͵� �ʱ�ȭ
				InitAnimationState(IndexedPosition(tempI, tempJ) );
			}
		}
	}

	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Type = MO_LINE_UNCONNECTED;
}

void CGameLogic::SetItem( IndexedPosition indexedPosition, MO_ITEM item )
{
	assert(indexedPosition.m_PosI < MAX_MAP_WIDTH && indexedPosition.m_PosJ < MAX_MAP_HEIGHT) ;

	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Item = item;
}

bool CGameLogic::EventHandle(IndexedPosition indexedPosition)
{
	if (!IsPossible(indexedPosition) )
	{
		return false;
	}

	//IsPossible üũ �Ŀ� �ϴ� �׸��� ���� ���� ���� üũ
	DrawLine(indexedPosition);

	for (int i = 0; i < m_ClosedTile.size(); ++i)
	{
		m_ClosedTile[i].m_PosI = 0;
		m_ClosedTile[i].m_PosJ = 0;
	}

	if (IsClosed(indexedPosition))
	{
		int i = 0;
		while (m_ClosedTile[i].m_PosI != 0 && m_ClosedTile[i].m_PosJ != 0 )
		{
			//���� Ÿ�Ͽ� ���� �־����� Ȯ���ؼ� ���� �ٲ� ��!!
			m_Map[m_ClosedTile[i].m_PosI][m_ClosedTile[i].m_PosJ].m_Owner = (MO_OWNER)GetPlayerIdByTurn(m_currentTurn % m_PlayerNumber);
			--m_VoidTileCount;
			i++;
		}
	}

	++m_currentTurn;

	return true;
}

int CGameLogic::GetPlayerIdByTurn( int currentTurn )
{
	PlayerData* currentPlayer = m_FirstPlayer;
	for(int i = 0;i<currentTurn;i++)
	{
		currentPlayer = currentPlayer->m_nextPlayer;
	}
	return currentPlayer->m_PlayerId;
}

MO_TYPE CGameLogic::IsConnected(IndexedPosition indexedPosition)
{
	MO_TYPE tempType = m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Type;

	if (tempType == MO_LINE_CONNECTED || tempType == MO_LINE_UNCONNECTED)
	{
		return m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Type;
	}
	else
	{
		CCLOG("what a %d", tempType);
	}
}