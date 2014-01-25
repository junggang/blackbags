#pragma once
#include "CMO_dot.h"

USING_NS_CC;

CMO_dot::CMO_dot()
{
}

CMO_dot::~CMO_dot()
{

}

CMO_dot* CMO_dot::create(const char* pszFileName, const CCRect& rect)
{
	CMO_dot* pSprite = new CMO_dot();
	if (pSprite && pSprite->initWithFile(pszFileName, rect))
	{
		pSprite->autorelease();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

CMO_dot* CMO_dot::Create()
{
	CMO_dot* pMapObejct = CMO_dot::create("image/MO_dot.png", CCRectMake(0.0f, 0.0f, 10.0f,  10.0f));

	return pMapObejct;
}

void CMO_dot::update( float delta )
{
	//아무것도 안 함
}
