//
//  BannerViewController.h
//  MonsterScramble
//
//  Created by Gyeongwook on 2014. 3. 29..
//
//

#ifndef __MonsterScramble__BannerViewController__
#define __MonsterScramble__BannerViewController__

#import <UIKit/UIKit.h>

extern NSString * const BannerViewActionWillBegin;
extern NSString * const BannerViewActionDidFinish;

@interface BannerViewController : UIViewController

- (instancetype)initWithContentViewController:(UIViewController *)contentController;
- (void) showAdMob;
- (void) hideAdMob;

@end

#endif /* defined(__MonsterScramble__BannerViewController__) */
