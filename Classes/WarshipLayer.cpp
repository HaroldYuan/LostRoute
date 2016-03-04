#include "WarshipLayer.h"

bool WarshipLayer::init(){
	if (!Layer::init()){
		return false;
	}

	auto size = Director::getInstance()->getWinSize();
	warship = Warship::create();
	warship->setPosition(size.width / 2, size.height / 2);
	addChild(warship);

	//Ϊ�ɴ�����һ����������������
	/*auto weapon=WarshipWeapon1::create();
	weapon->setPosition(100,200);
	addChild(weapon);*/

	//Ϊ�ɴ�����һ���������������ף�

	// 	auto weapon=WarshipWeapon2::create();
	// 	weapon->setAngleIndex(1);
	// 	weapon->setPosition(100,200);
	// 	addChild(weapon);

	return true;
}

void WarshipLayer::setWeaponLayer(WeaponLayer* weaponLayer){
	mWeaponLayer = weaponLayer;
	warship->setWeaponLayer(mWeaponLayer);
	warship->shoot();
}