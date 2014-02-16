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
	m_CurrentPlayerNumber = 0;
	m_PlayerNumberOfThisGame = 0;
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

	// PlayerData를 만들어서 할당
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		if ( m_PlayerData[i] != nullptr )
		{
			delete m_PlayerData[i];
			m_PlayerData[i] = nullptr;
		}

		m_PlayerData[i] = new PlayerData();
	}

	// 맵과 캐릭터를 골랐는지 여부 "고르지 않음"으로 설정, Next Button을 눌렀는지 여부를 "누르지 않음"으로 설정
	MapSelected = false;
	PlayerNumberSelected = false;
	NextButtonSelected = false;

	//캐릭터 관련 자료를 넣어준다.
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
			m_Character[0].m_isCharacterSelected = false;
			break;
		case 1:
			m_Character[1].m_CharacterName = "Blue";
			m_Character[1].m_CharacterColor = ccc4(_COLOR_CHARACTER_2_ );
			m_Character[1].m_CharacterSettingImage = "image/CHARACTER_2_Play.png";
			m_Character[1].m_CharacterPlayImage = "image/CHARACTER_2_Play.png";
			m_Character[1].m_CharacterResultImage = "image/PLAYER_face2.png";
			m_Character[1].m_CharacterVoice = "Sound/PLAYER_2_good.mp3";
			m_Character[1].m_isCharacterSelected = false;
			break;
		case 2:
			m_Character[2].m_CharacterName = "Red";
			m_Character[2].m_CharacterColor = ccc4(_COLOR_CHARACTER_3_ );
			m_Character[2].m_CharacterSettingImage = "image/CHARACTER_3_Play.png";
			m_Character[2].m_CharacterPlayImage = "image/CHARACTER_3_Play.png";
			m_Character[2].m_CharacterResultImage = "image/PLAYER_face3.png";
			m_Character[2].m_CharacterVoice = "Sound/PLAYER_3_good.mp3";
			m_Character[2].m_isCharacterSelected = false;
			break;
		case 3:
			m_Character[3].m_CharacterName = "Yellow";
			m_Character[3].m_CharacterColor =ccc4( _COLOR_CHARACTER_4_) ;
			m_Character[3].m_CharacterSettingImage = "image/CHARACTER_4_Play.png";
			m_Character[3].m_CharacterPlayImage = "image/CHARACTER_4_Play.png";
			m_Character[3].m_CharacterResultImage = "image/PLAYER_face4.png";
			m_Character[3].m_CharacterVoice = "Sound/PLAYER_4_good.mp3";
			m_Character[3].m_isCharacterSelected = false;
			break;

		}
	}

	return true;
}

bool CGameLogic::SetSelectedMapSize( MapSelect mapSize )
{
	m_SelectedMapSize = mapSize;
	MapSelected = true;

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

		//입력된 울타리 주변을 확인해서 소유주가 없는 타일과 센티널의 숫자를 센다
		if (m_Map[indexedPosition.m_PosI + 1][indexedPosition.m_PosJ].m_Owner == MO_NOBODY) { ++tileVoidCount; }

		if (m_Map[indexedPosition.m_PosI - 1][ indexedPosition.m_PosJ].m_Owner == MO_NOBODY) { ++tileVoidCount; }

		if (m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ + 1].m_Owner == MO_NOBODY) { ++tileVoidCount; }

		if (m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ - 1].m_Owner == MO_NOBODY) { ++tileVoidCount; }

		//확인된 타일의 수가 4가 되면 입력된 울타리는 열린 타일들 사이에 있으므로 그을 수 있음
		if (tileVoidCount == 4)
		{
			return true;
		}
	}

	return false;
}

bool CGameLogic::IsClosed( IndexedPosition indexedPosition )
{
	//선택된 울타리의 위쪽 확인
	CollectClosedTile(indexedPosition, DI_UP);
	if (m_ClosedTile[0].m_PosI != 0 && m_ClosedTile[0].m_PosJ != 0)
		return true;

	//선택된 울타리의 오른쪽 확인
	CollectClosedTile(indexedPosition, DI_RIGHT);
	if (m_ClosedTile[0].m_PosI != 0 && m_ClosedTile[0].m_PosJ != 0)
		return true;

	//선택된 울타리의 아래쪽 확인
	CollectClosedTile(indexedPosition, DI_DOWN);
	if (m_ClosedTile[0].m_PosI != 0 && m_ClosedTile[0].m_PosJ != 0)
		return true;

	//선택된 울타리의 왼쪽 확인
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

	//확인 할 방향을 지정
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

	//확인 할 방향의 출발점이 점이면 확인 안 함
	if (m_Map[currentTile.m_PosI][currentTile.m_PosJ].m_Type != MO_DOT)
	{
		//타일에 애니메이션 적용하는 순서 나타내기 위한 변수
		int animationTurn = 1;
		SetAnimationState(currentTile, animationTurn, direction);

		//앞에서 갱신한 탐색 출발 지점을 큐와 배열에 넣는다.
		int i = 0;

		searchTiles.push(currentTile);
		m_ClosedTile[i++] = currentTile;
		m_Map[currentTile.m_PosI][currentTile.m_PosJ].m_Flag = true;

		while (!searchTiles.empty() )
		{
			currentTile.m_PosI = searchTiles.front().m_PosI;
			currentTile.m_PosJ = searchTiles.front().m_PosJ;
			searchTiles.pop();

			//currentTile이 sentinel이면 지금까지 확인한 방향으로는 도형이 열려있으므로 확인한 타일을 저장하는 배열은 초기화하고 확인 종료
			if (m_Map[currentTile.m_PosI][currentTile.m_PosJ].m_Type == MO_SENTINEL)
			{
				for (int tempI = 0 ; tempI < MAX_MAP_WIDTH; ++tempI)
				{
					for (int tempJ = 0 ; tempJ < MAX_MAP_HEIGHT; ++tempJ)
					{
						m_Map[tempI][tempJ].m_Flag = false;

						if (m_Map[currentTile.m_PosI][currentTile.m_PosJ].m_Type == MO_TILE)
						{
							//애니메이션 재생을 위한 데이터도 초기화
							InitAnimationState(IndexedPosition(tempI, tempJ));
						}

						//재생할 애니메이션이 없으므로 0으로 설정
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
			//현재 타일의 위쪽 확인
			if (m_Map[currentTile.m_PosI - 1][currentTile.m_PosJ].m_Type == MO_LINE_UNCONNECTED)
			{
				nextTile.m_PosI = currentTile.m_PosI - 2;
				nextTile.m_PosJ = currentTile.m_PosJ;
				if (!IsAlreadyChecked(nextTile) )
				{
					searchTiles.push(nextTile);
					m_ClosedTile[i++] = nextTile;
					m_Map[nextTile.m_PosI][nextTile.m_PosJ].m_Flag = true;

					//애니메이션 재생을 위한 순서와 방향 지정
					animationTurn = GetTileAnimationTurn(currentTile) + 1;
					SetAnimationState(nextTile, animationTurn, DI_UP);
				}				
			}

			//현재 타일의 오른쪽 확인
			if (m_Map[currentTile.m_PosI][currentTile.m_PosJ + 1].m_Type == MO_LINE_UNCONNECTED)
			{
				nextTile.m_PosI = currentTile.m_PosI;
				nextTile.m_PosJ = currentTile.m_PosJ + 2;
				if (!IsAlreadyChecked(nextTile) )
				{
					searchTiles.push(nextTile);
					m_ClosedTile[i++] = nextTile;
					m_Map[nextTile.m_PosI][nextTile.m_PosJ].m_Flag = true;

					//애니메이션 재생을 위한 순서와 방향 지정
					animationTurn = GetTileAnimationTurn(currentTile) + 1;
					SetAnimationState(nextTile, animationTurn, DI_RIGHT);
				}				
			}

			//현재 타일의 아래쪽 확인
			if (m_Map[currentTile.m_PosI + 1][currentTile.m_PosJ].m_Type == MO_LINE_UNCONNECTED)
			{
				nextTile.m_PosI = currentTile.m_PosI + 2;
				nextTile.m_PosJ = currentTile.m_PosJ;
				if (!IsAlreadyChecked(nextTile) )
				{
					searchTiles.push(nextTile);
					m_ClosedTile[i++] = nextTile;
					m_Map[nextTile.m_PosI][nextTile.m_PosJ].m_Flag = true;

					//애니메이션 재생을 위한 순서와 방향 지정
					animationTurn = GetTileAnimationTurn(currentTile) + 1;
					SetAnimationState(nextTile, animationTurn, DI_DOWN);
				}				
			}

			//현재 타일의 왼쪽 확인
			if (m_Map[currentTile.m_PosI][currentTile.m_PosJ - 1].m_Type == MO_LINE_UNCONNECTED)
			{
				nextTile.m_PosI = currentTile.m_PosI;
				nextTile.m_PosJ = currentTile.m_PosJ - 2;
				if (!IsAlreadyChecked(nextTile) )
				{
					searchTiles.push(nextTile);
					m_ClosedTile[i++] = nextTile;
					m_Map[nextTile.m_PosI][nextTile.m_PosJ].m_Flag = true;

					//애니메이션 재생을 위한 순서와 방향 지정
					animationTurn = GetTileAnimationTurn(currentTile) + 1;
					SetAnimationState(nextTile, animationTurn, DI_LEFT);
				}				
			}
		}

		//닫힌 타일이 있으므로 애니메이션 실행하라는 플래그 설정
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

	for (int i = 1; i < CGameLogic::GetInstance()->GetCurrentPlayerNumber(); ++i)
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
	// 방어코드 추가 : 음수이거나 MAX_PLAYER_NUM 보다 크면 리턴
	if ( characterId < 0 || characterId > MAX_PLAYER_NUM )
	{
		return false;
	}

	// Single 일 때
	// 이미 선택된 캐릭터인지 확인해서 선택되어 있다면 취소시키고 리턴
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		if ( m_PlayerData[i]->m_CharacterId == characterId 
			&& m_PlayerData[i]->m_PlayerId != -1 )
		{
			m_PlayerData[i]->m_CharacterId = -1;
			m_PlayerData[i]->m_PlayerId = -1;
			m_Character[characterId].m_isCharacterSelected = false;
			--m_CurrentPlayerNumber;

			return true;
		}
	}

	// 아직 선택되지 않은 캐릭터라면 추가해준다
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		if (m_PlayerData[i]->m_PlayerId == -1)
		{
			m_PlayerData[i]->m_PlayerId = i;
			m_PlayerData[i]->m_CharacterId = characterId;
			m_Character[characterId].m_isCharacterSelected = true;
			++m_CurrentPlayerNumber;

			return true;
		}
	}

	return true;
	// 이 밑의 코드는 안 쓴다!
	//이미 선택했던 캐릭터가 있다면 이전 캐릭터는 풀어준다.
	// 	if (m_PlayerData[playerId]->m_CharacterId != -1)
	// 	{
	// 		m_Character[m_PlayerData[playerId]->m_CharacterId].m_isCharacterSelected = false;
	// 	}
	// 	m_PlayerData[playerId]->m_CharacterId = characterId;
}

bool CGameLogic::StartGame()
{
	/*
	//////////////////////테스트용 플레이어 생성/////////////////////////////////////////////
	m_PlayerData[0]= new PlayerData();
	m_PlayerData[0]->m_CharacterId=1;
	m_PlayerData[0]->m_PlayerId=0;
	m_PlayerData[0]->m_PlayerName="아이디0";
	m_PlayerData[1]= new PlayerData();
	m_PlayerData[1]->m_CharacterId=0;
	m_PlayerData[1]->m_PlayerId=1;
	m_PlayerData[1]->m_PlayerName="아이디1";
	m_PlayerData[2]= new PlayerData();
	m_PlayerData[2]->m_CharacterId=3;
	m_PlayerData[2]->m_PlayerId=2;
	m_PlayerData[2]->m_PlayerName="아이디2";
	m_PlayerNumber=3;
	///////////////////////////////////////////////////////////////////////////////////////////
	*/
	// 턴 생성 & 플레이어별로 턴 저장

	//순서를 바꾼 후
	std::array<int,4> tempTurn = {0, 1, 2, 3};
	srand( static_cast<unsigned int>(time(NULL)) );
	std::random_shuffle(tempTurn.begin(), tempTurn.end());

	PlayerData* current;
	int tempT = 0;
	for (int i = 0; i < MAX_PLAYER_NUM; ++i)
	{
		if (m_PlayerData[i]->m_PlayerId == -1)
			continue;

		while (tempTurn[tempT] >= m_CurrentPlayerNumber)
			++tempT;

		m_PlayerData[i]->m_PlayerTurn = tempTurn[tempT];

		if (tempTurn[tempT] == 0)
			current = m_PlayerData[i];

		++tempT;
	}

	//일단 current를 찾고, current->playerTurn + 1인 tempPlayer를 찾고
	//current->next = tempPlayer
	//current = tempPlayer
	//다시 반복

	//이제 링크드 리스트를 만들어주자!
	m_FirstPlayer = current;

	for (int i = 0; i < m_CurrentPlayerNumber; i++)
	{
		for (int j = 0; j < m_CurrentPlayerNumber; ++j)
		{
			if (m_PlayerData[i]->m_PlayerTurn+1 == m_PlayerData[j]->m_PlayerTurn)
				m_PlayerData[i]->m_nextPlayer = m_PlayerData[j];
		}

		if (m_PlayerData[i]->m_nextPlayer == nullptr)
			tempT = i;
	}

	m_PlayerData[tempT]->m_nextPlayer = m_FirstPlayer;

	CCLOG("player number : %d", m_CurrentPlayerNumber);



// 	for (int i = 0 ; i < MAX_PLAYER_NUM; ++i)
// 	{
// 		// PlayerId가 -1이 아닐 경우에만 TurnList에 랜덤한 순서로 넣어준다.
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

	// 맵 생성
	CreateMap();

	// 맵에 랜덤으로 선, 아이템 뿌리기 (크기 반영)
	InitRandomMap();

	return true;
}

void CGameLogic::CreateMap()
{
	/*	실제로 게임에 사용되는 타일 외에도 울타리와 점을 표시하기 위한 칸도 필요
	생성된 게임 주변은 기본값인 MO_SENTINEL로 두어서 IsClosed()와 같은 작업시 활용할 수 있도록 함 */
	int targetRow, targetColumn;

	MapSize mapSize;

	// MapSelect에서 MapSize를 만들어 낸다
	switch (m_SelectedMapSize)
	{
	case MS_5X5:
		mapSize.m_Width = 5;
		mapSize.m_Height = 5;
		break;
	case MS_8X8:
		mapSize.m_Width = 8;
		mapSize.m_Height = 8;
		break;
	default:
		// 조심해!! 방어코드를 넣어야해!! 여기 들어오면 뭔가 잘못된거다
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
	// 울타리, 고기, 독약 갯수를 위한 변수들
	int startLineNumber = 0;
	int startGoldNumber = 0;
	int startTrashNumber = 0;

	switch (m_SelectedMapSize)
	{
	case MS_5X5: 
		startLineNumber = 13;
		startGoldNumber = 5;
		startTrashNumber = 4;
		break;
	case MS_8X8:
		startLineNumber = 27;
		startGoldNumber = 8;
		startTrashNumber = 7;
		break;
	default:
		break;
	}

	// IsClosed에서 사용할 변수들입니다.
	IndexedPosition RandomTargetPosition;

	// 고정적인 시드값이 필요할 경우 아래 시드를 써보시기 바랍니다.
	//srand(1383706550);

	// 울타리를 뿌려주는 함수입니다.
	while (startLineNumber)
	{
		// 울타리는 (2,1), (1,2) 부터 시작하므로
		RandomTargetPosition.m_PosI = rand() % MAX_MAP_HEIGHT;
		RandomTargetPosition.m_PosJ = rand() % MAX_MAP_WIDTH;

		// 랜덤 값으로 뽑은 좌표가 MO_LINE_UNCONNECTED일 경우에
		if ( GetMapType(RandomTargetPosition) == MO_LINE_UNCONNECTED )
		{
			// IsPossible을 만족하면
			if ( IsPossible(RandomTargetPosition) )
			{
				// 일단 그립니다(IsClosed 검사를 위해서)
				//printf("random %d , %d\n",RandomTargetPosition.m_PosI,RandomTargetPosition.m_PosJ);
				DrawLine(RandomTargetPosition);
				--startLineNumber;

				// 지금 막 그려진 선이 IsClosed() 조건을 만족하지 않으면 그대로 종료
				if ( IsClosed(RandomTargetPosition) )
				{
					// 만약 지금 막 그려진 선이 어떤 도형을 닫는다면 해당 선을 삭제하고 라인 카운터를 복구
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
	// 범위를 벗어난 경우 예외 처리
	assert(indexedPosition.m_PosI < MAX_MAP_WIDTH && indexedPosition.m_PosJ < MAX_MAP_HEIGHT) ;

	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Type = MO_LINE_CONNECTED;

	//animaiton start
	m_LineAnimationFlag = true;
	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_AnimationFlag = true;
}

void CGameLogic::DeleteLine( const IndexedPosition& indexedPosition )
{
	// 범위를 벗어난 경우 예외 처리
	assert(indexedPosition.m_PosI < MAX_MAP_WIDTH && indexedPosition.m_PosJ < MAX_MAP_HEIGHT) ;

	//랜덤 라인 긋는 과정에서의 애니메이션 상태 변화 되돌리기
	for (int tempI = 0 ; tempI < MAX_MAP_WIDTH; ++tempI)
	{
		for (int tempJ = 0 ; tempJ < MAX_MAP_HEIGHT; ++tempJ)
		{
			SetMapFlag(IndexedPosition(tempI, tempJ), false);

			if (GetMapType(IndexedPosition(tempI, tempJ) ) == MO_TILE)
			{
				//애니메이션 재생을 위한 데이터도 초기화
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

	//IsPossible 체크 후에 일단 그리고 나서 닫힌 여부 체크
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
			MO_OWNER currentId = (MO_OWNER)GetPlayerIdByTurn(m_currentTurn % m_CurrentPlayerNumber);
			//본래 타일에 뭐가 있었는지 확인해서 각자 바꿀 것!!
			m_Map[m_ClosedTile[i].m_PosI][m_ClosedTile[i].m_PosJ].m_Owner = currentId;
			--m_VoidTileCount;

			//점수 추가 해 줄 것
			int score = 0;
			switch (m_Map[m_ClosedTile[i].m_PosI][m_ClosedTile[i].m_PosJ].m_Item)
			{
			case ITEM_NOTHING:
				score = SC_RT_SCORE_TILE;
				UpdatePlayerResult(currentId,ITEM_NOTHING);
				break;
			case ITEM_GOLD:
				score = SC_RT_SCORE_GOLD;
				UpdatePlayerResult(currentId,ITEM_GOLD);
				break;
			case ITEM_TRASH:
				score = SC_RT_SCORE_TRASH;
				UpdatePlayerResult(currentId,ITEM_TRASH);
				break;
			default:
				break;
			}
			UpdatePlayerScore(currentId,score);

			i++;
		}
	}

	++m_currentTurn;

	return true;
}

int CGameLogic::GetPlayerIdByTurn( int currentTurn )
{
	PlayerData* currentPlayer = m_FirstPlayer;
	for (int i = 0;i<currentTurn;i++)
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

bool CGameLogic::TimeOut()
{
	//주어진 시간을 초과하면 랜덤으로 선을 그어버린다.

	IndexedPosition RandomTargetPosition;

	//random line creation
	while (true)
	{
		// 울타리는 (2,1), (1,2) 부터 시작하므로
		RandomTargetPosition.m_PosI = rand() % MAX_MAP_HEIGHT; 
		RandomTargetPosition.m_PosJ = rand() % MAX_MAP_WIDTH;

		// 랜덤 값으로 뽑은 좌표가 MO_LINE_UNCONNECTED일 경우에
		if ( GetMapType(RandomTargetPosition) == MO_LINE_UNCONNECTED )
		{
			if ( IsPossible(RandomTargetPosition) )
			{
				return EventHandle(RandomTargetPosition);
			}
		}
	}
}

bool CGameLogic::IsPlayerJoinedGame( int playerId )
{
	// playerId :: ( 0 <= ~ < MAX_PLAYER_NUM )
	if (playerId < MAX_PLAYER_NUM && playerId >= 0)
	{
		if ( -1 == m_PlayerData[playerId]->m_PlayerId )
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	// err
	return false;
}
