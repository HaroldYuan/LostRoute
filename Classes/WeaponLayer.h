#ifndef _Weapon_Layer
#define _Weapon_Layer
#include "Resources.h"
#include "cocos2d.h"
#include "WarshipWeapon2.h"
#include "WarshipWeapon1.h"
#include "SmallEnemyWeapon.h"
USING_NS_CC;

class WeaponLayer :public Layer
{
public:

	static WeaponLayer* getInstance();

	virtual bool init();

	void weaponMovedFinished(Node* sender);

	WarshipWeapon1* produceWarshipWeapon1();

	WarshipWeapon2* produceWarshipWeapon2();

	SmallEnemyWeapon* produceSmallEnemyWeapon();

	~WeaponLayer();

private:
	WeaponLayer();

public:
	__Array* warshipWeapon1_Pool;//保存飞船发射的激光束

	__Array* warshipWeapon2_Pool;//保存飞船发射的光子鱼雷

	__Array* smallEnemyWeapon_Pool;//保存小型敌机发射的子弹

private:
	static WeaponLayer* sharedWeaponLayer;
};
#endif // _Weapon_Layer
