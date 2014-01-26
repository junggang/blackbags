#include "PlayerNameSettingLayer.h"

USING_NS_CC;

// 조심해!! 이 레이어가 제대로 작동하는지 알아보려면 Win32 키보드를 지원하지 않아서 iOS에서 돌려봐야해!!
// Win32 하드웨어 키보드는 아직 지원하지 않는다고 ㅠㅠ
bool CPlayerNameSettingLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// Get Window Size
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); 

	// touch enable == true for iPad keyboard input
	this->setTouchEnabled(true);

	CCTextFieldTTF *textfield = CCTextFieldTTF::textFieldWithPlaceHolder("NameInputPage", CCSize(480,30), kCCTextAlignmentCenter, "Arial", 20);
	// textfield tag == 1;
	textfield->setTag(1);
	// set position
	textfield->setPosition(ccp(visibleSize.width/2, visibleSize.height/2 + 100));
	this->addChild(textfield);

	CCLabelTTF *label = CCLabelTTF::create("NAME : ", "", 50);
	// label tag = 2;
	label->setTag(2);
	// set position
	label->setPosition(ccp(visibleSize.width/2, visibleSize.height/2 - 100));
	this->addChild(label);

	return true;
}

void CPlayerNameSettingLayer::ShowKeyboard( cocos2d::CCIMEKeyboardNotificationInfo & info )
{
	CCTextFieldTTF *textfield = (CCTextFieldTTF*)this->getChildByTag(1);
	textfield->setString("");
}

void CPlayerNameSettingLayer::HideKeyboard( cocos2d::CCIMEKeyboardNotificationInfo & info )
{
	CCTextFieldTTF *textfield = (CCTextFieldTTF *)this->getChildByTag(1);
	CCLabelTTF *label = (CCLabelTTF *)this->getChildByTag(2);

	// textfield에서 가져온 문자를 label로
	label->setString(textfield->getString());
}

void CPlayerNameSettingLayer::TouchKeyboard( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint point = pTouch->getLocationInView();
	point = CCDirector::sharedDirector()->convertToGL(point);

	CCTextFieldTTF *textfield = (CCTextFieldTTF *)this->getChildByTag(100);
	CCRect rect = textfield->boundingBox();

	if (rect.containsPoint(point)) {
		textfield->attachWithIME();
	}
}
