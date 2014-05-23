#include "ResultScoreLayer.h"
#include "GameManager.h"
#include "MainScene.h"

USING_NS_CC;

bool CResultScoreLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	
	/////////////////////////////
	// 2. add a background image

	//score part
	int playerNum = CGameManager::GetInstance()->GetCurrentPlayerNumber();

	CCPoint position;

	//«√∑π¿ÃæÓ ºˆø° µ˚∂Û Ω√¿€ ¡°¿ª ∞ËªÍ.
	position.x = (visibleSize.width / 2) - (RESULT_BACKGROUND_WIDTH * playerNum / 2);
	position.y = RESULT_BACKGROUND_POSITION_Y;

    int tileMax, goldMax, trashMax, tileMin, goldMin, trashMin;
    tileMax = goldMax = trashMax = 0;
    tileMin = goldMin = trashMin = INTMAX_MAX;
    
    // 점수 최대 최소 구하기
    for (unsigned int i = 0; i < playerNum; ++i)
	{
        // 타일 갯수 갱신
        int eachTileNum = CGameManager::GetInstance()->GetElementCount(i, ITEM_NOTHING);
        tileMax = (eachTileNum > tileMax) ? eachTileNum : tileMax;
        tileMin = (eachTileNum < tileMin) ? eachTileNum : tileMin;
        
        // 케이크 갯수 갱신
        int eachCakeNum = CGameManager::GetInstance()->GetElementCount(i, ITEM_GOLD);
        goldMax = (eachCakeNum > goldMax) ? eachCakeNum : goldMax;
        goldMin = (eachCakeNum < goldMin) ? eachCakeNum : goldMin;
        
        // 쓰레기 갯수 갱신
        int eachTrashNum = CGameManager::GetInstance()->GetElementCount(i, ITEM_TRASH);
        trashMax = (eachTrashNum > trashMax) ? eachTrashNum : trashMax;
        trashMin = (eachTrashNum < trashMin) ? eachTrashNum : trashMin;
    }
    
    // 4는 최대 아이콘 표시 개수 - 지금은 하드코딩임
    // float tileUnit = float(tileMax - tileMin) / 4;
    float goldUnit = float(goldMax - goldMin) / 4;
    float trashUnit = float(trashMax - trashMin) / 4;
    
	for (unsigned int i = 0; i < playerNum; ++i)
	{
        int tileNum, cakeNum, trashNum;
        tileNum = cakeNum = trashNum = 0;
        
        tileNum = CGameManager::GetInstance()->GetElementCount(i, ITEM_NOTHING);
        cakeNum = CGameManager::GetInstance()->GetElementCount(i, ITEM_GOLD);
        trashNum = CGameManager::GetInstance()->GetElementCount(i, ITEM_TRASH);
        
		// background
		CCSprite* pBackgorund = CCSprite::create(RESULT_BACKGROUND_IMAGE[i].c_str());
		pBackgorund->setAnchorPoint(ccp(0, 0) );
		pBackgorund->setPosition(ccp(position.x, position.y) );
		addChild(pBackgorund, 0);

		// character
		int characterId = CGameManager::GetInstance()->GetCharacterIdByPlayerId(i);
		CCSprite* pFace;
		//Ω¬∆– ø©∫Œø° µ˚∂Û ƒ≥∏Ø≈Õ ¿ÃπÃ¡ˆ ª˝º∫
		if ( CGameManager::GetInstance()->IsWinner(i) )
			pFace = CCSprite::create(RESULT_CHARACTER_WIN_IMAGE[characterId].c_str());
		else
			pFace = CCSprite::create(RESULT_CHARACTER_LOSE_IMAGE[characterId].c_str());

		pFace->setAnchorPoint(ccp(0.5,0) );
		pFace->setPosition(ccp(position.x + RESULT_CHARACTER_IMAGE_POSITION_X_MARGIN, position.y + RESULT_CHARACTER_IMAGE_POSITION_Y_MARGIN));
		addChild(pFace,1);
        
        //winner flag
        if ( CGameManager::GetInstance()->IsWinner(i) )
        {
            CCSpriteBatchNode* spritebatch = CCSpriteBatchNode::create(RESULT_WINNER.c_str());
            CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
            cache->addSpriteFramesWithFile(RESULT_WINNER_PLIST.c_str());
            
            
            CCArray* animFrames = CCArray::createWithCapacity(7);
            
            char str[100] = {0};
            
            for(int i = 1; i < 8; i++)
            {
                sprintf(str, "result_winner_ani_000%02d.png", i);
                
                CCSpriteFrame* frame = cache->spriteFrameByName( str );
                animFrames->addObject(frame);
            }
            
            CCSprite*pWinner = CCSprite::createWithSpriteFrameName("result_winner_ani_00001.png");
            pWinner->setAnchorPoint(ccp(0.5,0));
            
            spritebatch->addChild(pWinner);
            addChild(spritebatch,2);

            CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames,0.3f);
            CCRepeatForever* repeatAction = CCRepeatForever::create(CCAnimate::create(animation));
            pWinner->runAction(repeatAction);
            pWinner->setPosition(ccp(position.x + RESULT_CHARACTER_IMAGE_POSITION_X_MARGIN, position.y + RESULT_CHARACTER_IMAGE_POSITION_Y_MARGIN));
        }

		//player name
		CCLabelTTF* pName = CCLabelTTF::create(CGameManager::GetInstance()->GetPlayerName(i).c_str(), GAME_FONT, 48 );
		pName->setAnchorPoint(ccp(0.5, 0.5));
		pName->setPosition(ccp(position.x + RESULT_PLAYER_NAME_POSITION_X, position.y + RESULT_PLAYER_NAME_POSITION_Y) );
		addChild(pName,1);

		//total score
		std::string playerScore = std::to_string(CGameManager::GetInstance()->GetTotalScore(i) );
		CCLabelTTF* pScore = CCLabelTTF::create(playerScore.c_str(), GAME_FONT, 72 );
		pScore->setAnchorPoint(ccp(0.5,0.5));
		pScore->setColor(ccc3(80, 80, 80));
		pScore->setPosition(ccp(position.x + RESULT_PLAYER_SCORE_POSITION_X_MARGIN, position.y + RESULT_PLAYER_SCORE_POSITION_Y_MARGIN));
		addChild(pScore,0);

		// tile + * + count
        // origin
        CCSprite* pTile = CCSprite::create(RESULT_FLOWER_IMAGE[characterId].c_str());
        pTile->setPosition(ccp(position.x + RESULT_FLOWER_IMAGE_X_MARGIN ,
                               position.y + RESULT_ITEM_IMAGE_Y_MARGIN ) );
        pTile->setAnchorPoint(ccp(0.5, 0.0) );
        addChild(pTile, 0);
        /*
        // 표시할 그림 수 결정
        int weightedTileNum = (tileNum - tileMin) / tileUnit + 1;
        
        // 최대 최소 수 보정
        if (tileNum == 0)
            weightedTileNum = 0;
        else if (tileNum == tileMax)
            weightedTileNum = 4;
        
        for (int eachItem = weightedTileNum; eachItem > 0; --eachItem )
        {
            // 타일 그림 그리는 곳
            CCSprite* pTile = CCSprite::create(RESULT_FLOWER_IMAGE[characterId].c_str());
            pTile->setPosition(ccp(position.x + RESULT_FLOWER_IMAGE_X_MARGIN + ( (eachItem % 2 == 0) ? 20 : -20),
                                   position.y + RESULT_ITEM_IMAGE_Y_MARGIN + (4 - eachItem) * 20 ) );
            pTile->setAnchorPoint(ccp(0.5, 0.0) );
            pTile->setScale(1.0f - (0.1*eachItem) );
            pTile->setOpacity(255 - (20*eachItem) );
            // pTile->setScale(0.8f);
            addChild(pTile, 0);
        }
        */
        
		std::string tileCount = std::to_string( tileNum );

		CCLabelTTF* pTileCount = CCLabelTTF::create(tileCount.c_str(), GAME_FONT, 48 );
		pTileCount->setPosition(ccp(position.x + RESULT_FLOWER_COUNT_X_MARGIN, position.y + RESULT_ITEM_COUNT_Y_MARGIN) );
		pTileCount->setAnchorPoint(ccp(0.5, 0.0) );
		this->addChild(pTileCount, 0);

		//gold + * + count
        /*
        // origin
		CCSprite* pGold = CCSprite::create(RESULT_GOLD_IMAGE[0].c_str());
		pGold->setPosition(ccp(position.x + RESULT_GOLD_IMAGE_X_MARGIN, position.y + RESULT_ITEM_IMAGE_Y_MARGIN) );
		pGold->setAnchorPoint(ccp(0.5, 0.0) );
		addChild(pGold, 0);
        */
        
        // 표시할 그림 수 결정
        int weightedGoldNum = (cakeNum - goldMin) / goldUnit + 1;
        
        // 최대 최소 수 보정
        if (cakeNum == 0)
            weightedGoldNum = 0;
        else if (cakeNum == goldMax)
            weightedGoldNum = 4;
        
        for (int eachItem = weightedGoldNum; eachItem > 0; --eachItem )
        {
            // 케익 그림 그리는 곳
            CCSprite* pTile = CCSprite::create(RESULT_GOLD_IMAGE[0].c_str());
            pTile->setPosition(ccp(position.x + RESULT_GOLD_IMAGE_X_MARGIN + ( (eachItem % 2 == 0) ? 20 : -20),
                                   position.y + RESULT_ITEM_IMAGE_Y_MARGIN + (weightedGoldNum - eachItem) * 40 ) );
            pTile->setAnchorPoint(ccp(0.5, 0.0) );
            pTile->setRotation( (eachItem % 2 == 0 ? -1 : 1) * 20 );
            pTile->setScale(0.6f);
            // pTile->setOpacity(255 - (20*eachItem) );
            addChild(pTile, 0);
        }
        
		std::string goldCount = std::to_string( cakeNum );

		CCLabelTTF* pGoldCount = CCLabelTTF::create(goldCount.c_str(), GAME_FONT, 48 );
		pGoldCount->setPosition(ccp(position.x + RESULT_GOLD_COUNT_X_MARGIN, position.y + RESULT_ITEM_COUNT_Y_MARGIN) );
		pGoldCount->setAnchorPoint(ccp(0.5, 0.0) );
		this->addChild(pGoldCount, 0);

		//Trash + * + count
        /*
        // origin
		CCSprite* pTrash = CCSprite::create(ResultTrashImage[0].c_str());
		pTrash->setPosition(ccp(position.x + RESULT_TRASH_IMAGE_X_MARGIN, position.y + RESULT_ITEM_IMAGE_Y_MARGIN) );
		pTrash->setAnchorPoint(ccp(0.5, 0.0) );
		addChild(pTrash, 0);
        */
        
        // 표시할 그림 수 결정
        int weightedTrashNum = (trashNum - trashMin) / trashUnit;
        
        // 최대 최소 수 보정
        if (trashNum > 0 && trashNum < 1)
            weightedTrashNum = 1;
        else if (trashNum == trashMax)
            weightedTrashNum = 4;
        
        for (int eachItem = weightedTrashNum; eachItem > 0; --eachItem )
        {
            // 쓰레기 그림 그리는 곳
            CCSprite* pTile = CCSprite::create(ResultTrashImage[0].c_str());
            pTile->setPosition(ccp(position.x + RESULT_TRASH_IMAGE_X_MARGIN + ( (eachItem % 2 == 0) ? 15 : -20),
                                   position.y + RESULT_ITEM_IMAGE_Y_MARGIN + (weightedTrashNum - eachItem) * 40 ) );
            pTile->setAnchorPoint(ccp(0.5, 0.0) );
            pTile->setRotation( (eachItem % 2 == 0 ? -1 : 1) * 15 );
            pTile->setScale(0.7f);
            // pTile->setOpacity(255 - (20*eachItem) );
            addChild(pTile, 0);
        }
        
		std::string trashCount = std::to_string( trashNum );

		CCLabelTTF* pTrashCount = CCLabelTTF::create(trashCount.c_str(), GAME_FONT, 48 );
		pTrashCount->setPosition(ccp(position.x + RESULT_TRASH_COUNT_X_MARGIN, position.y + RESULT_ITEM_COUNT_Y_MARGIN) );
		pTrashCount->setAnchorPoint(ccp(0.5, 0.0) );
		this->addChild(pTrashCount, 0);

		//¥Ÿ¿Ω ¿Œµ¶Ω∫∏¶ ¿ß«ÿ ∆˜¡ˆº« x¡¬«• √ﬂ∞°.
		position.x += RESULT_BACKGROUND_WIDTH;
	}

	return true;
}