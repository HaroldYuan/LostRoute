#include "smallEnenmy.h"

bool SmallEnenmy::init(){
	if (!Sprite::init()){
		return false;
	}
	auto enemyPath = PATH_SMALLENEMY1_PICTURE;
	srand((unsigned)time(0));
	if (rand() % 100 > 50){
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

void SmallEnenmy::setWeaponLayer(WeaponLayer* mWeaponLayer){
	myWeaponLayer = mWeaponLayer;
}

void SmallEnenmy::shoot(){
	schedule(schedule_selector(SmallEnenmy::repeatShoot), 1.0);
}

void SmallEnenmy::repeatShoot(float dt){
	auto size = Director::getInstance()->getWinSize();
	Sprite* weapon = nullptr;
	if (getEnemyTag() == 1){
		//向上类型转换
		weapon = SmallEnemyWeapon1::create();
	}
	else{
		weapon = SmallEnemyWeapon2::create();
	}
	myWeaponLayer->addChild(weapon);
	myWeaponLayer->weaponContainer->addObject(weapon);

	//敌机子弹起始坐标
	auto weaponStartX = getPositionX();
	auto weaponStartY = getPositionY() - getContentSize().height / 2 - weapon->getContentSize().height / 2;
	weapon->setPosition(weaponStartX, weaponStartY);

	//敌机子弹终点坐标
	auto weaponEndX = weaponStartX;
	float value = rand() % 100;
	if (value < 15){
		//敌机子弹运动轨迹向左偏
		weaponEndX = rand() % (int)weaponEndX;
	}
	else if (value>85){
		//敌机子弹运动轨迹向右偏
		weaponEndX = weaponEndX + rand() % (int)(size.width - weaponEndX);
	}

	auto weaponEndY = -weapon->getContentSize().height / 2;

	//敌机子弹运动速度
	auto moveDuration = 2 * (weaponStartY - weaponEndY) / size.height;

	//动作序列
	auto actionMove = MoveTo::create(moveDuration, Vec2(weaponEndX, weaponEndY));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(WeaponLayer::weaponMovedFinished, myWeaponLayer));
	auto sequence = Sequence::create(actionMove, actionDone, nullptr);

	weapon->runAction(sequence);
}

int SmallEnenmy::getEnemyTag() const{
	return EnemyTag;
}

void SmallEnenmy::setEnemyTag(int tag){
	if (tag >= 1 && tag <= 2){
		EnemyTag = tag;
	}
	else{
		tag = 1;
	}
}