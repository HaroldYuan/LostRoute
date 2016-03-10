#ifndef SmallEnemyWeapon1_h__
#define SmallEnemyWeapon1_h__
#include "cocos2d.h"
#include "BodyParent.h"
#include "Resources.h"
USING_NS_CC;

class SmallEnemyWeapon1 :public BodyParent
{
public:
	virtual bool init();
	CREATE_FUNC(SmallEnemyWeapon1);
};
#endif // SmallEnemyWeapon1_h__
