#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "GameLogic.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
	CGameLogic::GetInstance()->init();
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("MonsterScramble");
    eglView->setFrameSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    return CCApplication::sharedApplication()->run();
}
