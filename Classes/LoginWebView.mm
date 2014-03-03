//
//  LoginWebView.cpp
//  MonsterScramble
//
//  Created by Gyeongwook on 2014. 3. 3..
//
//

#import "LoginWebView.h"

// *** origin code ***

@implementation LoginWebView

@synthesize webView = _webView;
@synthesize token = _token;

- (void)viewDidLoad
{
    //[self loadAuthenticateUrl:@"http://blackbags-mons.appspot.com/authentication"];
    
    [super viewDidLoad];
    
    self.webView.delegate = self;
    
    NSURL *url = [NSURL URLWithString:@"http://blackbags-mons.appspot.com/authentication"];
    NSURLRequest *requestURL = [NSURLRequest requestWithURL:url];
    [self.webView loadRequest:requestURL];
}

- (void)viewDidUnload
{
    [self setWebView:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

#pragma mark - Optional UIWebViewDelegate delegate methods
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    return YES;
}

- (void)webViewDidStartLoad:(UIWebView *)webView
{
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
}

- (void)gotToken:(NSString *)newToken
{
    self.token = newToken;
}

- (NSString*)getTokenFromCookie {
    NSHTTPCookie *cookie;
    NSHTTPCookieStorage *cookieJar = [NSHTTPCookieStorage sharedHTTPCookieStorage];
    for (cookie in [cookieJar cookies]) {
        //NSLog(@"%@", [cookie domain]);
        if ([[cookie domain] isEqualToString:@"blackbags-mons.appspot.com"]) {
            //NSLog(@"same");
            //NSLog(@"%@", [cookie name]);
            if ([[cookie name] isEqualToString:@"ACSID"]) {
                return [cookie value];
            }
        }
    }
    return nil;
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    NSLog(@"FinishLoad!");
    
    NSString* newToken = [self getTokenFromCookie];
    if (newToken != nil) {
        //NSLog(@"start!");
        //NSLog(@"%@", token);
        [self gotToken:newToken];
        [self.navigationController popViewControllerAnimated:YES];
    }
    
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    NSLog(@"%@", [self token]);
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
}

@end