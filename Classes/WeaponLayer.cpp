#include "WeaponLayer.h"
#include "BodyParent.h"

WeaponLayer* WeaponLayer::sharedWeaponLayer = nullptr;

WeaponLayer::WeaponLayer(){
	weaponContainer = __Array::create();
	weaponContainer->retain();

	warshipWeapon1_Pool = __Array::create();
	warshipWeapon1_Pool->retain();

	warshipWeapon2_Pool = __Array::create();
	warshipWeapon2_Pool->retain();

	smallEnemyWeapon_Pool = __Array::create();
	smallEnemyWeapon_Pool->retain();
}

WeaponLayer* WeaponLayer::getInstance(){
	if (sharedWeaponLayer == nullptr){
		sharedWeaponLayer = new WeaponLayer();
		if (sharedWeaponLayer &&  sharedWeaponLayer->init()){
			sharedWeaponLayer->autorelease();
			return sharedWeaponLayer;
		}
		else
		{
			delete sharedWeaponLayer;
			sharedWeaponLayer = nullptr;
			return nullptr;
		}
	}
	return sharedWeaponLayer;
}

bool WeaponLayer::init(){
	if (!Layer::init()){
		return false;
	}

	return true;
}

void WeaponLayer::weaponMovedFinished(Node* sender){
	auto weapon = dynamic_cast<BodyParent*>(sender);
	if (weapon != nullptr){
		weaponContainer->removeObject(weapon);
		auto wshipWeapon1 = dynamic_cast<WarshipWeapon1*>(weapon);
		if (wshipWeapon1 != nullptr){
			wshipWeapon1->clear();
			warshipWeapon1_Pool->addObject(wshipWeapon1);
		}
		auto wshipWeapon2 = dynamic_cast<WarshipWeapon2*>(weapon);
		if (wshipWeapon2 != nullptr){
			wshipWeapon2->clear();
			warshipWeapon2_Pool->addObject(wshipWeapon2);
		}
		auto sEnenmyWeapon = dynamic_cast<SmallEnemyWeapon*>(weapon);
		if (sEnenmyWeapon != nullptr){
			sEnenmyWeapon->clear();
			smallEnemyWeapon_Pool->addObject(sEnenmyWeapon);
		}
	}
}

WarshipWeapon1* WeaponLayer::produceWarshipWeapon1(){
	WarshipWeapon1* weapon = nullptr;
	if (warshipWeapon1_Pool->count() > 0){
		weapon = dynamic_cast<WarshipWeapon1*>(warshipWeapon1_Pool->getLastObject());
		warshipWeapon1_Pool->removeLastObject();
	}
	else{
		weapon = WarshipWeapon1::create();
	}
	weapon->setVisible(true);
	return weapon;
}

WarshipWeapon2* WeaponLayer::produceWarshipWeapon2(){
	WarshipWeapon2* weapon = nullptr;
	if (warshipWeapon2_Pool->count() > 0){
		weapon = dynamic_cast<WarshipWeapon2*>(warshipWeapon2_Pool->getLastObject());
		warshipWeapon2_Pool->removeLastObject();
	}
	else{
		weapon = WarshipWeapon2::create();
	}
	weapon->setVisible(true);
	return weapon;
}

SmallEnemyWeapon* WeaponLayer::produceSmallEnemyWeapon(){
	SmallEnemyWeapon* weapon = nullptr;
	if (smallEnemyWeapon_Pool->count() > 0){
		weapon = dynamic_cast<SmallEnemyWeapon*>(smallEnemyWeapon_Pool->getLastObject());
		smallEnemyWeapon_Pool->removeLastObject();
	}
	else{
		weapon = SmallEnemyWeapon::create();
	}
	weapon->setVisible(true);
	return weapon;
}

WeaponLayer::~WeaponLayer(){
	//weaponContainer->removeAllObjects();
	weaponContainer->release();
	weaponContainer = nullptr;

	warshipWeapon1_Pool->release();
	warshipWeapon1_Pool = nullptr;

	warshipWeapon2_Pool->release();
	warshipWeapon2_Pool = nullptr;

	smallEnemyWeapon_Pool->release();
	smallEnemyWeapon_Pool = nullptr;
}