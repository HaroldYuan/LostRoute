#include "WeaponLayer.h"
#include "BodyParent.h"

WeaponLayer* WeaponLayer::sharedWeaponLayer = nullptr;

WeaponLayer::WeaponLayer(){
	weaponContainer = __Array::create();
	weaponContainer->retain();
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
		removeChild(weapon, true);
		weaponContainer->removeObject(weapon);
	}
}

WeaponLayer::~WeaponLayer(){
	//weaponContainer->removeAllObjects();
	weaponContainer->release();
	weaponContainer = nullptr;
}