#ifndef Warship_h__
#define Warship_h__

#include "cocos2d.h"
#include "Resources.h"
#include "BodyParent.h"
#include "WeaponLayer.h"
#include "WarshipWeapon2.h"
USING_NS_CC;

class Warship:public BodyParent
{
private:
	WeaponLayer* myWeaponLayer;
public:
	void setWeaponLayer(WeaponLayer* weaponLayer);
	virtual bool init();
	CREATE_FUNC(Warship);
};
#endif // Warship_h__
