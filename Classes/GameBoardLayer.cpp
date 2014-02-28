#include "GameBoardLayer.h"
#include "GameManager.h"
#include "CMO_tile.h"
#include "CMO_dot.h"
#include "CMO_line.h"
#include "CMO_item.h"

USING_NS_CC;

bool CGameBoardLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	//////////////////////////////
	// 2. add resources
	m_VisibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	int rowNum = 0;
	int columnNum = 0;

	switch (CGameManager::GetInstance()->GetSelectedMapSize() )
	{
	case MS_5X5:
		rowNum = 5;
		columnNum = 5;
		break;
	case MS_8X8:
		rowNum = 8;
		columnNum = 8;
		break;
	default:
		break;
	}

	m_Board = CCSprite::create(
		PLAYSCENE_BOARD.c_str(), 
		CCRect(0, 0, columnNum * DEFAULT_TILE_WIDTH, rowNum * DEFAULT_TILE_HEIGHT)
		);
	m_Board->setAnchorPoint(ccp(0.5f, 0.5f));
	m_Board->setPosition(ccp(m_VisibleSize.width / 2, m_VisibleSize.height / 2) );
	this->addChild(m_Board);

	m_BoardOrigin.x = m_VisibleSize.width/2 - (float(columnNum)/2 * DEFAULT_TILE_WIDTH);
	m_BoardOrigin.y = m_VisibleSize.height/2;	

	float m_OriginX = 0.0f;
	float m_OriginY = m_Board->getContentSize().height/2;

	float m_LineOriginX = m_OriginX;
	float m_LineOriginY = m_OriginY;

	float m_DeltaX = DEFAULT_TILE_WIDTH/2;
	float m_DeltaY = DEFAULT_TILE_HEIGHT/2;

	for (int i = 1; i < rowNum * 2 + 2; ++i)
	{
		for (int j = 1; j < columnNum * 2 + 2; ++j)
		{
			IndexedPosition pos;
			pos.m_PosI = i;
			pos.m_PosJ = j;

			//행, 열 모두 짝수 일 경우 타일을 그린다.
			if ( i % 2 == 0 && j % 2 == 0)
			{
				CMO_tile* pTile = CMO_tile::create();
				pTile->setImage(pos);
				pTile->setPosition(ccp(m_OriginX+m_DeltaX*(j/2-1),m_OriginY+m_DeltaY*(j/2-1)));

				m_Board->addChild(pTile, 0);
			}
			// 행, 열 모두 홀수일 경우 닷을 그린다.
			else if ( i % 2 == 1 && j % 2 == 1)
			{
				CMO_dot* pDot = CMO_dot::Create();
				pDot->setPosition( ccp( m_OriginX+m_DeltaX*(j/2),m_OriginY+m_DeltaY*(j/2) ) );

				m_Board->addChild(pDot, 2);
			}
			
			//그 외에는 선이다.(i짝수/j홀수 또는 i홀수/j짝수)
			else
			{
				CMO_line* pLine = CMO_line::create();
				pLine->setImage(pos);

				if (j%2 == 0)
					pLine->setPosition( ccp( m_LineOriginX+m_DeltaX*(j/2-1),m_LineOriginY+m_DeltaY*(j/2-1) ) );
				else
					pLine->setPosition( ccp( m_LineOriginX+m_DeltaX*(j/2),m_LineOriginY+m_DeltaY*(j/2) ) );

				m_Board->addChild(pLine, 1);

			}

		}	
		if (i%2==0)
		{
			m_OriginX += m_DeltaX;
			m_OriginY -= m_DeltaY;
		}
		else
		{
			m_LineOriginX += m_DeltaX;
			m_LineOriginY -= m_DeltaY;
		}
		}
	

	this->setTouchEnabled(true);
	
    return true;
}

void CGameBoardLayer::DrawMapObjects()
{
	
}

void CGameBoardLayer::ccTouchesBegan( CCSet* pTouches, CCEvent* pEvent )
{
	CCTouch *pTouch = (CCTouch*)pTouches->anyObject();

	m_StartPoint = pTouch->getLocationInView();
	CCLog("Start point =  %f, %f", m_StartPoint.x,m_StartPoint.y);

}

void CGameBoardLayer::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
	CCTouch *pTouch = (CCTouch*)pTouches->anyObject();

	m_EndPoint  = pTouch->getLocationInView();
	CCLog("End point =  %f, %f", m_EndPoint.x,m_EndPoint.y);
	DrawLine();
}

void CGameBoardLayer::DrawLine()
{
	IndexedPosition startIndex = ConvertCoordinate(m_StartPoint);
	IndexedPosition endIndex = ConvertCoordinate(m_EndPoint);
	
	//이제 두개를 비교합니다.
	//행이 같은 경우
	if (startIndex.m_PosI == endIndex.m_PosI)
	{
		if (endIndex.m_PosJ - startIndex.m_PosJ == 2)
		{
			CGameManager::GetInstance()->DrawLine( IndexedPosition(startIndex.m_PosI, endIndex.m_PosJ - 1) );
			m_LineDirection = DI_UP;
		}
		else if (startIndex.m_PosJ - endIndex.m_PosJ == 2)
		{
			CGameManager::GetInstance()->DrawLine( IndexedPosition(startIndex.m_PosI, startIndex.m_PosJ - 1) );
			m_LineDirection = DI_DOWN;
		}
	}
	//열이 같은 경우
	else if (startIndex.m_PosJ == endIndex.m_PosJ)
	{
		if (endIndex.m_PosI - startIndex.m_PosI == 2)
		{
			CGameManager::GetInstance()->DrawLine( IndexedPosition(endIndex.m_PosI - 1, startIndex.m_PosJ) );
			m_LineDirection = DI_DOWN;
		}
		else if (startIndex.m_PosI - endIndex.m_PosI == 2)
		{
			CGameManager::GetInstance()->DrawLine( IndexedPosition(startIndex.m_PosI - 1, startIndex.m_PosJ) );
			m_LineDirection = DI_UP;
		}
	}
}

IndexedPosition CGameBoardLayer::ConvertCoordinate(CCPoint point)
{
	//새로운 변환 함수 작성
	//각 행마다 기울기는 y = (DeltaY/DeltaX) x 로 동일하지만, y절편이 -deltaY/2만큼씩 감소한다.
	//따라서 마우스 좌표값으로 해당 행을 구한 뒤, x값을 계산하여 열을 구해낼 수 있다.

	// (0,0)을 씬의 왼쪽 아래로 옮겨온다.
	point.y = m_VisibleSize.height - point.y - m_BoardOrigin.y;
	point.x -= m_BoardOrigin.x;

	//이제 인덱스로 바꾼다.
	IndexedPosition indexedPosition;

	//먼저, 범위를 벗어났는지 확인한다.
	if ( point.x > m_Board->getContentSize().width + TOUCH_AREA ||
		point.x< - TOUCH_AREA||
		point.y > m_Board->getContentSize().height/2 + TOUCH_AREA ||
		point.y < -m_Board->getContentSize().height/2- TOUCH_AREA)
	{
		indexedPosition.m_PosI = 0;
		indexedPosition.m_PosJ = 0;
		return indexedPosition;
	}

	float deltaX = DEFAULT_TILE_WIDTH/2;
	float deltaY = DEFAULT_TILE_HEIGHT/2;
	float interceptY = 0.0f;

	float remainderX = static_cast<int>(point.x) % static_cast<int>(deltaX);
	float remainderY = static_cast<int>(point.y) % static_cast<int>(deltaY) ;

	//일단 이 아이를 다듬어야 해.

	if ( remainderX < TOUCH_AREA)
	{
		point.x -= remainderX;
	}
	else if (remainderX > deltaX - TOUCH_AREA)
	{
		point.x +=(deltaX - remainderX);
	}

	if ( abs(remainderY) < TOUCH_AREA)
	{
		if (remainderY>=0)
			point.y -= remainderY;
		else
			point.y += remainderY;
	}
	else if (abs(remainderY) > deltaY - TOUCH_AREA)
	{
		if (remainderY>=0)
			point.y +=(deltaY - remainderY);
		else
			point.y -=(deltaY + remainderY);
	}

	//y절편을 계산한다.
	interceptY = point.y - (deltaY/deltaX)*point.x;

	//행을 계산한다.
	indexedPosition.m_PosI = static_cast<int>(interceptY/-DEFAULT_TILE_HEIGHT);

	//열을 계산한다.
	indexedPosition.m_PosJ = static_cast<int>(point.x - deltaX*indexedPosition.m_PosI)/deltaX;

	//점에 해당하도록 계산한다.
	indexedPosition.m_PosI = indexedPosition.m_PosI*2+1;
	indexedPosition.m_PosJ = indexedPosition.m_PosJ*2+1;

	CCLog("CONVERTED : %d, %d",indexedPosition.m_PosI, indexedPosition.m_PosJ);

	return indexedPosition;
}


void CGameBoardLayer::update(float dt)
{
	//여기서 child들을 업데이트 해야 합니다.
	//CCLog("1111 Board layer updated");
	CCArray* mapObjects = m_Board->getChildren();

	unsigned int objectNum = mapObjects->count();
	for (unsigned int i = 0; i < objectNum; ++i)
	{
		mapObjects->objectAtIndex(i)->update(dt);
	}
	
}