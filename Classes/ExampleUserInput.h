// 우선 책에 있는 사용자 입력 예제를 옮김
#include "cocos2d.h"
#include "cocos-ext.h"

class ExampleUserInput : public cocos2d::CCLayerColor,
	public cocos2d::extension::CCEditBoxDelegate
{
public:
	virtual bool init();
	
	static cocos2d::CCScene* scene();

	CREATE_FUNC(ExampleUserInput);

	virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
	
	cocos2d::extension::CCEditBox* m_pEditName;
};