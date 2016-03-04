#include "WeaponLayer.h"
#include "BodyParent.h"

WeaponLayer::WeaponLayer(){
	weaponContainer = __Array::create();
	weaponContainer->retain();
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
	weaponContainer->release();
	weaponContainer = nullptr;
}