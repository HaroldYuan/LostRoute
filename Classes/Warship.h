#ifndef Warship_h__
#define Warship_h__

#include "cocos2d.h"
#include "Resources.h"
#include "BodyParent.h"
#include "WeaponLayer.h"
#include "WarshipWeapon2.h"
#include "WarshipWeapon1.h"
USING_NS_CC;

class Warship :public BodyParent
{
public:
	virtual bool init();

	void setWeaponLayer(WeaponLayer* weaponLayer);

	void shoot();

	//���伤����
	void repeatShoot_lasor(float dt);

	//�����������
	void repeatShoot_torpedo(float dt);

	virtual void explode();

	CREATE_FUNC(Warship);

public:
	int weaponCount_lasor;  //����������·��   1 3 5
	int weaponType;    //�������� 1(�������� 2(��������)
};
#endif // Warship_h__
