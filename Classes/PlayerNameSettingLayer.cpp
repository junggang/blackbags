#include "PlayerNameSettingLayer.h"

USING_NS_CC;

// ������!! �� ���̾ ����� �۵��ϴ��� �˾ƺ����� Win32 Ű���带 �������� �ʾƼ� iOS���� ����������!!
// Win32 �ϵ���� Ű����� ���� �������� �ʴ´ٰ� �Ф�
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

	// textfield���� ������ ���ڸ� label��
	label->setString(textfield->getString());
}

void CPlayerNameSettingLayer::TouchKeyboard( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint point = pTouch->getLocationInView();
	point = CCDirector::sharedDirector()->convertToGL(point);

	CCTextFieldTTF *textfield = (CCTextFieldTTF *)this->getChildByTag(100);
	CCRect rect = textfield->boundingBox();

	if(rect.containsPoint(point)) {
		textfield->attachWithIME();
	}
}
