#ifndef WarshipWeapon1_h__
#define WarshipWeapon1_h__

#include "cocos2d.h"
#include "Resources.h"
#include "BodyParent.h"
USING_NS_CC;

class WarshipWeapon1 :public BodyParent{
	friend class WeaponLayer;
public:
	virtual bool init();

	void clear();

	CREATE_FUNC(WarshipWeapon1);

public:
	bool swithweapon;
};
#endif // WarshipWeapon1_h__