#include "SmallEnemyWeapon.h"

bool SmallEnemyWeapon::init(){
	if (!Sprite::init()){
		return false;
	}
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_ENEMY_WEAPON1_PICTURE);
	initWithSpriteFrame(spriteFrame);

	auto body = PhysicsBody::createCircle(getContentSize().width / 2);
	setPhysicsBody(body);

	//1.允许碰撞：CategoryBitmask & CollisionBitmask！=0
	//2.调用onContactBegan 方法  CategoryBitmask & ContactTestBitmask！=0
	body->setCategoryBitmask(0x01);       //0001
	body->setContactTestBitmask(0x03);    //0011
	body->setCollisionBitmask(0x02);      //0010

	currentHp = 1;
	isWeapon = true;
	setTag(Enemy);
	return true;
}

void SmallEnemyWeapon::clear(){
	setVisible(false);
	stopAllActions();
}