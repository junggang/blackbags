#include "CMO_score.h"
#include "GameManager.h"

USING_NS_CC;

bool CMO_score::init()
{
	if ( !CCSprite::init() )
    {
        return false;
    }
    
	pScore = NULL;
    return true;
}

void CMO_score::setImage(IndexedPosition indexedPosition)
{
	m_Index = indexedPosition;
}

void CMO_score::update( float delta )
{
    
    
}