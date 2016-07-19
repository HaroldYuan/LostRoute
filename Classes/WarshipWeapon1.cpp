#include "WarshipWeapon1.h"

bool WarshipWeapon1::init(){
	if (!Sprite::init()){
		return false;
	}
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_WARSHIP_WEAPON1_PICTURE);
	initWithSpriteFrame(spriteFrame);

	auto body = PhysicsBody::createBox(getContentSize());
	setPhysicsBody(body);

	body->setCategoryBitmask(0x01);       //0001
	body->setContactTestBitmask(0x03);    //0011
	body->setCollisionBitmask(0x02);      //0010

	currentHp = 1;
	maxHp = 1;
	isWeapon = true;
	setTag(Hero);
	return true;
}

void WarshipWeapon1::clear(){
	setVisible(false);
	stopAllActions();
}