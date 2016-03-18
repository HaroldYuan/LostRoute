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
	__Array *weaponContainer;  //���浱ǰ�������ڷ��е�����

private:
	WeaponLayer();

private:
	static WeaponLayer* sharedWeaponLayer;
};
#endif // _Weapon_Layer
