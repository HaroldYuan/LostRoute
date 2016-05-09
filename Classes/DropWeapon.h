#ifndef DropWeapon_h__
#define DropWeapon_h__

#include "Drop.h"
#include "cocos2d.h"
USING_NS_CC;

class DropWeapon :public Drop
{
public:
	virtual bool init();

	CREATE_FUNC(DropWeapon);
};
#endif // DropWeapon_h__
