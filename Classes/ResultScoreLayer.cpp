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
	int playerNum = CGameManager::GetInstance()->GetCurrentPlayerNumber();
	int winnerIdx = CGameManager::GetInstance()->GetWinnerIdx();

	CCPoint position;
	float m_columnWidth = 250.0f;

	//플레이어 수에 따라 시작 점을 계산.
	position.x = visibleSize.width/2 - m_columnWidth*playerNum/2;
	position.y = 100.0f;


	for (unsigned int i = 0; i < playerNum; ++i)
	{
		//position.y 축에 더해지는 높이 ( 초기화는 캐릭터 위치 )
		float nextLinePosition = 250.0f;

		int characterId = CGameManager::GetInstance()->GetCharacterIdByPlayerId(i);
		CCSprite* pFace;
		//승패 여부에 따라 캐릭터 이미지 생성
		if ( i == winnerIdx)
			pFace = CCSprite::create(ResultCharacterWinImage[characterId].c_str());
		else
			pFace = CCSprite::create(ResultCharacterLoseImage[characterId].c_str());

		pFace->setAnchorPoint(ccp(0,0));
		pFace->setPosition(ccp(position.x,position.y+nextLinePosition));
		addChild(pFace,0);

		nextLinePosition -= 80.0;

		//player name
		CCLabelTTF* pName = CCLabelTTF::create(CGameManager::GetInstance()->GetPlayerName(i).c_str(), "arial", 34 );
		pName->setAnchorPoint(ccp(0,0));
		pName->setPosition(ccp(position.x,position.y+nextLinePosition));
		addChild(pName,0);

		nextLinePosition -= 50.0;

		//total score
		std::string playerScore = std::to_string(CGameManager::GetInstance()->GetTotalScore(i) );
		CCLabelTTF* pScore = CCLabelTTF::create(playerScore.c_str(), "arial", 34 );
		pScore->setAnchorPoint(ccp(0,0));
		pScore->setPosition(ccp(position.x,position.y+nextLinePosition));
		addChild(pScore,0);

		nextLinePosition -= 50.0;

		//tile + * + count
		CCSprite* pTile = CCSprite::create("image/PLAYER_tile0.png");
		pTile->setPosition(ccp(position.x,position.y+nextLinePosition) );
		pTile->setAnchorPoint(ccp(0.0, 0.0) );
		addChild(pTile, 0);

		CCSprite* pTileMultiply = CCSprite::create("image/RESULT_multiply.png");
		pTileMultiply->setPosition(ccp(position.x+80.0f,position.y+nextLinePosition) );
		pTileMultiply->setAnchorPoint(ccp(0.0, 0.0) );
		this->addChild(pTileMultiply, 0);

		std::string tileCount = std::to_string(CGameManager::GetInstance()->GetElementCount(i, ITEM_NOTHING) );

		CCLabelTTF* pTileCount = CCLabelTTF::create(tileCount.c_str(), "arial", 34 );
		pTileCount->setPosition(ccp(position.x+140.0f,position.y+nextLinePosition) );
		pTileCount->setAnchorPoint(ccp(0.0, 0.0) );
		this->addChild(pTileCount, 0);

		nextLinePosition -= 50.0;

		int itemPerLine = 3;
		//gold + * + count
		int goldNum = CGameManager::GetInstance()->GetElementCount(i,ITEM_GOLD);
		for(int itemNum = 0; itemNum<goldNum;++itemNum)
		{
			CCSprite* pGold = CCSprite::create("image/RESULT_gold.png");
			pGold->setPosition(ccp(position.x+80.0f*(itemNum%itemPerLine),position.y+nextLinePosition-80.0f*(itemNum/itemPerLine)));
			pGold->setAnchorPoint(ccp(0,0));
			addChild(pGold,0);
		}

		nextLinePosition-= 80.0f * (goldNum/itemPerLine);

		//Trash + * + count
		int trashNum = CGameManager::GetInstance()->GetElementCount(i,ITEM_TRASH);
		for(int itemNum = 0; itemNum<trashNum;++itemNum)
		{
			CCSprite* pTrash = CCSprite::create("image/RESULT_trash.png");
			pTrash->setPosition(ccp(position.x+80.0f*(itemNum%itemPerLine),position.y+nextLinePosition-80.0f*(itemNum/itemPerLine)));
			pTrash->setAnchorPoint(ccp(0,0));
			addChild(pTrash,0);
		}

		//다음 인덱스를 위해 포지션 x좌표 추가.
		position.x += m_columnWidth;
	}

	return true;
}