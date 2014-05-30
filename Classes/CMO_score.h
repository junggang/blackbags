#pragma once
#include "cocos2d.h"
#include "config.h"

class CMO_score : public cocos2d::CCSprite
{
public:
	virtual bool init();
	virtual void update(float delta);
    
	void setImage(IndexedPosition indexedPosition);
	
	CREATE_FUNC(CMO_score);
    
private:
	IndexedPosition		m_Index;
	cocos2d::CCSprite*	pScore;
};

