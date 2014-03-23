#pragma once
#include "cocos2d.h"

class CTutorialBoardLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
    
    void ccTouchesBegan(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent);
	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ShowNextAnimation(int num);
    void ShowTimerAnimation();
    void ShowDrawAnimation();
    void ShowLandAnimation();
    
	// implement the "static node()" method manually
    CREATE_FUNC(CTutorialBoardLayer);
private:
    int m_clickedNum;
};

