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
	CCEGLView::sharedOpenGLView()->setFrameSize(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(WINDOW_WIDTH,WINDOW_HEIGHT,kResolutionShowAll);
	//CCDirector::sharedDirector()->setContentScaleFactor(2.0f);

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
