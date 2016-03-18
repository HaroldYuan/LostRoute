#ifndef Warship_h__
#define Warship_h__

#include "cocos2d.h"
#include "Resources.h"
#include "BodyParent.h"
#include "WeaponLayer.h"
#include "WarshipWeapon1.h"
#include "WarshipWeapon2.h"
USING_NS_CC;

class Warship :public BodyParent
{
public:
	virtual bool init();

	void setWeaponLayer(WeaponLayer* weaponLayer);

	void shoot();

	//���伤����
	void repeatShoot1(float dt);

	//�����������
	void repeatShoot2(float dt);

	CREATE_FUNC(Warship);

public:
	int weaponCount1;  //����������·��    1 3
	int weaponCount2;  //������������·��   1 3 5
	int weaponType;    //�������� 1(�������� 2(��������)
};
#endif // Warship_h__
