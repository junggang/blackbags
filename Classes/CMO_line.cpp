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
	//�����ֿ� ���� �׸� ���� ��
	static std::string objectNames[4] =
	{
		"image/MO_line_vertical.png",
		"image/MO_line_horizontal.png",
		"image/MO_line_vertical_c.png",
		"image/MO_line_horizontal_c.png",
	};

	//i�� Ȧ���� j�� ¦���� ���� �ִ�.
	//i�� ¦���� j�� Ȧ���� �� �ִ�.
	//¦������ ��� �������� �� ����. Ȧ������ ��� �������� �� ����.
	int width = (indexedPosition.m_PosI % 2 == 0)? DEFAULT_LINE_WEIGHT : DEFAULT_TILE_SIZE ;
	int height = (indexedPosition.m_PosI % 2 == 0)? DEFAULT_TILE_SIZE : DEFAULT_LINE_WEIGHT  ;

	int objectIdx = indexedPosition.m_PosI % 2;

	CMO_line* pMapObejct;

	m_Index = indexedPosition;

	//���� ����� ��� �׸��� �ٲ� ��.
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

	//i�� Ȧ���� j�� ¦���� ���� �ִ�.
	//i�� ¦���� j�� Ȧ���� �� �ִ�.
	//¦������ ��� �������� �� ����. Ȧ������ ��� �������� �� ����.
	int width = (indexedPosition.m_PosI % 2 == 0)? DEFAULT_LINE_WEIGHT : DEFAULT_TILE_SIZE ;
	int height = (indexedPosition.m_PosI % 2 == 0)? DEFAULT_TILE_SIZE : DEFAULT_LINE_WEIGHT  ;

	m_ImageFileIdx = indexedPosition.m_PosI % 2;

	//���� ����� ��� �׸��� �ٲ� ��.
	if (CGameManager::GetInstance()->GetMapType(indexedPosition) == MO_LINE_CONNECTED)
	{
		m_Connected = true;
		m_ImageFileIdx += 2;
	}
	
	//������ �̹����� �־��ش�.
	pLine = CCSprite::create(lineImageFileList[m_ImageFileIdx].c_str(), CCRectMake(0.0f, 0.0f, width,  height) );
	setAnchorPoint();
	pLine->setPosition( ccp(0.0f, 0.0f) );
	this->addChild(pLine, 0);
}

void CMO_line::update( float delta )
{
	//CCLog("Line updated");
	//���� Ÿ�� ������ ����� ������Ʈ
	if (!m_Connected && CGameManager::GetInstance()->IsConnected(m_Index) == MO_LINE_CONNECTED)
	{
		m_Connected = true;

		//������ �̹����� �����ϰ�
		int width = pLine->getContentSize().width;
		int height = pLine->getContentSize().height;
		this->removeChild(pLine, true);

		//�ٲ� �̹����� �߰�
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