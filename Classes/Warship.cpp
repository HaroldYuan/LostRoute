#include "Warship.h"
bool Warship::init(){
	if(!Sprite::init()){
		return false;
	}
	
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
	/*auto weapon=WarshipWeapon1::create();
	weapon->setPosition(100,200);
	addChild(weapon);*/

	//为飞船创建一种武器（光子鱼雷）

		auto weapon=WarshipWeapon2::create();
		weapon->setAngleIndex(1);
		weapon->setPosition(100,200);
		addChild(weapon);
	return true;
}

void Warship::setWeaponLayer(WeaponLayer* weaponLayer){
	WeaponLayer* myWeaponLayer = weaponLayer;
}

