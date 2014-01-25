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
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a background image
	
	//score part
	int playerNum = CGameManager::GetInstance()->GetPlayerNumber();
	int winnerIdx = CGameManager::GetInstance()->GetWinnerIdx();

	for (unsigned int i = 0; i < playerNum; ++i)
	{
		float horizontalPos = 0.0f;
		float verticlaPos = 0.0f;

		//character face
		CCSprite* pFace = CCSprite::create(CGameManager::GetInstance()->GetCharacterResultFaceFileName(i).c_str() );

		//상수값으로 계산하도록 해서 위로 뺄 것
		verticlaPos = pFace->getContentSize().height * (3 + i);

		horizontalPos = pFace->getContentSize().width * 2;
		pFace->setPosition(ccp(horizontalPos, verticlaPos) );
		pFace->setAnchorPoint(ccp(0.0, 0.0) );
		this->addChild(pFace, 0);

		if (winnerIdx == i)
		{
			CCSprite* pCrown = CCSprite::create("image/RESULT_crown.png");

			pCrown->setPosition(ccp(horizontalPos, verticlaPos + pFace->getContentSize().height) );
			pCrown->setAnchorPoint(ccp(0.0, 1.0) );
			this->addChild(pCrown, 0);
		}

		//player name
		CCLabelTTF* pName = CCLabelTTF::create(CGameManager::GetInstance()->GetPlayerName(i).c_str(), "arial", 34 );
		horizontalPos += pFace->getContentSize().width;
		pName->setPosition(ccp(horizontalPos, verticlaPos + pFace->getContentSize().height) );
		pName->setAnchorPoint(ccp(0.0, 1.0) );
		this->addChild(pName, 0);

		//total score
		std::string playerScore = std::to_string(CGameManager::GetInstance()->GetTotalScore(i) );

		CCLabelTTF* pScore = CCLabelTTF::create(playerScore.c_str(), "arial", 34 );
		horizontalPos += pFace->getContentSize().width;
		pScore->setPosition(ccp(horizontalPos, verticlaPos) );
		pScore->setAnchorPoint(ccp(0.0, 0.0) );
		this->addChild(pScore, 0);

		//tile + * + count
		CCSprite* pTile = CCSprite::create("image/PLAYER_tile0.png");
		horizontalPos += pTile->getContentSize().width;
		pTile->setPosition(ccp(horizontalPos, verticlaPos) );
		pTile->setAnchorPoint(ccp(0.0, 0.0) );
		this->addChild(pTile, 0);

		CCSprite* pTileMultiply = CCSprite::create("image/RESULT_multiply.png");
		horizontalPos += pTile->getContentSize().width;
		pTileMultiply->setPosition(ccp(horizontalPos, verticlaPos) );
		pTileMultiply->setAnchorPoint(ccp(0.0, 0.0) );
		this->addChild(pTileMultiply, 0);

		std::string tileCount = std::to_string(CGameManager::GetInstance()->GetElementCount(i, ITEM_NOTHING) );

		CCLabelTTF* pTileCount = CCLabelTTF::create(tileCount.c_str(), "arial", 34 );
		horizontalPos += pTileMultiply->getContentSize().width;
		pTileCount->setPosition(ccp(horizontalPos, verticlaPos) );
		pTileCount->setAnchorPoint(ccp(0.0, 0.0) );
		this->addChild(pTileCount, 0);

		//gold + * + count
		CCSprite* pGold = CCSprite::create("image/RESULT_gold.png");
		horizontalPos += pGold->getContentSize().width;
		pGold->setPosition(ccp(horizontalPos, verticlaPos) );
		pGold->setAnchorPoint(ccp(0.0, 0.0) );
		this->addChild(pGold, 0);

		CCSprite* pGoldMultiply = CCSprite::create("image/RESULT_multiply.png");
		horizontalPos += pGold->getContentSize().width;
		pGoldMultiply->setPosition(ccp(horizontalPos, verticlaPos) );
		pGoldMultiply->setAnchorPoint(ccp(0.0, 0.0) );
		this->addChild(pGoldMultiply, 0);

		std::string goldCount = std::to_string(CGameManager::GetInstance()->GetElementCount(i, ITEM_GOLD) );

		CCLabelTTF* pGoldCount = CCLabelTTF::create(goldCount.c_str(), "arial", 34 );
		horizontalPos += pGoldMultiply->getContentSize().width;
		pGoldCount->setPosition(ccp(horizontalPos, verticlaPos) );
		pGoldCount->setAnchorPoint(ccp(0.0, 0.0) );
		this->addChild(pGoldCount, 0);

		//trash + * + count
		CCSprite* pTrash = CCSprite::create("image/RESULT_trash.png");
		horizontalPos += pTrash->getContentSize().width;
		pTrash->setPosition(ccp(horizontalPos, verticlaPos) );
		pTrash->setAnchorPoint(ccp(0.0, 0.0) );
		this->addChild(pTrash, 0);

		CCSprite* pTrashMultiply = CCSprite::create("image/RESULT_multiply.png");
		horizontalPos += pTrash->getContentSize().width;
		pTrashMultiply->setPosition(ccp(horizontalPos, verticlaPos) );
		pTrashMultiply->setAnchorPoint(ccp(0.0, 0.0) );
		this->addChild(pTrashMultiply, 0);

		std::string trashCount = std::to_string(CGameManager::GetInstance()->GetElementCount(i, ITEM_TRASH) );

		CCLabelTTF* pTrashCount = CCLabelTTF::create(trashCount.c_str(), "arial", 34 );
		horizontalPos += pTrashMultiply->getContentSize().width;
		pTrashCount->setPosition(ccp(horizontalPos, verticlaPos) );
		pTrashCount->setAnchorPoint(ccp(0.0, 0.0) );
		this->addChild(pTrashCount, 0);
	}
    
	return true;
}