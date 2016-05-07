#include "SmallEnemy2.h"
#include "Resources.h"
#include "WeaponLayer.h"
#include "SmallEnemyWeapon.h"
#include "Explosion.h"

void SmallEnemy2::explode(){
	Explosion explosion;
	explosion.explode(this, Enemy);
}

bool SmallEnemy2::init(){
	if (!Sprite::init()){
		return false;
	}
	auto enemyPath = PATH_SMALLENEMY1_PICTURE;
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(enemyPath);
	initWithSpriteFrame(spriteFrame);
	auto height = getContentSize().height;
	auto width = getContentSize().width;
	Vec2 points[] = { Vec2(0, height / 2), Vec2(width / 2, -height / 2), Vec2(-width / 2, -height / 2), };
	auto body = PhysicsBody::createPolygon(points, 3);
	setPhysicsBody(body);
	setRotation(180);

	body->setCategoryBitmask(0x01);       //0001
	body->setContactTestBitmask(0x03);    //0011
	body->setCollisionBitmask(0x02);      //0010

	hp = SmallEnemy2_MAX_HP;          //当前敌机的生命值
	isWeapon = false;
	setTag(Enemy);
	return true;
}

void SmallEnemy2::clear(){
	stopAllActions();
	setVisible(false);
	node = nullptr;
	missle = nullptr;
	selected = false;
	unscheduleAllSelectors();
}