#pragma once
#include "cocos2d.h"
#include "config.h"

class CAudioManager;

class CGameBoardLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	void DrawMapObjects();
	virtual void update(float dt);

	void ccTouchesBegan(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent);
    void ccTouchesMoved(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent);
	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void DrawLine();

	IndexedPosition ConvertCoordinate(cocos2d::CCPoint point);
    void Highlight(cocos2d::CCPoint point,int isClicked);

	// implement the "static node()" method manually
	CREATE_FUNC(CGameBoardLayer);

private:
	cocos2d::CCSize m_VisibleSize;
	cocos2d::CCPoint m_StartPoint;
    cocos2d::CCPoint m_middlePoint;
	cocos2d::CCPoint m_EndPoint;
	cocos2d::CCPoint m_BoardOrigin;
	cocos2d::CCSprite * m_Board;
    
    int m_RowNum;
    int m_ColNum;

	Direction m_LineDirection;
};

