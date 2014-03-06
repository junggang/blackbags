//
//  UIDelegateBridge.mm
//  MyApp1
//
//  Created by DAC-TOAN HO on 11-10-10.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "UIWebViewBridge.h"
#import "EAGLView.h"

@implementation UIWebViewBridge

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)dealloc
{
   	[mWebView release];
	[mView release]; 
    [super dealloc];
}


-(void) setLayerWebView : (LayerWebView*) iLayerWebView
{
    mLayerWebView = iLayerWebView;
    //mView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, size.width , size.height)];
    mView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 1024 , 768)];
    
    // create webView
    //mWebView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 0, size.width, wWebViewHeight)];
    mWebView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 0, 1024, 768)];
    mWebView.delegate = self;
    
    NSString *urlBase = @"http://blackbags-mons.appspot.com/authentication";
    [mWebView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlBase ]]];
    [mWebView setUserInteractionEnabled:NO]; //don't let the user scroll while things are
    
    // add the webView to the view
    [mView addSubview:mWebView];
    [[EAGLView sharedEGLView] addSubview:mView];
}


- (void)webViewDidStartLoad:(UIWebView *)thisWebView {
	
    
}

- (void)webViewDidFinishLoad:(UIWebView *)thisWebView{ 
    [mWebView setUserInteractionEnabled:YES];
    
    NSLog(@"FinishLoad!");
    
    NSString* newToken = [self getTokenFromCookie];
    if (newToken != nil) {
        //NSLog(@"start!");
        //NSLog(@"%@", token);
        
        // 만약 토큰 가져오기가 성공하면 이거 호출해서 실행할 수 있도록
        mLayerWebView->webViewDidFinishLoad([newToken UTF8String]);
    }
}

- (void)webView:(UIWebView *)thisWebView didFailLoadWithError:(NSError *)error 
{
	if ([error code] != -999 && error != NULL) { //error -999 happens when the user clicks on something before it's done loading.
		
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Network Error" message:@"MultiTest was unable to load the page. Please try again later when you have a network connection."
													   delegate:self cancelButtonTitle:nil otherButtonTitles:@"OK", nil];
		[alert show];
		[alert release];
		
	}		
    
} 

-(void) releaseResource
{
	mWebView.delegate = nil; //keep the webview from firing off any extra messages
    
	//remove items from the Superview...just to make sure they're gone
	[mWebView removeFromSuperview];
	[mView removeFromSuperview];
}

// functions for getting token
// get token from cookie
- (NSString*)getTokenFromCookie
{
    NSHTTPCookie *cookie;
    NSHTTPCookieStorage *cookieJar = [NSHTTPCookieStorage sharedHTTPCookieStorage];
    
    for (cookie in [cookieJar cookies])
    {
        //NSLog(@"%@", [cookie domain]);
        if ([[cookie domain] isEqualToString:@"blackbags-mons.appspot.com"])
        {
            //NSLog(@"same");
            //NSLog(@"%@", [cookie name]);
            if ([[cookie name] isEqualToString:@"ACSID"])
            {
                return [cookie value];
            }
        }
    }
    return nil;
}

@end
