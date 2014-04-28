#include "CMO_line.h"
#include "GameManager.h"

USING_NS_CC;

/*
CMO_line::CMO_line()
{

}

CMO_line::~CMO_line()
{

}

CMO_line* CMO_line::create(const char* pszFileName, const CCRect& rect)
{
	CMO_line* pSprite = new CMO_line();
	if (pSprite && pSprite->initWithFile(pszFileName, rect))
	{
		pSprite->autorelease();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

CMO_line* CMO_line::Create(IndexedPosition indexedPosition)
{
	//소유주에 따른 그림 파일 들
	static std::string objectNames[4] =
	{
		"image/MO_line_vertical.png",
		"image/MO_line_horizontal.png",
		"image/MO_line_vertical_c.png",
		"image/MO_line_horizontal_c.png",
	};

	//i가 홀수고 j가 짝수면 누워 있다.
	//i가 짝수고 j가 홀수면 서 있다.
	//짝수행인 경우 수평으로 긴 라인. 홀수행인 경우 수직으로 긴 라인.
	int width = (indexedPosition.m_PosI % 2 == 0)? DEFAULT_LINE_WEIGHT : DEFAULT_TILE_SIZE ;
	int height = (indexedPosition.m_PosI % 2 == 0)? DEFAULT_TILE_SIZE : DEFAULT_LINE_WEIGHT  ;

	int objectIdx = indexedPosition.m_PosI % 2;

	CMO_line* pMapObejct;

	m_Index = indexedPosition;

	//선이 연결된 경우 그림만 바꿔 줌.
	if (CGameManager::GetInstance()->GetMapType(indexedPosition) == MO_LINE_CONNECTED)
	{
		pMapObejct->m_Connected = true;
		objectIdx += 2;
	}

	pMapObejct = CMO_line::create(objectNames[objectIdx].c_str(), CCRectMake(0.0f, 0.0f, width,  height));

	return pMapObejct;
}
*/
bool CMO_line::init()
{
	if ( !CCSprite::init() )
    {
        return false;
    }

	pLine = NULL;
	m_Connected = false;
	m_ImageFileIdx = 0;

	return true;
}

void CMO_line::setImage(IndexedPosition indexedPosition)
{
	m_Index = indexedPosition;

	int width = DEFAULT_TILE_WIDTH/2;
	int height = DEFAULT_TILE_HEIGHT/2;

	m_ImageFileIdx = indexedPosition.m_PosI % 2;

	//선이 연결된 경우 그림만 바꿔 줌.
	if (CGameManager::GetInstance()->GetMapType(indexedPosition) == MO_LINE_CONNECTED)
	{
		m_Connected = true;
		m_ImageFileIdx += 2;
	}
	
	//적절한 이미지를 넣어준다.
	//pLine = CCSprite::create(lineImageFileList[m_ImageFileIdx].c_str(), CCRectMake(0.0f, 0.0f, width,  height) );
	
	if (indexedPosition.m_PosI%2==0 &&indexedPosition.m_PosJ%2==1)
	{
		pLine = CCSprite::create(lineImageFileList[m_ImageFileIdx].c_str(), CCRectMake(0.0f, 0.0f, width,  height) );
		pLine->setAnchorPoint(ccp(1,0));
	}
	else
	{
		pLine = CCSprite::create(lineImageFileList[m_ImageFileIdx].c_str(), CCRectMake(0.0f, 0.0f, width,  height) );
		pLine->setAnchorPoint(ccp(0,0));
	}

	//setAnchorPoint();
	pLine->setPosition( ccp(0.0f, 0.0f) );
	this->addChild(pLine, 0);
}

void CMO_line::update( float delta )
{
    if ( !m_Connected && CGameManager::GetInstance()->IsConnected(m_Index) == MO_LINE_CONNECTED)
	{
        changeImage();
		m_Connected = true;
        
        CCSpriteBatchNode* spritebatch = CCSpriteBatchNode::create(LineAnimationFileList[m_ImageFileIdx % 2].c_str());
        CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
        cache->addSpriteFramesWithFile(LineAnimationFileListPlist[m_ImageFileIdx % 2].c_str());
        
        
        CCArray* animFrames = CCArray::createWithCapacity(48);
        
        char str[100] = {0};
        
        for(int i = 1; i < 49; i++)
        {
            if(m_ImageFileIdx % 2==0)
            {
                sprintf(str, "ani_playscene_line_recent_v_000%02d.png", i);
            }
            else
            {
                sprintf(str, "ani_playscene_line_recent_000%02d.png", i);
            }
            
            CCSpriteFrame* frame = cache->spriteFrameByName( str );
            animFrames->addObject(frame);
        }
        
        CCSprite*pElement;
        if(m_ImageFileIdx % 2==0)
        {
            pElement = CCSprite::createWithSpriteFrameName("ani_playscene_line_recent_v_00001.png");
            pElement->setAnchorPoint(ccp(1,0));
        }
        else
        {
            pElement = CCSprite::createWithSpriteFrameName("ani_playscene_line_recent_00001.png");
            pElement->setAnchorPoint(ccp(0,0));
        }
        
        spritebatch->addChild(pElement);
        addChild(spritebatch,2);
        spritebatch->setTag(0);
        
        
        CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames,PLAYSCENE_ANIMATION_TIME/48);
        CCAction* myLine = CCAnimate::create(animation);
        pElement->runAction(myLine);
    }
    else if( m_Connected )
    {
        removeChildByTag(0);
        pLine->setVisible(true);
    }
  
    
}

void CMO_line::setAnchorPoint()
{
	if (m_ImageFileIdx % 2 == 0)
	{
		//vertical
		pLine->setAnchorPoint( ccp(0.5f, 0.0f) );
	}
	else
	{
		//horizontal
		pLine->setAnchorPoint( ccp(0.0f, 0.5f) );
	}
}

void CMO_line::changeImage()
{
	//removeChild(pLine,false);
	pLine = CCSprite::create(lineImageFileList[m_ImageFileIdx + 2].c_str());

	if (m_ImageFileIdx % 2== 0)
		pLine->setAnchorPoint( ccp(1.0f, 0.0f) );
	else
		pLine->setAnchorPoint( ccp (0,0));

	pLine->setPosition(ccp(0,0));
    pLine->setVisible(false);
	this->addChild(pLine, 0);
}

void CMO_line::setLineDirection( Direction lineDirection )
{
	m_LineDirection = lineDirection;
}
