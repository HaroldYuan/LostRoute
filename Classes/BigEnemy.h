#ifndef BigEnemy_h__
#define BigEnemy_h__

#include "cocos2d.h"
#include "BodyParent.h"
#include "Resources.h"
#include "WeaponLayer.h"
#include "BigEnemyWeapon.h"
USING_NS_CC;

class BigEnemy :public BodyParent
{
public:
	virtual bool init();

	void shoot();

	void repeatShoot(float dt);

	virtual void clear();

	CREATE_FUNC(BigEnemy);
};
#endif // BigEnemy_h__
