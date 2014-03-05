//
//  LoginScene.h
//  MonsterScramble
//
//  Created by Gyeongwook on 2014. 3. 5..
//
//

#ifndef __MonsterScramble__LoginScene__
#define __MonsterScramble__LoginScene__

#include "cocos2d.h"
#include "config.h"

class CLoginScene : public cocos2d::CCScene
{
public:
	virtual bool init(void);
	virtual void update(float dt);
    
	// implement the "static node()" method manually
	CREATE_FUNC(CLoginScene);
    
private:
	LoginPhase m_CurrentPhase;
    cocos2d::CCLayer* m_LoginLayer;
};

#endif /* defined(__MonsterScramble__LoginScene__) */