#include "BigEnemy.h"

bool BigEnemy::init(){
	if (!Sprite::init()){
		return false;
	}
	auto enemyPath = PATH_BIGENEMY_PICTURE;
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_BIGENEMY_PICTURE);
	initWithSpriteFrame(spriteFrame);
	hp = 10;
	maxHP = 10;
	return true;
}

void BigEnemy::shoot(){
	schedule(schedule_selector(BigEnemy::repeatShoot), 1.0);
}

void BigEnemy::repeatShoot(float dt){
	auto size = Director::getInstance()->getWinSize();

	auto leftWeapon = BigEnemyWeapon::create();
	auto rightWeapon = BigEnemyWeapon::create();

	//双排子弹起始坐标
	auto leftWeaponStartX = getPositionX() - (getContentSize().width*(1.0 / 5) + 2);
	auto leftWeaponStartY = getPositionY() - getContentSize().height / 2 - leftWeapon->getContentSize().height / 2;
	log("leftWeaponStartX= %f,leftWeaponStartY=%f", leftWeaponStartX, leftWeaponStartY);

	auto rightWeaponStartX = getPositionX() + (getContentSize().width*(1.0 / 5) + 2);
	auto rightWeaponStartY = getPositionY() - getContentSize().height / 2 - rightWeapon->getContentSize().height / 2;
	log("rightWeaponStartX= %f,rightWeaponStartY=%f", rightWeaponStartX, rightWeaponStartY);

	auto leftWeaponEndX = leftWeaponStartX;
	auto leftWeaponEndY = -leftWeapon->getContentSize().height / 2;

	auto rightWeaponEndX = rightWeaponStartX;
	auto rightWeaponEndY = -rightWeapon->getContentSize().height / 2;

	leftWeapon->setPosition(leftWeaponStartX, leftWeaponStartY);
	rightWeapon->setPosition(rightWeaponStartX, rightWeaponStartY);

	myWeaponLayer->addChild(leftWeapon);
	myWeaponLayer->addChild(rightWeapon);

	myWeaponLayer->weaponContainer->addObject(leftWeapon);
	myWeaponLayer->weaponContainer->addObject(rightWeapon);

	//子弹移动速度
	auto moveDuration = 2 * (leftWeaponStartY - leftWeaponEndY) / size.height;

	//动作序列
	auto actionLeftWeaponMove = MoveTo::create(moveDuration, Vec2(leftWeaponEndX, leftWeaponEndY));
	auto actionRightWeaponMove = MoveTo::create(moveDuration, Vec2(rightWeaponEndX, rightWeaponEndY));

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(WeaponLayer::weaponMovedFinished, myWeaponLayer));

	auto actionSequenceLeftWeapon = Sequence::create(actionLeftWeaponMove, actionDone, nullptr);
	auto actionSequenceRightWeapon = Sequence::create(actionRightWeaponMove, actionDone, nullptr);

	leftWeapon->runAction(actionSequenceLeftWeapon);
	rightWeapon->runAction(actionSequenceRightWeapon);
}

void BigEnemy::setWeaponLayer(WeaponLayer* mWeaponLayer){
	myWeaponLayer = mWeaponLayer;
}