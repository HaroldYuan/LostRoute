#include "SmallEnemy.h"

bool SmallEnemy::init(){
	if (!Sprite::init()){
		return false;
	}
	auto enemyPath = PATH_SMALLENEMY1_PICTURE;
	if (rand() % 10000 > 5000){
		enemyPath = PATH_SMALLENEMY2_PICTURE;
		EnemyTag = 2;
	}
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(enemyPath);
	initWithSpriteFrame(spriteFrame);

	hp = 4;
	maxHP = 4;
	isWeapon = true;
	return true;
}

void SmallEnemy::setWeaponLayer(WeaponLayer* mWeaponLayer){
	myWeaponLayer = mWeaponLayer;
}

void SmallEnemy::shoot(){
	schedule(schedule_selector(SmallEnemy::repeatShoot), 0.6);
}

void SmallEnemy::repeatShoot(float dt){
	auto size = Director::getInstance()->getWinSize();
	Sprite* weapon = nullptr;
	//向上类型转换
	weapon = SmallEnemyWeapon::create();
	myWeaponLayer->addChild(weapon);
	myWeaponLayer->weaponContainer->addObject(weapon);

	//敌机子弹起始坐标
	auto weaponStartX = getPositionX();
	auto weaponStartY = getPositionY() - getContentSize().height / 2 - weapon->getContentSize().height / 2;
	weapon->setPosition(weaponStartX, weaponStartY);

	//敌机子弹终点坐标
	auto weaponEndX = weaponStartX;
	// 	float value = rand() % 100;
	// 	if (value < 15){
	// 		//敌机子弹运动轨迹向左偏
	// 		weaponEndX = rand() % (int)weaponEndX;
	// 	}
	// 	else if (value>85){
	// 		//敌机子弹运动轨迹向右偏
	// 		weaponEndX = weaponEndX + rand() % (int)(size.width - weaponEndX);
	// 	}

	auto weaponEndY = -weapon->getContentSize().height / 2;

	//敌机子弹运动时间
	UpdateTimeCount += dt;
	//auto moveDuration = (weaponStartY - weaponEndY) / size.height;
	auto moveDuration = (duration - UpdateTimeCount) * 1 / 4;

	//动作序列
	auto actionMove = MoveTo::create(moveDuration, Vec2(weaponEndX, weaponEndY));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(WeaponLayer::weaponMovedFinished, myWeaponLayer));
	auto sequence = Sequence::create(actionMove, actionDone, nullptr);

	weapon->runAction(sequence);
}

int SmallEnemy::getEnemyTag() const{
	return EnemyTag;
}

void SmallEnemy::setEnemyTag(int tag){
	if (tag >= 1 && tag <= 2){
		EnemyTag = tag;
	}
	else{
		tag = 1;
	}
}

void SmallEnemy::clear(){
	UpdateTimeCount = 0;
	stopAllActions();
	setVisible(false);
	node = nullptr;
	missle = nullptr;
	selected = false;
	unscheduleAllSelectors();
}