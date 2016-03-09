#ifndef BigEnemy_h__
#define BigEnemy_h__

#include "cocos2d.h"
#include "BodyParent.h"
#include "Resources.h"
USING_NS_CC;

class BigEnemy :public BodyParent
{
public:
	virtual bool init();
	CREATE_FUNC(BigEnemy);
private:
};
#endif // BigEnemy_h__
