#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MainScene.h"
#include "config.h"
#include "IntroScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//이것은 프레임 사이즈입니다.
	CCEGLView::sharedOpenGLView()->setFrameSize(winSize.width,winSize.height);
#else
	CCEGLView::sharedOpenGLView()->setFrameSize(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);
#endif

	//이것은 실제 우리가 만든 화면을 나타냅니다. 이 비율에 맞춰 모든 그림들이 프레임 사이즈로 줄어드는 것!!
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(WINDOW_WIDTH,WINDOW_HEIGHT,kResolutionShowAll);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	CCScene *pScene = CIntroScene::create();

    // run
    pDirector->runWithScene(CCTransitionFade::create(1.0,pScene));

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
