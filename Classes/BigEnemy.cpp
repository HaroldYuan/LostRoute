#include "BigEnemy.h"
#include "Resources.h"
#include "WeaponLayer.h"
#include "BigEnemyWeapon.h"
#include "Explosion.h"

bool BigEnemy::init(){
	if (!Sprite::init()){
		return false;
	}
	auto enemyPath = PATH_BIGENEMY_PICTURE;
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_BIGENEMY_PICTURE);
	initWithSpriteFrame(spriteFrame);

	auto body = PhysicsBody::createBox(getContentSize());
	setPhysicsBody(body);

	body->setCategoryBitmask(0x01);       //0001
	body->setContactTestBitmask(0x03);    //0011
	body->setCollisionBitmask(0x02);      //0010

	currentHp = BigEnemy_MAX_HP;            //当前敌机的生命值
	maxHp = BigEnemy_MAX_HP;
	isWeapon = false;
	setTag(Enemy);
	return true;
}

void BigEnemy::shoot(){
	schedule(schedule_selector(BigEnemy::repeatShoot), 2.0);
}

void BigEnemy::repeatShoot(float dt){
	auto size = Director::getInstance()->getWinSize();
	auto myWeaponLayer = WeaponLayer::getInstance();

	auto leftWeapon = BigEnemyWeapon::create();
	auto rightWeapon = BigEnemyWeapon::create();

	//双排子弹起始坐标
	auto leftWeaponStartX = getPositionX() - (getContentSize().width*(1.0 / 5) + 2);
	auto leftWeaponStartY = getPositionY() - getContentSize().height / 2 - leftWeapon->getContentSize().height / 2;

	auto rightWeaponStartX = getPositionX() + (getContentSize().width*(1.0 / 5) + 2);
	auto rightWeaponStartY = getPositionY() - getContentSize().height / 2 - rightWeapon->getContentSize().height / 2;

	auto leftWeaponEndX = leftWeaponStartX;
	auto leftWeaponEndY = -leftWeapon->getContentSize().height / 2;

	auto rightWeaponEndX = rightWeaponStartX;
	auto rightWeaponEndY = -rightWeapon->getContentSize().height / 2;

	leftWeapon->setPosition(leftWeaponStartX, leftWeaponStartY);
	rightWeapon->setPosition(rightWeaponStartX, rightWeaponStartY);

	myWeaponLayer->addChild(leftWeapon);
	myWeaponLayer->addChild(rightWeapon);

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
	SimpleAudioEngine::getInstance()->playEffect(PATH_ENEMY_WEAPON_MUSIC, false);
}

void BigEnemy::clear(){
	stopAllActions();
	setVisible(false);
	node = nullptr;
	unscheduleAllSelectors();
}

void BigEnemy::explode(){
	Explosion explosion;
	explosion.explode(this, Enemy);
	SimpleAudioEngine::getInstance()->playEffect(PATH_ENEMY_EXPLOSION_MUSIC, false);
}