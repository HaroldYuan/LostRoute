#ifndef WarshipWeapon2_h__
#define WarshipWeapon2_h__

#include "cocos2d.h"
#include "Resources.h"
#include "BodyParent.h"
USING_NS_CC;

class WarshipWeapon2:public BodyParent{
public:
	virtual bool init();
	void setAngleIndex(int index);
	CREATE_FUNC(WarshipWeapon2);
private:
	int angles[2]; //�洢ÿһ·�������׵ĽǶ�
};
#endif // WarshipWeapon2_h__