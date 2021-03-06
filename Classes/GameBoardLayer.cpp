#include "GameBoardLayer.h"
#include "GameManager.h"
#include "CMO_tile.h"
#include "CMO_dot.h"
#include "CMO_line.h"
#include "CMO_item.h"
#include "CMO_score.h"

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

    switch (CGameManager::GetInstance()->GetSelectedMapSize() )
	{
	case MS_5X5:
		m_RowNum = 5;
		m_ColNum = 5;
		break;
	case MS_6X6:
		m_RowNum = 6;
		m_ColNum = 6;
		break;
	case MS_7X7:
		m_RowNum = 7;
		m_ColNum = 7;
		break;
	default:
        m_RowNum = 0;
        m_ColNum = 0;
		break;
	}
    
    m_Board = CCSprite::create(
		PLAYSCENE_BOARD.c_str(), 
		CCRect(0, 0, m_ColNum * DEFAULT_TILE_WIDTH, m_RowNum * DEFAULT_TILE_HEIGHT)
		);
	m_Board->setAnchorPoint(ccp(0.5f, 0.5f));
	m_Board->setPosition(ccp(m_VisibleSize.width / 2, m_VisibleSize.height / 2) );
	this->addChild(m_Board);

	m_BoardOrigin.x = m_VisibleSize.width/2 - (float(m_ColNum)/2 * DEFAULT_TILE_WIDTH);
	m_BoardOrigin.y = m_VisibleSize.height/2;	

	float m_OriginX = 0.0f;
	float m_OriginY = m_Board->getContentSize().height/2;

	float m_LineOriginX = m_OriginX;
	float m_LineOriginY = m_OriginY;

	float m_DeltaX = DEFAULT_TILE_WIDTH/2;
	float m_DeltaY = DEFAULT_TILE_HEIGHT/2;

	for (int i = 1; i < m_RowNum * 2 + 2; ++i)
	{
		for (int j = 1; j < m_ColNum * 2 + 2; ++j)
		{
			IndexedPosition pos;
			pos.m_PosI = i;
			pos.m_PosJ = j;

			//«‡, ø≠ ∏µŒ ¬¶ºˆ ¿œ ∞ÊøÏ ≈∏¿œ¿ª ±◊∏∞¥Ÿ.
			if ( i % 2 == 0 && j % 2 == 0)
			{
				CMO_tile* pTile = CMO_tile::create();
				pTile->setImage(pos);
				pTile->setPosition(ccp(m_OriginX+m_DeltaX*(j/2-1),m_OriginY+m_DeltaY*(j/2-1)));

				m_Board->addChild(pTile, 0);
                
                //add score layer : 아이템 레이어 보다 상위에 있어야 해서 레이어 따로 뺌.
                CMO_score* pScore = CMO_score::create();
                pScore->setImage(pos);
                pScore->setPosition(ccp(m_OriginX+m_DeltaX*(j/2-1),m_OriginY+m_DeltaY*(j/2-1)));
                m_Board->addChild(pScore, 6);
                
                //add item
                if (CGameManager::GetInstance()->GetItem(IndexedPosition(i,j))!= ITEM_NOTHING)
                {
                    CMO_item* pItem = CMO_item::create();
                    pItem->setImage(IndexedPosition(i,j));
                    pItem->setPosition( ccp(m_OriginX+m_DeltaX*(j/2-1),m_OriginY+m_DeltaY*(j/2-1)) );
                    m_Board->addChild(pItem, 5);
                }
                
			}
			// «‡, ø≠ ∏µŒ »¶ºˆ¿œ ∞ÊøÏ ¥Â¿ª ±◊∏∞¥Ÿ.
			else if ( i % 2 == 1 && j % 2 == 1)
			{
				CMO_dot* pDot = CMO_dot::Create();
				pDot->setPosition( ccp( m_OriginX+m_DeltaX*(j/2),m_OriginY+m_DeltaY*(j/2) ) );

				m_Board->addChild(pDot, 2);
			}
			
			//±◊ ø‹ø°¥¬ º±¿Ã¥Ÿ.(i¬¶ºˆ/j»¶ºˆ ∂«¥¬ i»¶ºˆ/j¬¶ºˆ)
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
    Highlight(m_StartPoint, 1);
	CCLog("Start point =  %f, %f", m_StartPoint.x,m_StartPoint.y);

}

void CGameBoardLayer::ccTouchesMoved(CCSet* pTouches, cocos2d::CCEvent* pEvent)
{
    CCTouch *pTouch = (CCTouch*)pTouches->anyObject();
    m_middlePoint = pTouch->getLocationInView();
    CCLog("Middle point =  %f, %f", m_middlePoint.x,m_middlePoint.y);

    Highlight(m_middlePoint, 0);
}

void CGameBoardLayer::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
	CCTouch *pTouch = (CCTouch*)pTouches->anyObject();

	m_EndPoint  = pTouch->getLocationInView();
	CCLog("End point =  %f, %f", m_EndPoint.x,m_EndPoint.y);
    removeChildByTag(0);
    removeChildByTag(1);
    removeChildByTag(3);
	DrawLine();
}

void CGameBoardLayer::DrawLine()
{
    
	IndexedPosition startIndex = ConvertCoordinate(m_StartPoint);
	IndexedPosition endIndex = ConvertCoordinate(m_EndPoint);
    
    CCLog("%d,%d",m_RowNum,m_ColNum);
    
    //마름모 범위를 벗어날 경우, 그냥 종료
    if ( ( startIndex.m_PosI <= 0 ) ||
        ( startIndex.m_PosJ <=0 ) ||
        ( startIndex.m_PosI > ( m_RowNum * 2 ) + 1 ) ||
        ( startIndex.m_PosJ > ( m_ColNum * 2 ) + 1 ) )
    {
        CCLog("bad position");
        return;
    }
	
	if (startIndex.m_PosI == endIndex.m_PosI)
	{
		if (endIndex.m_PosJ - startIndex.m_PosJ == 2)
		{
			CGameManager::GetInstance()->DrawLine( IndexedPosition(startIndex.m_PosI, endIndex.m_PosJ - 1) );
			m_LineDirection = DI_UP;
            
            return;
		}
		else if (startIndex.m_PosJ - endIndex.m_PosJ == 2)
		{
			CGameManager::GetInstance()->DrawLine( IndexedPosition(startIndex.m_PosI, startIndex.m_PosJ - 1) );
			m_LineDirection = DI_DOWN;
            
            return;
		}
	}
	else if (startIndex.m_PosJ == endIndex.m_PosJ)
	{
		if (endIndex.m_PosI - startIndex.m_PosI == 2)
		{
			CGameManager::GetInstance()->DrawLine( IndexedPosition(endIndex.m_PosI - 1, startIndex.m_PosJ) );
			m_LineDirection = DI_DOWN;
            
            return;
		}
		else if (startIndex.m_PosI - endIndex.m_PosI == 2)
		{
			CGameManager::GetInstance()->DrawLine( IndexedPosition(startIndex.m_PosI - 1, startIndex.m_PosJ) );
			m_LineDirection = DI_UP;
            
            return;
		}
	}
    
    return;
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
		point.x < - TOUCH_AREA ||
		point.y > m_Board->getContentSize().height/2 + TOUCH_AREA ||
		point.y < -m_Board->getContentSize().height/2 - TOUCH_AREA)
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

void CGameBoardLayer::Highlight(cocos2d::CCPoint point,int isClicked)
{
    //Dot에 해당하는지 검사.
    //마우스 오버시 무조건 highlight, 클릭된 것은 클릭이 끝날 때 까지 highlight 유지.
    
    IndexedPosition indexedPosition = ConvertCoordinate(point);
    point.y = m_VisibleSize.height - point.y - m_BoardOrigin.y;
	point.x -= m_BoardOrigin.x;
    
    // convert는 그냥 변환만 하고
    // 유효성 검증을 그 값을 이용하는 곳에서 할 것
    // 바로 여기서!!!!
    // 마름모 범위를 벗어날 경우, 그냥 종료
    
    CCLog("I : %d, J : %d", indexedPosition.m_PosI, indexedPosition.m_PosJ );
    
    if ( ( indexedPosition.m_PosI <= 0 ) ||
        ( indexedPosition.m_PosJ <= 0 ) ||
        ( indexedPosition.m_PosI > ( m_RowNum * 2 ) + 1 ) ||
        ( indexedPosition.m_PosJ > ( m_ColNum * 2 ) + 1 ) )
    {
        return;
    }
    
    //범위를 벗어날 경우. 그냥 종료.
	if ( point.x > m_Board->getContentSize().width + TOUCH_AREA ||
		point.x< - TOUCH_AREA||
		point.y > m_Board->getContentSize().height/2 + TOUCH_AREA ||
		point.y < -m_Board->getContentSize().height/2- TOUCH_AREA)
	{
		return;
	}
    
    ///
    if(getChildByTag(0)!=nullptr)
    {
        removeChildByTag(0);
    }
    
    //line
    if( isClicked == 0 )
    {
        // 방어코드 추가
        // 일단 이걸로 죽는 현상은 없어짐
        if ( getChildByTag( 3 ) == nullptr)
            return;
        
        /*
        // 무슨 코드인지 잘 모르겠어요
        // getChildByTag(3)를 아래에서 사용하는데 nullptr 체크해서 있으면 삭제(주석이 되어 있긴 하지만) -> 아래에서 nullptr에 접근하는 거 아닌가?
        if( getChildByTag(3) != nullptr)
        {
            //removeChildByTag(3);
        }
        */
        
        float scaleFactor = sqrt(powf(m_middlePoint.x-m_StartPoint.x,2)+powf(m_middlePoint.y-m_StartPoint.y,2));
        
        if (scaleFactor >= (DEFAULT_TILE_DIAGONAL+TOUCH_AREA))
        {
            getChildByTag(3)->setScaleX(0);
        }
        else if (scaleFactor >= DEFAULT_TILE_DIAGONAL)
        {
            getChildByTag(3)->setScaleX(DEFAULT_TILE_DIAGONAL);
        }
        else
        {
            getChildByTag(3)->setScaleX(sqrt(powf(m_middlePoint.x-m_StartPoint.x,2)+powf(m_middlePoint.y-m_StartPoint.y,2)));
        }
        
        //angle direction
        //좌표 원점이 왼쪽상단임을 잊지말것
        if(m_middlePoint.x>m_StartPoint.x && m_middlePoint.y>m_StartPoint.y)
        {
            getChildByTag(3)->setRotation(33.0f);
        }
        else if(m_middlePoint.x<m_StartPoint.x && m_middlePoint.y>m_StartPoint.y)
        {
            getChildByTag(3)->setRotation(147.0f);
        }
        else if(m_middlePoint.x<m_StartPoint.x && m_middlePoint.y<m_StartPoint.y)
        {
            getChildByTag(3)->setRotation(213.0f);
        }
        else if(m_middlePoint.x>m_StartPoint.x && m_middlePoint.y<m_StartPoint.y)
        {
            getChildByTag(3)->setRotation(327.0f);
        }

    }
    
    ///
    
    float deltaX = DEFAULT_TILE_WIDTH/2;
	float deltaY = DEFAULT_TILE_HEIGHT/2;
	
    //2. converted IndexPosition이 Dot에 해당하는지 검사.
    if(indexedPosition.m_PosI%2==1 && indexedPosition.m_PosJ%2 ==1)
    {
        //고쳐라.
        if(isClicked == 0 && (abs(indexedPosition.m_PosI-ConvertCoordinate(m_StartPoint).m_PosI)+abs(indexedPosition.m_PosJ-ConvertCoordinate(m_StartPoint).m_PosJ))>2 )
        {
            return;
        }
        
        CCPoint tempP;
        //시작점
        tempP.x = m_BoardOrigin.x + (indexedPosition.m_PosI/2) * deltaX;
        tempP.y = m_BoardOrigin.y - (indexedPosition.m_PosI/2) * deltaY;
        
        tempP.x += deltaX * (indexedPosition.m_PosJ/2) ;
        tempP.y += deltaY * (indexedPosition.m_PosJ/2) ;
        
        
        CCSprite* pHighlight = CCSprite::create("image/playscene_dot_highlight.png");
        
        pHighlight->setPosition(tempP);
        pHighlight->setTag(isClicked);
        addChild(pHighlight,4);
        
        //line
        if (isClicked==1)
        {
            removeChildByTag(3);
            CCSprite * lineHighlight = CCSprite::create();
            lineHighlight->setTextureRect(CCRectMake(0, 0, 1, 25));
            lineHighlight->setColor(ccc3(192,41,20));
            lineHighlight->setPosition(tempP);
            lineHighlight->setAnchorPoint(ccp(0,0.5));
            lineHighlight->setTag(3);
            addChild(lineHighlight,3);
        }

    }
    return;
	
}

void CGameBoardLayer::update(float dt)
{
	//ø©±‚º≠ childµÈ¿ª æ˜µ•¿Ã∆Æ «ÿæﬂ «’¥œ¥Ÿ.
	//CCLog("1111 Board layer updated");
	CCArray* mapObjects = m_Board->getChildren();

	unsigned int objectNum = mapObjects->count();
	for (unsigned int i = 0; i < objectNum; ++i)
	{
		mapObjects->objectAtIndex(i)->update(dt);
	}
	
}