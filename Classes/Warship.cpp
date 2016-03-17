#include "Warship.h"

bool Warship::init(){
	if (!Sprite::init()){
		return false;
	}

	weaponCount1 = 1;
	weaponCount2 = 1;
	weaponType = weapon_torpedo;
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_WARSHIP_1_PICTURE);
	initWithSpriteFrame(spriteFrame);

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

		//�жϵ����Χ������ɻ�ʱ�������ƶ�
		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		//���������Χ�����͵�����Ѷ�
		Rect rect = Rect(-10, -10, s.width + 10, s.height + 10);
		if (rect.containsPoint(locationInNode)){
			//δ��������ǰ������
			auto newPosition = target->getPosition() + touch->getDelta();

			float halfwarshipWidth = target->getContentSize().width / 2;
			float halfwarshipHeight = target->getContentSize().height / 2;
			log("width= %f,height= %f", target->getContentSize().width, target->getContentSize().height);

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
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	hp = WARSHIP_MAX_HP;

	return true;
}

void Warship::setWeaponLayer(WeaponLayer* weaponLayer){
	myWeaponLayer = weaponLayer;
}

void Warship::repeatShoot1(float dt){
	auto size = Director::getInstance()->getWinSize();
	int weaponOffset[] = { 40, 20, 0, -20, -40 }; //����������ɴ�ˮƽ���ĵ�ľ���
	for (int i = 0; i < weaponCount1; i++){
		auto weapon = WarshipWeapon1::create();

		auto index = i + 2 - weaponCount1 / 2;

		//���ü���������ʼ����
		auto weaponStartX = getPositionX() - weaponOffset[index];
		auto weaponStartY = getPositionY() + getContentSize().height / 2 + weapon->getContentSize().height / 2;

		//���ü������ĳ�ʼλ��
		weapon->setPosition(weaponStartX, weaponStartY);
		myWeaponLayer->addChild(weapon);
		myWeaponLayer->weaponContainer->addObject(weapon);

		//���ü������ƶ��ٶ�
		//bug:���·ɻ��ӽ���Ļ��Ե���ӵ��޷�����Ļ�Ƴ�(�ɻ���ʱ����Եʱ��size.height - weaponStartYΪ��ֵ��
		//auto moveDuration = 2 * (size.height - weaponStartY) / size.height;

		//���ü��������յ�����
		auto weaponEndX = weaponStartX;
		auto weaponEndY = size.height + weapon->getContentSize().height / 2;
		//���ü������ƶ��ٶ�
		auto moveDuration = 2 * (weaponEndY - weaponStartY) / size.height;

		//MoveTo��������
		auto actionMove = MoveTo::create(moveDuration, Vec2(weaponEndX, weaponEndY));
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(WeaponLayer::weaponMovedFinished, myWeaponLayer));
		auto sequence = Sequence::create(actionMove, actionDone, nullptr);
		weapon->setVisible(true);
		weapon->runAction(sequence);
	}
}

void Warship::repeatShoot2(float dt){
	auto size = Director::getInstance()->getVisibleSize();
	int weaponOffset[] = { 20, 10, 0, -10, -20 }; //�������׾���ɴ�ˮƽ���ĵ�ľ���
	for (int i = 0; i < weaponCount2; i++){
		auto weapon = WarshipWeapon2::create();
		//weaponCount=1
		//index=2

		//weaponCount=3
		//index=1

		//weaponCount=5
		//index=0

		auto index = i + 2 - weaponCount2 / 2;
		weapon->setAngleIndex(index);

		//���ù������׵���ʼ����
		auto weaponStartX = getPositionX() + weaponOffset[index];
		auto weaponStartY = getPositionY() + getContentSize().height / 2 + weapon->getContentSize().height / 2;

		//���ù������׵ĳ�ʼλ��
		weapon->setPosition(weaponStartX, weaponStartY);
		myWeaponLayer->addChild(weapon);
		myWeaponLayer->weaponContainer->addObject(weapon);

		//���ù��������յ�����
		auto weaponEndX = getPositionX();
		auto weaponEndY = size.height + weapon->getContentSize().height / 2;
		weaponEndX += tan(weapon->getAngle(index)* PI / 180)*(getPositionY() + getContentSize().height / 2);

		//���ù��������ƶ��ٶ�
		auto moveDuration = 2 * (weaponEndY - weaponStartY) / size.height;
		//MoveTo ��������
		auto actionMove = MoveTo::create(moveDuration, Vec2(weaponEndX, weaponEndY));
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(WeaponLayer::weaponMovedFinished, myWeaponLayer));
		auto sequence = Sequence::create(actionMove, actionDone, nullptr);

		//weapon->setVisible(true);
		weapon->runAction(sequence);
	}
}

void Warship::shoot(){
	if (weaponType == weapon_lasor){
		if (isScheduled(schedule_selector(Warship::repeatShoot1))){
			return;
		}
		if (isScheduled(schedule_selector(Warship::repeatShoot2))){
			unschedule(schedule_selector(Warship::repeatShoot2));
		}
		schedule(schedule_selector(Warship::repeatShoot1), 0.3);
	}
	else{
		if (isScheduled(schedule_selector(Warship::repeatShoot2))){
			return;
		}
		if (isScheduled(schedule_selector(Warship::repeatShoot1))){
			unschedule(schedule_selector(Warship::repeatShoot1));
		}
		schedule(schedule_selector(Warship::repeatShoot2), 0.5);
	}
	//schedule(schedule_selector(Warship::repeatShoot1), 0.3);
}