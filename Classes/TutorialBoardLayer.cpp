#include "TutorialBoardLayer.h"
#include "GameManager.h"
#include "MainScene.h"
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
    ShowNextAnimation(m_clickedNum);
    m_clickedNum++;
    
}

void CTutorialBoardLayer::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
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
            removeChildByTag(9);
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
            removeChildByTag(10);
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
        case 9:
            if (CGameManager::GetInstance()->GetSeenFirstTutorialFlag())
            {
                CCDirector::sharedDirector()->popScene();
            }
            else
            {
                // 지금 막 첫 튜토리얼을 다 봤으므로 플래그 바꾸고 메인씬 호출
                CGameManager::GetInstance()->SetSeenFirstTutorialFlag(true);
                
                CCScene* newScene = CMainScene::create();
                CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );

            }
            break;
            
    }
}

void CTutorialBoardLayer::ShowTimerAnimation()
{
    //
    CCSpriteBatchNode* spritebatch = CCSpriteBatchNode::create(TUTORIAL_ANI_TIMER.c_str());
    //
    
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
    spritebatch->addChild(pTimer);
    spritebatch->setTag(9);
    addChild(spritebatch,3);
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames,0.3f);
    //CCAction* myTimer = CCAnimate::create(animation);
    
    CCRepeatForever* repeatAction = CCRepeatForever::create(CCAnimate::create(animation));
    
    pTimer->runAction(repeatAction);
    
}
void CTutorialBoardLayer::ShowDrawAnimation()
{
    //
    CCSpriteBatchNode* spritebatch = CCSpriteBatchNode::create(TUTORIAL_ANI_DRAW.c_str());
    //
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile(TUTORIAL_ANI_DRAW_PLIST.c_str());
    
    
    CCArray* animFrames = CCArray::createWithCapacity(60);
    
    char str[100] = {0};
    for(int i = 1; i < 61; i++)
    {
        sprintf(str, "tutorial_animation_draw_000%02d.png", i);
        CCSpriteFrame* frame = cache->spriteFrameByName( str );
        animFrames->addObject(frame);
    }
    
    CCSprite *pElement = CCSprite::createWithSpriteFrameName("tutorial_animation_draw_00001.png");
    pElement->setPosition( CCPoint(TUTORIAL_DRAW_ANIMATION_POS) );
    pElement->setAnchorPoint(ccp(0,0));
    spritebatch->addChild(pElement);
    spritebatch->setTag(10);
    addChild(spritebatch,3);
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames,0.1f);
    //CCAction* myTimer = CCAnimate::create(animation);
    
    CCRepeatForever* repeatAction = CCRepeatForever::create(CCAnimate::create(animation));
    
    pElement->runAction(repeatAction);
}
void CTutorialBoardLayer::ShowLandAnimation()
{
    //
    CCSpriteBatchNode* spritebatch = CCSpriteBatchNode::create(TUTORIAL_ANI_LAND.c_str());
    //
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile(TUTORIAL_ANI_LAND_PLIST.c_str());
    
    
    CCArray* animFrames = CCArray::createWithCapacity(26);
    
    char str[100] = {0};
    for(int i = 1; i < 27; i++)
    {
        sprintf(str, "tutorial_animation_land_000%02d.png", i);
        CCSpriteFrame* frame = cache->spriteFrameByName( str );
        animFrames->addObject(frame);
    }
    
    CCSprite *pElement = CCSprite::createWithSpriteFrameName("tutorial_animation_land_00001.png");
    pElement->setPosition( CCPoint(TUTORIAL_DRAW_ANIMATION_POS) );
    pElement->setAnchorPoint(ccp(0,0));
    spritebatch->addChild(pElement);
    spritebatch->setTag(11);
    addChild(spritebatch,3);
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames,0.1f);
    //CCAction* myTimer = CCAnimate::create(animation);
    
    CCAction* repeatAction = CCAnimate::create(animation);
    
    pElement->runAction(repeatAction);
}
