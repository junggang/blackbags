#include "cocos2d.h"
#include "config.h"


class CMO_dot : public cocos2d::CCSprite
{
public:
	CMO_dot();
	~CMO_dot();

protected:
	static CMO_dot* create(const char* pszFileName);

public:
	static CMO_dot* Create();
	void update(float delta);


private:
};

