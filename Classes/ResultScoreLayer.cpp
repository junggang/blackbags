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

	//플레이어 수에 따라 시작 점을 계산.
	position.x = (visibleSize.width / 2) - (RESULT_BACKGROUND_WIDTH * playerNum / 2);
	position.y = RESULT_BACKGROUND_POSITION_Y;

	for (unsigned int i = 0; i < playerNum; ++i)
	{
		// background
		CCSprite* pBackgorund = CCSprite::create(RESULT_BACKGROUND_IMAGE[i].c_str());
		pBackgorund->setAnchorPoint(ccp(0, 0) );
		pBackgorund->setPosition(ccp(position.x, position.y) );
		addChild(pBackgorund, 0);

		// character
		int characterId = CGameManager::GetInstance()->GetCharacterIdByPlayerId(i);
		CCSprite* pFace;
		//승패 여부에 따라 캐릭터 이미지 생성
		if ( CGameManager::GetInstance()->IsWinner(i) )
			pFace = CCSprite::create(RESULT_CHARACTER_WIN_IMAGE[characterId].c_str());
		else
			pFace = CCSprite::create(RESULT_CHARACTER_LOSE_IMAGE[characterId].c_str());

		pFace->setAnchorPoint(ccp(0.5,0) );
		pFace->setPosition(ccp(position.x + RESULT_CHARACTER_IMAGE_POSITION_X_MARGIN, position.y + RESULT_CHARACTER_IMAGE_POSITION_Y_MARGIN));
		addChild(pFace,1);

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

		//tile + * + count
		CCSprite* pTile = CCSprite::create(RESULT_FLOWER_IMAGE[characterId].c_str());
		pTile->setPosition(ccp(position.x + RESULT_FLOWER_IMAGE_X_MARGIN, position.y + RESULT_ITEM_IMAGE_Y_MARGIN) );
		pTile->setAnchorPoint(ccp(0.5, 0.0) );
		addChild(pTile, 0);

		std::string tileCount = std::to_string(CGameManager::GetInstance()->GetElementCount(i, ITEM_NOTHING) );

		CCLabelTTF* pTileCount = CCLabelTTF::create(tileCount.c_str(), GAME_FONT, 48 );
		pTileCount->setPosition(ccp(position.x + RESULT_FLOWER_COUNT_X_MARGIN, position.y + RESULT_ITEM_COUNT_Y_MARGIN) );
		pTileCount->setAnchorPoint(ccp(0.5, 0.0) );
		this->addChild(pTileCount, 0);

		//gold + * + count
		CCSprite* pGold = CCSprite::create(RESULT_GOLD_IMAGE[0].c_str());
		pGold->setPosition(ccp(position.x + RESULT_GOLD_IMAGE_X_MARGIN, position.y + RESULT_ITEM_IMAGE_Y_MARGIN) );
		pGold->setAnchorPoint(ccp(0.5, 0.0) );
		addChild(pGold, 0);

		std::string goldCount = std::to_string(CGameManager::GetInstance()->GetElementCount(i, ITEM_GOLD) );

		CCLabelTTF* pGoldCount = CCLabelTTF::create(goldCount.c_str(), GAME_FONT, 48 );
		pGoldCount->setPosition(ccp(position.x + RESULT_GOLD_COUNT_X_MARGIN, position.y + RESULT_ITEM_COUNT_Y_MARGIN) );
		pGoldCount->setAnchorPoint(ccp(0.5, 0.0) );
		this->addChild(pGoldCount, 0);

		//Trash + * + count
		CCSprite* pTrash = CCSprite::create(ResultTrashImage[0].c_str());
		pTrash->setPosition(ccp(position.x + RESULT_TRASH_IMAGE_X_MARGIN, position.y + RESULT_ITEM_IMAGE_Y_MARGIN) );
		pTrash->setAnchorPoint(ccp(0.5, 0.0) );
		addChild(pTrash, 0);

		std::string trashCount = std::to_string(CGameManager::GetInstance()->GetElementCount(i, ITEM_TRASH) );

		CCLabelTTF* pTrashCount = CCLabelTTF::create(trashCount.c_str(), GAME_FONT, 48 );
		pTrashCount->setPosition(ccp(position.x + RESULT_TRASH_COUNT_X_MARGIN, position.y + RESULT_ITEM_COUNT_Y_MARGIN) );
		pTrashCount->setAnchorPoint(ccp(0.5, 0.0) );
		this->addChild(pTrashCount, 0);

		//다음 인덱스를 위해 포지션 x좌표 추가.
		position.x += RESULT_BACKGROUND_WIDTH;
	}

	return true;
}