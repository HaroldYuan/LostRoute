#include "BigEnemyWeapon.h"

bool BigEnemyWeapon::init(){
	if (!Sprite::init()){
		return false;
	}
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_ENEMY_WEAPON2_PICTURE);
	initWithSpriteFrame(spriteFrame);

	auto body = PhysicsBody::createBox(getContentSize());
	setPhysicsBody(body);

	body->setCategoryBitmask(0x01);       //0001
	body->setContactTestBitmask(0x03);    //0011
	body->setCollisionBitmask(0x02);      //0010

	hp = 3;
	isWeapon = true;
	setTag(Enemy);
	return true;
}