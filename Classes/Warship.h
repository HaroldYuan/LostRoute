#ifndef Warship_h__
#define Warship_h__

#include "cocos2d.h"
#include "Resources.h"
#include "BodyParent.h"
#include "WeaponLayer.h"
#include "WarshipWeapon1.h"
#include "WarshipWeapon2.h"
USING_NS_CC;

class Warship:public BodyParent
{
private:
	WeaponLayer* myWeaponLayer;
	int weaponCount;  //ÎäÆ÷Â·Êý 1 3 5
public:
	virtual bool init();

	void setWeaponLayer(WeaponLayer* weaponLayer);

	void shoot();

	void repeatShoot1(float dt);

	CREATE_FUNC(Warship);

};
#endif // Warship_h__
