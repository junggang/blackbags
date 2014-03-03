//
//  LoginWebView.h
//  MonsterScramble
//
//  Created by Gyeongwook on 2014. 3. 3..
//
//

#ifndef __MonsterScramble__LoginWebView__
#define __MonsterScramble__LoginWebView__

#import <UIKit/UIKit.h>

/*
//클래스 전방 선언 같은 건가?
@class ViewController;

@interface LoginWebView : NSObject <UIWebViewDelegate> // 어플리케이션을 상속 받았다... 이래도 되나?
{
    UIWindow* window;
    ViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet ViewController *viewController;

@end
*/

// *** origin code ***
 
@interface LoginWebView : UIViewController <UIWebViewDelegate>
{
    UIWebView *webView;
    NSString *token;
}

@property (nonatomic, retain) IBOutlet UIWebView *webView;
@property (nonatomic, retain) IBOutlet NSString *token;
//@property (nonatomic, retain) IBOutlet NSString *domain;

@end

#endif /* defined(__MonsterScramble__LoginWebView__) */
