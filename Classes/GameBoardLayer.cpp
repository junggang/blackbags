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

			//��, �� ��� ¦�� �� ��� Ÿ���� �׸���.
			if ( i % 2 == 0 && j % 2 == 0)
			{
				CMO_tile* pTile = CMO_tile::create();
				pTile->setImage(pos);
				pTile->setPosition(ccp(m_OriginX+m_DeltaX*(j/2-1),m_OriginY+m_DeltaY*(j/2-1)));

				m_Board->addChild(pTile, 0);
			}
			// ��, �� ��� Ȧ���� ��� ���� �׸���.
			else if ( i % 2 == 1 && j % 2 == 1)
			{
				CMO_dot* pDot = CMO_dot::Create();
				pDot->setPosition( ccp( m_OriginX+m_DeltaX*(j/2),m_OriginY+m_DeltaY*(j/2) ) );

				m_Board->addChild(pDot, 2);
			}
			
			//�� �ܿ��� ���̴�.(i¦��/jȦ�� �Ǵ� iȦ��/j¦��)
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
	
	//���� �ΰ��� ���մϴ�.
	//���� ���� ���
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
	//���� ���� ���
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
	//���ο� ��ȯ �Լ� �ۼ�
	//�� �ึ�� ����� y = (DeltaY/DeltaX) x �� ����������, y������ -deltaY/2��ŭ�� �����Ѵ�.
	//���� ���콺 ��ǥ������ �ش� ���� ���� ��, x���� ����Ͽ� ���� ���س� �� �ִ�.

	// (0,0)�� ���� ���� �Ʒ��� �Űܿ´�.
	point.y = m_VisibleSize.height - point.y - m_BoardOrigin.y;
	point.x -= m_BoardOrigin.x;

	//���� �ε����� �ٲ۴�.
	IndexedPosition indexedPosition;

	//����, ������ ������� Ȯ���Ѵ�.
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

	//�ϴ� �� ���̸� �ٵ��� ��.

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

	//y������ ����Ѵ�.
	interceptY = point.y - (deltaY/deltaX)*point.x;

	//���� ����Ѵ�.
	indexedPosition.m_PosI = static_cast<int>(interceptY/-DEFAULT_TILE_HEIGHT);

	//���� ����Ѵ�.
	indexedPosition.m_PosJ = static_cast<int>(point.x - deltaX*indexedPosition.m_PosI)/deltaX;

	//���� �ش��ϵ��� ����Ѵ�.
	indexedPosition.m_PosI = indexedPosition.m_PosI*2+1;
	indexedPosition.m_PosJ = indexedPosition.m_PosJ*2+1;

	CCLog("CONVERTED : %d, %d",indexedPosition.m_PosI, indexedPosition.m_PosJ);

	return indexedPosition;
}


void CGameBoardLayer::update(float dt)
{
	//���⼭ child���� ������Ʈ �ؾ� �մϴ�.
	//CCLog("1111 Board layer updated");
	CCArray* mapObjects = m_Board->getChildren();

	unsigned int objectNum = mapObjects->count();
	for (unsigned int i = 0; i < objectNum; ++i)
	{
		mapObjects->objectAtIndex(i)->update(dt);
	}
	
}