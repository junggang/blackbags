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
    m_isTaken = false;
    return true;
}

void CMO_score::setImage(IndexedPosition indexedPosition)
{
	m_Index = indexedPosition;
}

void CMO_score::update( float delta )
{
    MO_ITEM tempItem = CGameManager::GetInstance()->GetItem(m_Index);
    MO_OWNER tempOwner = CGameManager::GetInstance()->GetMapOwner(m_Index);
    if(tempOwner != MO_NOBODY && m_isTaken==false)
    {
        // 애니메이션이 시작하는 시간은 라인이 재생되는 시간 + 인덱스가 낮은 타일들이 모두 그려지는 시간(애니메이션이 있는 타일은 인덱스 1부터 시작하므로 자신의 인덱스에서 1을 빼서 재생시간 곱함)
        float delayTime = PLAYSCENE_ANIMATION_TIME + PLAYSCENE_ANIMATION_TIME * (CGameManager::GetInstance()->GetTileAnimationTurn(m_Index) - 1);
        
        // 애니메이션이 끝나는 시간을 지정함
		CGameManager::GetInstance()->SetAnimationDelay(delayTime);
        
		CCDelayTime *dt = CCDelayTime::create(delayTime);
        m_isTaken = true;
        
        pScore = CCSprite::create(PLAYSCENE_SCORE_LAND.c_str());
        
        //점수 애니메이션 부분
        
        CCFadeOut* FadeOut = CCFadeOut::create(0.8f);
        CCMoveBy* actionBy = CCMoveBy::create(0.8f, ccp(0.0f,80.0f));
        CCAction* simul = CCSequence::create(dt,FadeOut,NULL);
        //CCAction *Fadeactions = CCSequence::create(dt, FadeOut, NULL);
        pScore->setOpacity(0);
        pScore->setAnchorPoint( ccp(0, 0.5f) );
        pScore->runAction(simul);
        
        CCAction* simul1 = CCSequence::create(dt,actionBy,NULL);
        pScore->runAction(simul1);
        
        addChild(pScore,1);
        
        if (tempItem != ITEM_NOTHING)
        {
            CCSprite* pItem = CCSprite::create();
            
            switch (tempItem) {
                case ITEM_GOLD:
                    pItem = CCSprite::create(PLAYSCENE_SCORE_CAKE.c_str());
                    break;
                case ITEM_TRASH:
                    pItem = CCSprite::create(PLAYSCENE_SCORE_TRASH.c_str());
                    break;
                default:
                    CCLog("FAILED TO LOAD ITEM TEXTURE");
                    return;
            }
            
            
            CCDelayTime *dtItem = CCDelayTime::create(delayTime+0.4f);
            
            CCFadeOut* FadeOutItem = CCFadeOut::create(0.8f);
            CCMoveBy* actionByItem = CCMoveBy::create(0.8f, ccp(0.0f,80.0f));
            CCAction* simulItem = CCSequence::create(dtItem,FadeOutItem,NULL);
            //CCAction *Fadeactions = CCSequence::create(dt, FadeOut, NULL);
            
            pItem->setOpacity(0);
            pItem->setAnchorPoint( ccp(0, 0.5f) );
            pItem->runAction(simulItem);
            
            CCAction* simulItem1 = CCSequence::create(dtItem,actionByItem,NULL);
            pItem->runAction(simulItem1);
            addChild(pItem,1);


        }
        
 
    }
    
}