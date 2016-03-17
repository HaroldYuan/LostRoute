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

		//判断点击范围，点击飞机时，发生移动
		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		//扩大监听范围，降低点击的难度
		Rect rect = Rect(-10, -10, s.width + 10, s.height + 10);
		if (rect.containsPoint(locationInNode)){
			//未经过修正前的坐标
			auto newPosition = target->getPosition() + touch->getDelta();

			float halfwarshipWidth = target->getContentSize().width / 2;
			float halfwarshipHeight = target->getContentSize().height / 2;
			log("width= %f,height= %f", target->getContentSize().width, target->getContentSize().height);

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
	int weaponOffset[] = { 40, 20, 0, -20, -40 }; //激光束距离飞船水平中心点的距离
	for (int i = 0; i < weaponCount1; i++){
		auto weapon = WarshipWeapon1::create();

		auto index = i + 2 - weaponCount1 / 2;

		//设置激光束的起始坐标
		auto weaponStartX = getPositionX() - weaponOffset[index];
		auto weaponStartY = getPositionY() + getContentSize().height / 2 + weapon->getContentSize().height / 2;

		//设置激光束的初始位置
		weapon->setPosition(weaponStartX, weaponStartY);
		myWeaponLayer->addChild(weapon);
		myWeaponLayer->weaponContainer->addObject(weapon);

		//设置激光束移动速度
		//bug:导致飞机接近屏幕边缘，子弹无法从屏幕移除(飞机接时近边缘时，size.height - weaponStartY为负值）
		//auto moveDuration = 2 * (size.height - weaponStartY) / size.height;

		//设置激光束的终点坐标
		auto weaponEndX = weaponStartX;
		auto weaponEndY = size.height + weapon->getContentSize().height / 2;
		//设置激光束移动速度
		auto moveDuration = 2 * (weaponEndY - weaponStartY) / size.height;

		//MoveTo动作序列
		auto actionMove = MoveTo::create(moveDuration, Vec2(weaponEndX, weaponEndY));
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(WeaponLayer::weaponMovedFinished, myWeaponLayer));
		auto sequence = Sequence::create(actionMove, actionDone, nullptr);
		weapon->setVisible(true);
		weapon->runAction(sequence);
	}
}

void Warship::repeatShoot2(float dt){
	auto size = Director::getInstance()->getVisibleSize();
	int weaponOffset[] = { 20, 10, 0, -10, -20 }; //光子鱼雷距离飞船水平中心点的距离
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

		//设置光子鱼雷的起始坐标
		auto weaponStartX = getPositionX() + weaponOffset[index];
		auto weaponStartY = getPositionY() + getContentSize().height / 2 + weapon->getContentSize().height / 2;

		//设置光子鱼雷的初始位置
		weapon->setPosition(weaponStartX, weaponStartY);
		myWeaponLayer->addChild(weapon);
		myWeaponLayer->weaponContainer->addObject(weapon);

		//设置光子鱼雷终点坐标
		auto weaponEndX = getPositionX();
		auto weaponEndY = size.height + weapon->getContentSize().height / 2;
		weaponEndX += tan(weapon->getAngle(index)* PI / 180)*(getPositionY() + getContentSize().height / 2);

		//设置光子鱼雷移动速度
		auto moveDuration = 2 * (weaponEndY - weaponStartY) / size.height;
		//MoveTo 动作序列
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