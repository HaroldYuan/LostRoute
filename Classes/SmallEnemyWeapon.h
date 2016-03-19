#ifndef SmallEnemyWeapon2_h__
#define SmallEnemyWeapon2_h__
#include "cocos2d.h"
#include "BodyParent.h"
#include "Resources.h"
USING_NS_CC;

class SmallEnemyWeapon :public BodyParent
{
	friend class WeaponLayer;
public:
	virtual bool init();

	void clear();

	CREATE_FUNC(SmallEnemyWeapon);
};
#endif // SmallEnemyWeapon2_h__
