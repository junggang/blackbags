//
//  UIDelegateBridge.h
//  MyApp1
//
//  Created by DAC-TOAN HO on 11-10-10.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

#import "LayerWebView.h"

@interface UIWebViewBridge : NSObject<UIWebViewDelegate,UIAlertViewDelegate>
{
    LayerWebView * mLayerWebView; 
    UIView    *mView;
    UIWebView *mWebView;
}

-(void) setLayerWebView : (LayerWebView*) iLayerWebView ;
-(void) releaseResource;
@end