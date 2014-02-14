#pragma once
#include "cocos2d.h"
#include "config.h"


class CMO_item : public cocos2d::CCSprite
{
public:
	virtual bool init();
	virtual void update(float delta);

	void setImage(IndexedPosition indexedPosition);

	CREATE_FUNC(CMO_item);

private:
	cocos2d::CCSprite*	pItem;

};


