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

	//�ƶ��ɴ�
	auto listener = EventListenerTouchOneByOne::create();

	//ʹ��lambda���ʽ
	listener->onTouchBegan = [](Touch* touch, Event* event){
		return true;
	};

	listener->onTouchMoved = [](Touch* touch, Event* event){
		if (Director::getInstance()->isPaused()){
			return;
		}

		Size screenSize = Director::getInstance()->getVisibleSize();
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		//δ��������ǰ������
		auto newPosition = target->getPosition() + touch->getDelta();

		float halfwarshipWidth = target->getContentSize().width / 2;
		float halfwarshipHeight = target->getContentSize().height / 2;

		float pos_X = newPosition.x;
		float pos_Y = newPosition.y;

		//�жϺ������Ƿ񳬳���Ļ��Χ
		if (pos_X < halfwarshipWidth){
			pos_X = halfwarshipWidth;
		}
		else if (pos_X>screenSize.width - halfwarshipWidth){
			pos_X = screenSize.width - halfwarshipWidth;
		}

		//�ж��������Ƿ񳬳���Ļ��Χ
		if (pos_Y < halfwarshipHeight){
			pos_Y = halfwarshipHeight;
		}
		else if (pos_Y>screenSize.height - halfwarshipHeight){
			pos_Y = screenSize.height - halfwarshipHeight;
		}

		//���������������
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

	//���ù������׵���ʼ����
	auto weaponStartX = getPositionX();
	auto weaponStartY = getPositionY() + getContentSize().height / 2 + weapon->getContentSize().height / 2;

	//���ù������׵ĳ�ʼλ��
	weapon->setPosition(weaponStartX, weaponStartY);
	/*WeaponLayer::getInstance()->addChild(weapon);*/
	if (weapon->getParent() == nullptr){
		WeaponLayer::getInstance()->addChild(weapon);
	}
	//���ù��������ƶ��ٶ�
	//bug:���·ɻ��ӽ���Ļ��Ե���ӵ��޷�����Ļ�Ƴ�(�ɻ���ʱ����Եʱ��size.height - weaponStartYΪ��ֵ��
	//auto moveDuration = 2 * (size.height - weaponStartY) / size.height;

	//���ù������׵��յ�����
	auto weaponEndX = weaponStartX;
	auto weaponEndY = size.height + weapon->getContentSize().height / 2;
	//���ù��������ƶ��ٶ�
	auto moveDuration = 2 * (weaponEndY - weaponStartY) / size.height;

	//MoveTo��������
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
	int weaponOffset[] = { 40, 0, -40 }; //����������ɴ���ƫ����
	for (int i = 0; i < weaponCount_lasor; i++){
		auto weapon = WeaponLayer::getInstance()->produceWarshipWeapon2();
		//weaponCount_lasor=1
		//index=1

		//weaponCount_lasor=3
		//index=0

		auto index = i + 1 - weaponCount_lasor / 2;
		weapon->setAngleIndex(index);

		//���ü���������ʼ����
		auto weaponStartX = getPositionX() + weaponOffset[index];
		auto weaponStartY = getPositionY() + getContentSize().height / 2 + weapon->getContentSize().height / 2;

		//���ü������ĳ�ʼλ��
		weapon->setPosition(weaponStartX, weaponStartY);
		if (weapon->getParent() == nullptr){
			WeaponLayer::getInstance()->addChild(weapon);
		}

		//���ü������յ�����
		auto weaponEndX = weaponStartX;
		auto weaponEndY = size.height + weapon->getContentSize().height / 2;
		weaponEndX += tan(weapon->getAngle(index)* PI / 180)*(size.height - getPositionY() - getContentSize().height / 2);

		//���ü������ƶ��ٶ�
		auto moveDuration = 2 * (weaponEndY - weaponStartY) / size.height;
		//MoveTo ��������
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
		//���ݼ�����·�����÷���Ƶ��
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