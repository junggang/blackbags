//
//  DisconnectedLayer.h
//  MonsterScramble
//
//  Created by Gyeongwook on 2014. 3. 6..
//
//

#ifndef __MonsterScramble__TimeOutLayer__
#define __MonsterScramble__TimeOutLayer__
#include "cocos2d.h"

class CTimeOutLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
    
	// a selector callback
    void mainSceneCallback(CCObject* pSender);
    
	// implement the "static node()" method manually
    CREATE_FUNC(CTimeOutLayer);
};

#endif /* defined(__MonsterScramble__DisconnectedLayer__) */
