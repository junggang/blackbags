#include "PlayerLayer.h"
#include "GameManager.h"

USING_NS_CC;

bool CPlayerLayer::init()
{
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    
	m_CurrentPlayerId = -1;
    
	m_VisibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
	//int playerNumber = CGameManager::GetInstance()->GetPlayerNumberOfThisGame();
    
    //Init setting
    //1.prepare positions for UI.
    //2.prepare wating background
    //3.set name
    
	m_UIposition[0] = CCPoint(SHARED_PLAYER_UI_UPPER_LEFT_POS);
	m_UIposition[1] = CCPoint(SHARED_PLAYER_UI_UPPER_RIGHT_POS);
	m_UIposition[2] = CCPoint(SHARED_PLAYER_UI_BELOW_LEFT_POS);
	m_UIposition[3] = CCPoint(SHARED_PLAYER_UI_BELOW_RIGHT_POS);
	
    
	for (int playerId = 0; playerId<MAX_PLAYER_NUM; ++playerId)
	{
		if (CGameManager::GetInstance()->GetCharacterIdByPlayerId(playerId) == -1)
			continue;
        
		int position = CGameManager::GetInstance()->GetPlayerTurn(playerId);
		int characterId = CGameManager::GetInstance()->GetCharacterIdByPlayerId(playerId);
        
        if ( !CGameManager::GetInstance()->IsOnlineMode() )
        {
            position = 3 - position;
            CCLog("%d",position);
        }
        
		m_BackGround[playerId] = CCSprite::create(SHARED_PLAYERUI_BG_WAIT[position].c_str());
		m_BackGround[playerId]->setAnchorPoint(ccp(0,0));
		m_BackGround[playerId]->setPosition(m_UIposition[position]);
		addChild(m_BackGround[playerId],0);
        
		
		if(CGameManager::GetInstance()->IsOnlineMode())
		{
			m_Player[playerId] = CCSprite::create(SHARED_PLAYERUI_CHARACTERS[4*position+characterId].c_str());
			
			//¿Ã∏ß¿ª µπ∑¡¡‡æﬂ«—¥Ÿ. configø° √ﬂ∞°«“ ∞Õ.
			m_PlayerName[playerId] = CCLabelTTF::create(CGameManager::GetInstance()->GetPlayerName(playerId).c_str(), GAME_FONT, 50,
                                                        CCSizeMake(400, 100), kCCTextAlignmentLeft);
			m_PlayerName[playerId]->setAnchorPoint(ccp(0,0));
			switch (position)
			{
                case 0:
                    m_PlayerName[playerId]->setPosition(ccp(m_UIposition[position].x+300.0f,m_UIposition[position].y+100.0f));
                    break;
                case 1:
                    m_PlayerName[playerId]->setPosition(ccp(m_UIposition[position].x+100.0f,m_UIposition[position].y+100.0f));
                    break;
                case 2:
                    m_PlayerName[playerId]->setPosition(ccp(m_UIposition[position].x+300.0f,m_UIposition[position].y+100.0f));
                    break;
                case 3:
                    m_PlayerName[playerId]->setPosition(ccp(m_UIposition[position].x+100.0f,m_UIposition[position].y+100.0f));
                    break;
                default:
                    break;
			}
			addChild(m_PlayerName[playerId],3);
		}
		else
		{
			m_Player[playerId] = CCSprite::create(SHARED_PLAYERUI_CHARACTERS_OFF[4*position+characterId].c_str());
            CCSprite* name = CCSprite::create(SHARED_PLAYERUI_NAME_OFF[4*position+characterId].c_str());
            name->setAnchorPoint(ccp(0,0));
            name->setPosition(m_UIposition[position]);
            addChild(name,3);
		}
		m_Player[playerId]->setAnchorPoint(ccp(0,0));
        CCLog("%d",position);
		m_Player[playerId]->setPosition(m_UIposition[position]);
		addChild(m_Player[playerId],2);
    }
    
	//«ˆ¿Á ≈œ(√ππ¯¬∞ ≈œ)∫Œ≈Õ æ÷¥œ∏ﬁ¿Ãº«¿Ã ¿Áª˝µ… ºˆ ¿÷µµ∑œ update()∏¶ «— π¯ «ÿ¡ÿ¥Ÿ.
	update(0);
    
	return true;
    
}

void CPlayerLayer::update( float dt )
{
	//before running the animation, pause all the animations of playerUi.
	if (m_CurrentPlayerId != -1)
	{
        removeChildByTag(10);
        //SetWaitingCharacters();
        m_Player[m_CurrentPlayerId]->setVisible(true);
    }
    
	m_CurrentPlayerId = CGameManager::GetInstance()->GetCurrentPlayerId();
	int position = CGameManager::GetInstance()->GetPlayerTurn(m_CurrentPlayerId);
    
    if ( !CGameManager::GetInstance()->IsOnlineMode() )
    {
        position = 3 - position;
    }
    
    
    int characterId = CGameManager::GetInstance()->GetCharacterIdByPlayerId(m_CurrentPlayerId);
    m_Player[m_CurrentPlayerId]->setVisible(false);
    
	removeChildByTag(0);
    
	CCSprite* currentTurnUI = CCSprite::create(SHARED_PLAYERUI_BG_TURN[position].c_str());
	currentTurnUI->setTag(0);
	currentTurnUI->setAnchorPoint(ccp(0,0));
	currentTurnUI->setPosition(m_UIposition[position]);
	addChild(currentTurnUI,1);
    
    
    /////////added////////////
    CCSpriteBatchNode* spritebatch;
    CCSpriteFrameCache *cache;
    if(CGameManager::GetInstance()->IsOnlineMode())
    {
        spritebatch = CCSpriteBatchNode::create(SHARED_PLAYERUI_CHARACTERS_ANI[4*position+characterId].c_str());
        cache = CCSpriteFrameCache::sharedSpriteFrameCache();
        cache->addSpriteFramesWithFile(SHARED_PLAYERUI_CHARACTERS_ANI_PLIST[4*position+characterId].c_str());
        
    }
    else
    {
        spritebatch = CCSpriteBatchNode::create(SHARED_PLAYERUI_CHARACTERS_ANI_OFF[4*position+characterId].c_str());
        cache = CCSpriteFrameCache::sharedSpriteFrameCache();
        cache->addSpriteFramesWithFile(SHARED_PLAYERUI_CHARACTERS_ANI_OFF_PLIST[4*position+characterId].c_str());
    }
    
    CCArray* animFrames = CCArray::createWithCapacity(SHARED_PLAYERUI_CHARACTERS_ANI_FRAME[characterId]);
    
    char str[100] = {0};
    for(int i = 1; i <= SHARED_PLAYERUI_CHARACTERS_ANI_FRAME[characterId]; i++)
    {
        sprintf(str, "ani_player_character0%d_0%d_000%02d.png",(characterId+1),(position+1),i);
        CCSpriteFrame* frame = cache->spriteFrameByName( str );
        animFrames->addObject(frame);
    }
    
    sprintf(str,"ani_player_character0%d_0%d_00001.png",(characterId+1),(position+1));
    CCSprite *pElement = CCSprite::createWithSpriteFrameName( str );
    pElement->setPosition( CCPoint(m_UIposition[position]) );
    pElement->setAnchorPoint(ccp(0,0));
    spritebatch->addChild(pElement);
    spritebatch->setTag(10);
    addChild(spritebatch,3);
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames,0.1f);
    CCRepeatForever* repeatAction = CCRepeatForever::create(CCAnimate::create(animation));
    
    pElement->runAction(repeatAction);
}

void CPlayerLayer::SetWaitingCharacters()
{
    //pause
	for (int playerId = 0; playerId<MAX_PLAYER_NUM;++playerId)
	{
		if (CGameManager::GetInstance()->GetCharacterIdByPlayerId(playerId)==-1)
			continue;
        
        int position = CGameManager::GetInstance()->GetPlayerTurn(playerId);
		int characterId = CGameManager::GetInstance()->GetCharacterIdByPlayerId(playerId);
        
        //online
        if(CGameManager::GetInstance()->IsOnlineMode())
        {
            m_Player[playerId] = CCSprite::create(SHARED_PLAYERUI_CHARACTERS[4*position+characterId].c_str());
        }
        
        //offline
        else
        {
            m_Player[playerId] = CCSprite::create(SHARED_PLAYERUI_CHARACTERS_OFF[4*position+characterId].c_str());
        }
        
	}
}
