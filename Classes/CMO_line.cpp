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

	//i가 홀수고 j가 짝수면 누워 있다.
	//i가 짝수고 j가 홀수면 서 있다.
	//짝수행인 경우 수평으로 긴 라인. 홀수행인 경우 수직으로 긴 라인.
	int width = (indexedPosition.m_PosI % 2 == 0)? DEFAULT_LINE_WEIGHT : DEFAULT_TILE_SIZE ;
	int height = (indexedPosition.m_PosI % 2 == 0)? DEFAULT_TILE_SIZE : DEFAULT_LINE_WEIGHT  ;

	m_ImageFileIdx = indexedPosition.m_PosI % 2;

	//선이 연결된 경우 그림만 바꿔 줌.
	if (CGameManager::GetInstance()->GetMapType(indexedPosition) == MO_LINE_CONNECTED)
	{
		m_Connected = true;
		m_ImageFileIdx += 2;
	}
	
	//적절한 이미지를 넣어준다.
	pLine = CCSprite::create(lineImageFileList[m_ImageFileIdx].c_str(), CCRectMake(0.0f, 0.0f, width,  height) );
	setAnchorPoint();
	pLine->setPosition( ccp(0.0f, 0.0f) );
	this->addChild(pLine, 0);
}

void CMO_line::update( float delta )
{
	//CCLog("Line updated");
	//현재 타일 소유를 물어보고 업데이트
	if (!m_Connected && CGameManager::GetInstance()->IsConnected(m_Index) == MO_LINE_CONNECTED)
	{
		m_Connected = true;

		//기존의 이미지는 삭제하고
		int width = pLine->getContentSize().width;
		int height = pLine->getContentSize().height;
		this->removeChild(pLine, true);

		//바뀐 이미지로 추가
		pLine = CCSprite::create(lineImageFileList[m_ImageFileIdx + 2].c_str(), CCRectMake(0.0f, 0.0f, width,  height) );
		setAnchorPoint();
		pLine->setPosition( ccp(0.0f, 0.0f) );
		this->addChild(pLine, 0);
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