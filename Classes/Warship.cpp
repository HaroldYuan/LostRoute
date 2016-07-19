#include "Warship.h"
#include "Explosion.h"

bool Warship::init(){
	if (!Sprite::init()){
		return false;
	}

	weaponCount_lasor = 3;
	weaponType = weapon_torpedo;
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_WARSHIP_1_PICTURE);
	initWithSpriteFrame(spriteFrame);

	auto body = PhysicsBody::createBox(getContentSize());
	setPhysicsBody(body);

	body->setCategoryBitmask(0x01);       //0001
	body->setContactTestBitmask(0x03);    //0011
	body->setCollisionBitmask(0x02);      //0010

	//移动飞船
	auto listener = EventListenerTouchOneByOne::create();

	//使用lambda表达式
	listener->onTouchBegan = [](Touch* touch, Event* event){
		return true;
	};

	listener->onTouchMoved = [](Touch* touch, Event* event){
		if (Director::getInstance()->isPaused()){
			return;
		}

		Size screenSize = Director::getInstance()->getVisibleSize();
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		//未经过修正前的坐标
		auto newPosition = target->getPosition() + touch->getDelta();

		float halfwarshipWidth = target->getContentSize().width / 2;
		float halfwarshipHeight = target->getContentSize().height / 2;

		float pos_X = newPosition.x;
		float pos_Y = newPosition.y;

		//判断横坐标是否超出屏幕范围
		if (pos_X < halfwarshipWidth){
			pos_X = halfwarshipWidth;
		}
		else if (pos_X>screenSize.width - halfwarshipWidth){
			pos_X = screenSize.width - halfwarshipWidth;
		}

		//判断纵坐标是否超出屏幕范围
		if (pos_Y < halfwarshipHeight){
			pos_Y = halfwarshipHeight;
		}
		else if (pos_Y>screenSize.height - halfwarshipHeight){
			pos_Y = screenSize.height - halfwarshipHeight;
		}

		//经过修正后的坐标
		auto correctPosition = Vec2(pos_X, pos_Y);

		target->setPosition(correctPosition);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	currentHp = WARSHIP_MAX_HP;
	maxHp = WARSHIP_MAX_HP;
	setTag(Hero);
	isWeapon = false;

	return true;
}

void Warship::repeatShoot_torpedo(float dt){
	auto size = Director::getInstance()->getWinSize();

	auto weapon = WeaponLayer::getInstance()->produceWarshipWeapon1();

	//设置光子鱼雷的起始坐标
	auto weaponStartX = getPositionX();
	auto weaponStartY = getPositionY() + getContentSize().height / 2 + weapon->getContentSize().height / 2;

	//设置光子鱼雷的初始位置
	weapon->setPosition(weaponStartX, weaponStartY);
	/*WeaponLayer::getInstance()->addChild(weapon);*/
	if (weapon->getParent() == nullptr){
		WeaponLayer::getInstance()->addChild(weapon);
	}
	//设置光子鱼雷移动速度
	//bug:导致飞机接近屏幕边缘，子弹无法从屏幕移除(飞机接时近边缘时，size.height - weaponStartY为负值）
	//auto moveDuration = 2 * (size.height - weaponStartY) / size.height;

	//设置光子鱼雷的终点坐标
	auto weaponEndX = weaponStartX;
	auto weaponEndY = size.height + weapon->getContentSize().height / 2;
	//设置光子鱼雷移动速度
	auto moveDuration = 2 * (weaponEndY - weaponStartY) / size.height;

	//MoveTo动作序列
	auto actionMove = MoveTo::create(moveDuration, Vec2(weaponEndX, weaponEndY));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(WeaponLayer::weaponMovedFinished, WeaponLayer::getInstance()));
	auto sequence = Sequence::create(actionMove, actionDone, nullptr);
	weapon->setVisible(true);
	weapon->runAction(sequence);
	SimpleAudioEngine::getInstance()->playEffect(PATH_WARSHIP_WEAPON_MUSIC);
}

void Warship::changeWeaponType(){
	weaponType = weapon_lasor;
	shoot();
	scheduleOnce(schedule_selector(Warship::resetWeapon), 8);
	SimpleAudioEngine::getInstance()->playEffect(PATH_SWITCHWEAPON_MUSIC, false);
}

void Warship::addHP(int delta_hp){
	if (currentHp + delta_hp <= WARSHIP_MAX_HP){
		currentHp += delta_hp;
	}
	else{
		currentHp = WARSHIP_MAX_HP;
	}
}

void Warship::resetWeapon(float dt){
	weaponType = weapon_torpedo;
	shoot();
	SimpleAudioEngine::getInstance()->playEffect(PATH_SWITCHWEAPON_MUSIC, false);
}

void Warship::repeatShoot_lasor(float dt){
	auto size = Director::getInstance()->getVisibleSize();
	int weaponOffset[] = { 40, 0, -40 }; //激光束距离飞船的偏移量
	for (int i = 0; i < weaponCount_lasor; i++){
		auto weapon = WeaponLayer::getInstance()->produceWarshipWeapon2();
		//weaponCount_lasor=1
		//index=1

		//weaponCount_lasor=3
		//index=0

		auto index = i + 1 - weaponCount_lasor / 2;
		weapon->setAngleIndex(index);

		//设置激光束的起始坐标
		auto weaponStartX = getPositionX() + weaponOffset[index];
		auto weaponStartY = getPositionY() + getContentSize().height / 2 + weapon->getContentSize().height / 2;

		//设置激光束的初始位置
		weapon->setPosition(weaponStartX, weaponStartY);
		if (weapon->getParent() == nullptr){
			WeaponLayer::getInstance()->addChild(weapon);
		}

		//设置激光束终点坐标
		auto weaponEndX = weaponStartX;
		auto weaponEndY = size.height + weapon->getContentSize().height / 2;
		weaponEndX += tan(weapon->getAngle(index)* PI / 180)*(size.height - getPositionY() - getContentSize().height / 2);

		//设置激光束移动速度
		auto moveDuration = 2 * (weaponEndY - weaponStartY) / size.height;
		//MoveTo 动作序列
		auto actionMove = MoveTo::create(moveDuration, Vec2(weaponEndX, weaponEndY));
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(WeaponLayer::weaponMovedFinished, WeaponLayer::getInstance()));
		auto sequence = Sequence::create(actionMove, actionDone, nullptr);

		weapon->runAction(sequence);
	}
	SimpleAudioEngine::getInstance()->playEffect(PATH_WARSHIP_WEAPON_MUSIC);
}

void Warship::explode(){
	Explosion explosion;
	explosion.explode(this, Hero);
	SimpleAudioEngine::getInstance()->playEffect(PATH_WARSHIP_EXPLOSION_MUSIC, false);
}

void Warship::shoot(){
	if (weaponType == weapon_lasor){
		if (isScheduled(schedule_selector(Warship::repeatShoot_lasor))){
			return;
		}
		if (isScheduled(schedule_selector(Warship::repeatShoot_torpedo))){
			unschedule(schedule_selector(Warship::repeatShoot_torpedo));
		}
		//根据激光束路数设置发射频率
		if (weaponCount_lasor == 1){
			schedule(schedule_selector(Warship::repeatShoot_lasor), 0.3);
		}
		else{
			schedule(schedule_selector(Warship::repeatShoot_lasor), 0.5);
		}
	}
	else{
		if (isScheduled(schedule_selector(Warship::repeatShoot_torpedo))){
			return;
		}
		if (isScheduled(schedule_selector(Warship::repeatShoot_lasor))){
			unschedule(schedule_selector(Warship::repeatShoot_lasor));
		}
		schedule(schedule_selector(Warship::repeatShoot_torpedo), 0.3);
	}
}