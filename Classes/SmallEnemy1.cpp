#include "SmallEnemy1.h"
#include "Resources.h"
#include "WeaponLayer.h"
#include "SmallEnemyWeapon.h"
#include "explosion.h"

bool SmallEnemy1::init(){
	if (!Sprite::init()){
		return false;
	}
	auto enemyPath = PATH_SMALLENEMY2_PICTURE;
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

	currentHp = SmallEnemy1_MAX_HP;       //当前敌机的生命值
	isWeapon = false;
	setTag(Enemy);
	return true;
}

void SmallEnemy1::shoot(){
	schedule(schedule_selector(SmallEnemy1::repeatShoot), 1);
}

void SmallEnemy1::repeatShoot(float dt){
	auto size = Director::getInstance()->getWinSize();
	Sprite* weapon = nullptr;
	//向上类型转换
	weapon = WeaponLayer::getInstance()->produceSmallEnemyWeapon();
	if (weapon->getParent() == nullptr){
		WeaponLayer::getInstance()->addChild(weapon);
	}

	//敌机子弹起始坐标
	auto weaponStartX = getPositionX();
	auto weaponStartY = getPositionY() - getContentSize().height / 2 - weapon->getContentSize().height / 2;
	weapon->setPosition(weaponStartX, weaponStartY);

	//敌机子弹终点坐标
	auto weaponEndX = weaponStartX;
	auto weaponEndY = -weapon->getContentSize().height / 2;

	//敌机子弹运动时间
	auto moveDuration = (weaponStartY - weaponEndY) / size.height;
	//动作序列
	auto actionMove = MoveTo::create(moveDuration, Vec2(weaponEndX, weaponEndY));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(WeaponLayer::weaponMovedFinished, WeaponLayer::getInstance()));
	auto sequence = Sequence::create(actionMove, actionDone, nullptr);

	weapon->runAction(sequence);
	SimpleAudioEngine::getInstance()->playEffect(PATH_ENEMY_WEAPON_MUSIC, false);
}

void SmallEnemy1::explode(){
	Explosion explosion;
	explosion.explode(this, Enemy);
	SimpleAudioEngine::getInstance()->playEffect(PATH_ENEMY_EXPLOSION_MUSIC, false);
}

void SmallEnemy1::clear(){
	stopAllActions();
	setVisible(false);
	node = nullptr;
	unscheduleAllSelectors();
}