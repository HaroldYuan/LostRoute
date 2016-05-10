#ifndef BigEnemyWeapon_h__
#define BigEnemyWeapon_h__

#include "cocos2d.h"
#include "BodyParent.h"
#include "Resources.h"

USING_NS_CC;

class BigEnemyWeapon :public BodyParent
{
public:
	virtual bool init();
	CREATE_FUNC(BigEnemyWeapon);
};
#endif // BigEnemyWeapon_h__
