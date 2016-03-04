#include "WarshipLayer.h"

bool WarshipLayer::init(){
	if (!Layer::init()){
		return false;
	}

	auto size = Director::getInstance()->getWinSize();
	warship = Warship::create();
	warship->setPosition(size.width / 2, size.height / 2);
	addChild(warship);

	//为飞船创建一种武器（激光束）
	/*auto weapon=WarshipWeapon1::create();
	weapon->setPosition(100,200);
	addChild(weapon);*/

	//为飞船创建一种武器（光子鱼雷）

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