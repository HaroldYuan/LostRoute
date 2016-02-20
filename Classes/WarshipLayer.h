#ifndef WarshipLayer_h__
#define WarshipLayer_h__
#include "cocos2d.h"
#include "Resources.h"
#include "Warship.h"
USING_NS_CC;

class WarshipLayer:public Layer
{
public:
	void setWeaponLayer(WeaponLayer* weaponLayer);
	virtual bool init();
	CREATE_FUNC(WarshipLayer);
private:
	WeaponLayer* mWeaponLayer;
public:
	Warship* warship;
};
#endif // WarshipLayer_h__
