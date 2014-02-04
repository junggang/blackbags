#include "ExampleUserInput.h"

using namespace cocos2d;
using namespace cocos2d::extension;

CCScene* ExampleUserInput::scene()
{
	CCScene *scene = CCScene::create();

	ExampleUserInput *layer = ExampleUserInput::create();

	scene->addChild(layer);

	return scene;
}

bool ExampleUserInput::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(255,255,255,255)) )
	{
		return false;
	}

	CCSize editBoxSize = CCSizeMake(300, 60);

	m_pEditName = CCEditBox::create(editBoxSize, CCScale9Sprite::create("image/board.png"));
	m_pEditName->setPosition(ccp(240, 250));
	m_pEditName->setFontColor(ccGREEN);
	m_pEditName->setPlaceHolder("name:");
	m_pEditName->setReturnType(kKeyboardReturnTypeDone);
	m_pEditName->setDelegate(this);
	addChild(m_pEditName);

	return true;
}

void ExampleUserInput::editBoxEditingDidBegin( cocos2d::extension::CCEditBox* editBox )
{

}

void ExampleUserInput::editBoxEditingDidEnd( cocos2d::extension::CCEditBox* editBox )
{

}

void ExampleUserInput::editBoxTextChanged( cocos2d::extension::CCEditBox* editBox, const std::string& text )
{

}

void ExampleUserInput::editBoxReturn( cocos2d::extension::CCEditBox* editBox )
{

}
