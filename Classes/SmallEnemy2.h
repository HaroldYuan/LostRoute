#ifndef SmallEnemy2_h__
#define SmallEnemy2_h__
#include "cocos2d.h"
#include "BodyParent.h"

USING_NS_CC;

class SmallEnemy2 :public BodyParent
{
public:
	virtual void explode();

	virtual bool init();

	CREATE_FUNC(SmallEnemy2);

	virtual void clear();
};
#endif // SmallEnemy2_h__
