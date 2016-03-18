#ifndef _Weapon_Layer
#define _Weapon_Layer
#include "Resources.h"
#include "cocos2d.h"
USING_NS_CC;

class WeaponLayer :public Layer
{
public:
	//WeaponLayer();

	static WeaponLayer* getInstance();

	virtual bool init();

	void weaponMovedFinished(Node* sender);

	//CREATE_FUNC(WeaponLayer);

	~WeaponLayer();

public:
	__Array *weaponContainer;  //保存当前所有正在飞行的武器

private:
	WeaponLayer();

private:
	static WeaponLayer* sharedWeaponLayer;
};
#endif // _Weapon_Layer
