#ifndef BigEnemy_h__
#define BigEnemy_h__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "BodyParent.h"
USING_NS_CC;
using namespace CocosDenshion;

class BigEnemy :public BodyParent
{
public:
	virtual bool init();

	void shoot();

	void repeatShoot(float dt);

	virtual void clear();

	virtual void explode();

	CREATE_FUNC(BigEnemy);
};
#endif // BigEnemy_h__
