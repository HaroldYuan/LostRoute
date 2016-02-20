#ifndef WarshipWeapon1_h__
#define WarshipWeapon1_h__

#include "cocos2d.h"
#include "Resources.h"
#include "BodyParent.h"
USING_NS_CC;

class WarshipWeapon1:public BodyParent{
public:
	virtual bool init();
	CREATE_FUNC(WarshipWeapon1);
	bool swithweapon;
};
#endif // WarshipWeapon1_h__