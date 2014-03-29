#include "CMO_dot.h"

USING_NS_CC;

CMO_dot::CMO_dot()
{
}

CMO_dot::~CMO_dot()
{

}

CMO_dot* CMO_dot::create(const char* pszFileName)
{
	CMO_dot* pSprite = new CMO_dot();
	if (pSprite && pSprite->initWithFile(pszFileName))
	{
		pSprite->autorelease();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

CMO_dot* CMO_dot::Create()
{
	CMO_dot* pMapObejct = CMO_dot::create(PLAYSCENE_DOT.c_str());
	return pMapObejct;
}

void CMO_dot::update( float delta )
{
	//아무것도 안 함
}
