#include "MapObject.h"

USING_NS_CC;


CMapObject::CMapObject()
{

}

CMapObject::~CMapObject()
{

}

CMapObject* CMapObject::create(const char* pszFileName, const CCRect& rect)
{
	CMapObject* pSprite = new CMapObject();
	if (pSprite && pSprite->initWithFile(pszFileName, rect))
	{
		pSprite->autorelease();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

CMapObject* CMapObject::Create(MO_TYPE type, int targetRow)
{
	//�� MO_TYPE�� �ش��ϴ� �׸��� �� ���� ����. �켱 �ϵ��ڵ�.. 
	static std::string objectNames[6] =
	{
		"image/MO_dot.png",
		"image/MO_line_horizontal.png",
		"image/MO_line_vertical.png",
		"image/MO_line_horizontal_c.png",
		"image/MO_line_vertical_c.png",
		"image/MO_tile.png"
	};

	//MO_SENTINEL�� ��� ������Ʈ ���� ��ü�� �� �ϵ��� ����.
	if (type < 0 || type >5 || type == MO_SENTINEL)
		return NULL;

	int objectIdx = 0;
	float width = 0;
	float height = 0;

	switch (type)
	{
	case MO_DOT:
		objectIdx = 0;
		width = 50.0f;
		height = 50.0f;
		break;
	case MO_LINE_UNCONNECTED:
		objectIdx = 1+(targetRow%2);
		width = (targetRow%2==0)? 200.0f:50.0f;
		height = (targetRow%2==0)? 50.0f:200.0f;
		break;
	case MO_LINE_CONNECTED:
		objectIdx = 3+(targetRow%2);
		width = (targetRow%2==0)? 200.0f:50.0f;
		height = (targetRow%2==0)? 50.0f:200.0f;
		break;
	case MO_LINE_HIDDEN:
		break;
	case MO_TILE:
		objectIdx = 5;
		width = 200.0f;
		height = 200.0f;
		break;
	default:
		break;
	}

	//m_Type�� �����Ǵ� �̹����� �����ͼ� ������Ʈ�� �����Ѵ�. ���⼭�� setMapType�� ������Ʈ�� ���� ...?
	CMapObject* pMapObejct = CMapObject::create(objectNames[objectIdx].c_str(), CCRectMake(0.0f, 0.0f, width, height));
	pMapObejct->SetMapType(type);

	return pMapObejct;
}

int CMapObject::GetMapType()
{
	return m_type;
}

void CMapObject::SetMapType(MO_TYPE type)
{
	m_type = type;
}
