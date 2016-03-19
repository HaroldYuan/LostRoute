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
	//WeaponLayer();

	static WeaponLayer* getInstance();

	virtual bool init();

	void weaponMovedFinished(Node* sender);

	//CREATE_FUNC(WeaponLayer);
	WarshipWeapon1* produceWarshipWeapon1();

	WarshipWeapon2* produceWarshipWeapon2();

	SmallEnemyWeapon* produceSmallEnemyWeapon();

	~WeaponLayer();

private:
	WeaponLayer();

public:
	__Array* weaponContainer;  //���浱ǰ�������ڷ��е�����

	__Array* warshipWeapon1_Pool;//����ɴ�����ļ�����

	__Array* warshipWeapon2_Pool;//����ɴ�����Ĺ�������

	__Array* smallEnemyWeapon_Pool;//����С�͵л�������ӵ�

private:
	static WeaponLayer* sharedWeaponLayer;
};
#endif // _Weapon_Layer
