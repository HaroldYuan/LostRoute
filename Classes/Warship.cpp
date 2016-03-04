#include "Warship.h"

bool Warship::init(){
	if(!Sprite::init()){
		return false;
	}

	weaponCount = 5;
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_WARSHIP_1_PICTURE);
	initWithSpriteFrame(spriteFrame);
	
	//移动飞船
	auto listener=EventListenerTouchOneByOne::create();

	//使用lambda表达式
	listener->onTouchBegan=[=](Touch* touch,Event* event){
		return true;
	};

	listener->onTouchMoved=[](Touch* touch,Event* event){
		if(Director::getInstance()->isPaused()){
			return ;
		}
		auto target=static_cast<Sprite*>(event->getCurrentTarget());
		target->setPosition(target->getPosition()+touch->getDelta());
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	hp = WARSHIP_MAX_HP;

	//为飞船创建一种武器（激光束）
// 	auto weapon=WarshipWeapon1::create();
// 	weapon->setPosition(100,200);
// 	addChild(weapon);

	//为飞船创建一种武器（光子鱼雷）

// 	auto weapon=WarshipWeapon2::create();
// 	weapon->setAngleIndex(1);
// 	weapon->setPosition(100,200);
// 	addChild(weapon);
	return true;
}

void Warship::setWeaponLayer(WeaponLayer* weaponLayer){
	myWeaponLayer = weaponLayer;
}

void Warship::repeatShoot1(float dt){
	auto size = Director::getInstance()->getWinSize();
	int weaponOffset[] = { 20, 10, 0, -10, -20 }; //光子鱼雷距离飞船水平中心点的距离
	for (int i = 0; i < weaponCount; i++){
		auto weapon = WarshipWeapon2::create();
		//weaponCount=1
		//index=2

		//weaponCount=3
		//index=1

		//weaponCount=5
		//index=0

		auto index = i + 2 - weaponCount / 2;
		weapon->setAngleIndex(index);

		//设置光子鱼雷的起始坐标
		auto weaponStartX = getPositionX() +weaponOffset[index];
		auto weaponStartY = getPositionY() + getContentSize().height / 3;
		weapon->setPosition(weaponStartX, weaponStartY);
		myWeaponLayer->addChild(weapon);

		//设置光子鱼雷移动速度
		auto moveDuration = 2 * (size.height - weaponStartY) / size.height;

		//设置光子鱼雷终点坐标
		auto weaponEndX = getPositionX();
		auto weaponEndY = size.height + weapon->getContentSize().height / 2;
		weaponEndX += tan(weapon->getAngle(index)* PI / 180)*(getPositionY() + getContentSize().height / 2);

		//MoveTo 动作序列
		auto actionMove = MoveTo::create(moveDuration, Vec2(weaponEndX, weaponEndY));
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(WeaponLayer::weaponMovedFinished, myWeaponLayer));
		auto sequence = Sequence::create(actionMove, actionDone, nullptr);
		myWeaponLayer->weaponContainer->addObject(weapon);
		weapon->setVisible(true);
		weapon->runAction(sequence);
	}
}

void Warship::shoot(){
	schedule(schedule_selector(Warship::repeatShoot1),0.3);
}



