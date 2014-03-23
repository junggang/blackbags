#include "TutorialBoardLayer.h"

#include "config.h"

USING_NS_CC;

bool CTutorialBoardLayer::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    m_clickedNum = 0;
    
    //1.add tutorial board
    CCSprite* board = CCSprite::create(TUTORIAL_BOARD.c_str());
    board->setAnchorPoint(ccp(0,0));
    board->setPosition(CCPoint(TUTORIAL_BOARD_POS));
    addChild(board,1);
    
    //2.add fixed timer image
    CCSprite* timer = CCSprite::create(TUTORIAL_TIMER.c_str());
    timer->setAnchorPoint(ccp(0,0));
    timer->setPosition(CCPoint(TUTORIAL_TIMER_POS));
    addChild(timer,2);
    
    this->setTouchEnabled(true);
    
    return true;
}


void CTutorialBoardLayer::ccTouchesBegan( CCSet* pTouches, CCEvent* pEvent )
{
	CCTouch *pTouch = (CCTouch*)pTouches->anyObject();
    
    ShowNextAnimation(m_clickedNum);
    m_clickedNum++;
    
}

void CTutorialBoardLayer::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
	CCTouch *pTouch = (CCTouch*)pTouches->anyObject();
}

void CTutorialBoardLayer::ShowNextAnimation(int num)
{
    switch (num) {
        case 0:
        {
            CCSprite* text_timer0 = CCSprite::create(TUTORIAL_TEXT_TIMER0.c_str());
            text_timer0->setAnchorPoint(ccp(0,0));
            text_timer0->setPosition(CCPoint(TUTORIAL_TEXT_TIMER_POS));
            text_timer0->setTag(0);
            addChild(text_timer0,2);
            
            ShowTimerAnimation();
        }
            break;
            
        case 1:
        {
            removeChildByTag(0);
            CCSprite* text_timer1 = CCSprite::create(TUTORIAL_TEXT_TIMER1.c_str());
            text_timer1->setAnchorPoint(ccp(0,0));
            text_timer1->setPosition(CCPoint(TUTORIAL_TEXT_TIMER_POS));
            text_timer1->setTag(1);
            addChild(text_timer1,2);
        }
            break;
            
        case 2:
        {
            removeChildByTag(1);
            CCSprite* text_draw0 = CCSprite::create(TUTORIAL_TEXT_DRAW0.c_str());
            text_draw0->setAnchorPoint(ccp(0,0));
            text_draw0->setPosition(CCPoint(TUTORIAL_TEXT_DRAW_POS));
            text_draw0->setTag(2);
            addChild(text_draw0,2);
            
            ShowDrawAnimation();
        }
            break;
            
        case 3:
        {
            removeChildByTag(2);
            CCSprite* text_draw1 = CCSprite::create(TUTORIAL_TEXT_DRAW1.c_str());
            text_draw1->setAnchorPoint(ccp(0,0));
            text_draw1->setPosition(CCPoint(TUTORIAL_TEXT_DRAW_POS));
            text_draw1->setTag(3);
            addChild(text_draw1,2);
            ShowLandAnimation();
        }
            break;
            
        case 4:
        {
            removeChildByTag(3);
            CCSprite* text_score = CCSprite::create(TUTORIAL_TEXT_SCORE0.c_str());
            text_score->setAnchorPoint(ccp(0,0));
            text_score->setPosition(CCPoint(TUTORIAL_TEXT_SCORE_POS));
            text_score->setTag(4);
            addChild(text_score,2);
        }
            break;
            
        case 5:
        {
            removeChildByTag(4);
            CCSprite* text_score = CCSprite::create(TUTORIAL_TEXT_SCORE1.c_str());
            text_score->setAnchorPoint(ccp(0,0));
            text_score->setPosition(CCPoint(TUTORIAL_TEXT_SCORE_POS));
            text_score->setTag(5);
            addChild(text_score,2);
        }
            break;
            
        case 6:
        {
            removeChildByTag(5);
            CCSprite* text_score = CCSprite::create(TUTORIAL_TEXT_SCORE2.c_str());
            text_score->setAnchorPoint(ccp(0,0));
            text_score->setPosition(CCPoint(TUTORIAL_TEXT_SCORE_POS));
            text_score->setTag(6);
            addChild(text_score,2);
        }
            break;
            
        case 7:
        {
            removeChildByTag(6);
            CCSprite* text_score = CCSprite::create(TUTORIAL_TEXT_SCORE3.c_str());
            text_score->setAnchorPoint(ccp(0,0));
            text_score->setPosition(CCPoint(TUTORIAL_TEXT_SCORE_POS));
            text_score->setTag(7);
            addChild(text_score,2);
        }
            break;
            
        case 8:
        {
            removeChildByTag(7);
            CCSprite* text_menu = CCSprite::create(TUTORIAL_TEXT_MENU.c_str());
            text_menu->setAnchorPoint(ccp(0,0));
            text_menu->setPosition(CCPoint(TUTORIAL_TEXT_MENU_POS));
            text_menu->setTag(7);
            addChild(text_menu,2);
        }
            break;
            
    }
}

void CTutorialBoardLayer::ShowTimerAnimation()
{
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile(TUTORIAL_ANI_TIMER_PLIST.c_str());
    
    
    CCArray* animFrames = CCArray::createWithCapacity(18);
    
    char str[100] = {0};
    for(int i = 1; i < 19; i++)
    {
        sprintf(str, "tutorial_ani_timer_000%02d.png", i);
        CCSpriteFrame* frame = cache->spriteFrameByName( str );
        animFrames->addObject(frame);
    }
    
    CCSprite *pTimer = CCSprite::createWithSpriteFrameName("tutorial_ani_timer_00001.png");
    pTimer->setPosition( CCPoint(TUTORIAL_TIMER_POS) );
    pTimer->setAnchorPoint(ccp(0,0));
    addChild(pTimer,3);
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames);
    //CCAction* myTimer = CCAnimate::create(animation);
    
    CCRepeatForever* repeatAction = CCRepeatForever::create(CCAnimate::create(animation));
    
    pTimer->runAction(repeatAction);
    
}
void CTutorialBoardLayer::ShowDrawAnimation()
{
    
}
void CTutorialBoardLayer::ShowLandAnimation()
{
    
}
