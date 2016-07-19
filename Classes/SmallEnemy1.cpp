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

	currentHp = SmallEnemy1_MAX_HP;       //��ǰ�л�������ֵ
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
	//��������ת��
	weapon = WeaponLayer::getInstance()->produceSmallEnemyWeapon();
	if (weapon->getParent() == nullptr){
		WeaponLayer::getInstance()->addChild(weapon);
	}

	//�л��ӵ���ʼ����
	auto weaponStartX = getPositionX();
	auto weaponStartY = getPositionY() - getContentSize().height / 2 - weapon->getContentSize().height / 2;
	weapon->setPosition(weaponStartX, weaponStartY);

	//�л��ӵ��յ�����
	auto weaponEndX = weaponStartX;
	auto weaponEndY = -weapon->getContentSize().height / 2;

	//�л��ӵ��˶�ʱ��
	auto moveDuration = (weaponStartY - weaponEndY) / size.height;
	//��������
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