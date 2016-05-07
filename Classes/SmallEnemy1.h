#ifndef SmallEnemy1_h__
#define SmallEnemy1_h__
#include "cocos2d.h"
#include "BodyParent.h"

USING_NS_CC;

class SmallEnemy1 :public BodyParent
{
public:
	virtual bool init();

	CREATE_FUNC(SmallEnemy1);

	void shoot();

	void repeatShoot(float dt);

	virtual void explode();

	virtual void clear();
};
#endif // SmallEnemy1_h__
