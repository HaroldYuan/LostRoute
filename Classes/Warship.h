#ifndef Warship_h__
#define Warship_h__

#include "cocos2d.h"
#include "Resources.h"
#include "BodyParent.h"
#include "WeaponLayer.h"
#include "WarshipWeapon1.h"
#include "WarshipWeapon2.h"
USING_NS_CC;

class Warship :public BodyParent
{
public:
	virtual bool init();

	void setWeaponLayer(WeaponLayer* weaponLayer);

	void shoot();

	//发射激光束
	void repeatShoot1(float dt);

	//发射光子鱼雷
	void repeatShoot2(float dt);

	CREATE_FUNC(Warship);

public:
	int weaponCount1;  //激光束武器路数    1 3
	int weaponCount2;  //光子鱼雷武器路数   1 3 5
	int weaponType;    //武器类型 1(激光束） 2(光子鱼雷)
};
#endif // Warship_h__
