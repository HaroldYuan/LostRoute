#include "WarshipWeapon2.h"

bool WarshipWeapon2::init(){
	if (!Sprite::init()){
		return false;
	}
	angles[0] = 12;
	angles[1] = 0;
	angles[2] = -12;
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_WARSHIP_WEAPON2_PICTURE);
	initWithSpriteFrame(spriteFrame);

	auto body = PhysicsBody::createBox(getContentSize());
	setPhysicsBody(body);

	body->setCategoryBitmask(0x01);       //0001
	body->setContactTestBitmask(0x03);    //0011
	body->setCollisionBitmask(0x02);      //0010

	currentHp = 2;
	maxHp = 2;
	isWeapon = true;
	setTag(Hero);
	return true;
}

void WarshipWeapon2::setAngleIndex(int index){
	if (index >= 0 && index <= 2){
		setRotation(angles[index]);
	}
}

int WarshipWeapon2::getAngle(int index){
	if (index >= 0 && index <= 2){
		return angles[index];
	}
	else{
		return angles[0];
	}
}

void WarshipWeapon2::clear(){
	setVisible(false);
	stopAllActions();
}