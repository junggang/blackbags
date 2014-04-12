//
//  AdMobObjectCPP.cpp
//  MonsterScramble
//
//  Created by Gyeongwook on 2014. 4. 12..
//
//

#include "AdMobObjectCPP.h"
#include "BannerViewController.h"

namespace gene  {
    void AdMobObjectCPP::showAdMob(){
        [[BannerViewController shared] showAdMob];
    }
    void AdMobObjectCPP::hideAdMob(){
        [[BannerViewController shared] hideAdMob];
    }
}
