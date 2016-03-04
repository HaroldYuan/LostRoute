#include "Warship.h"

bool Warship::init(){
	if(!Sprite::init()){
		return false;
	}

	weaponCount = 5;
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_WARSHIP_1_PICTURE);
	initWithSpriteFrame(spriteFrame);
	
	//�ƶ��ɴ�
	auto listener=EventListenerTouchOneByOne::create();

	//ʹ��lambda���ʽ
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

	//Ϊ�ɴ�����һ����������������
// 	auto weapon=WarshipWeapon1::create();
// 	weapon->setPosition(100,200);
// 	addChild(weapon);

	//Ϊ�ɴ�����һ���������������ף�

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
	int weaponOffset[] = { 20, 10, 0, -10, -20 }; //�������׾���ɴ�ˮƽ���ĵ�ľ���
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

		//���ù������׵���ʼ����
		auto weaponStartX = getPositionX() +weaponOffset[index];
		auto weaponStartY = getPositionY() + getContentSize().height / 3;
		weapon->setPosition(weaponStartX, weaponStartY);
		myWeaponLayer->addChild(weapon);

		//���ù��������ƶ��ٶ�
		auto moveDuration = 2 * (size.height - weaponStartY) / size.height;

		//���ù��������յ�����
		auto weaponEndX = getPositionX();
		auto weaponEndY = size.height + weapon->getContentSize().height / 2;
		weaponEndX += tan(weapon->getAngle(index)* PI / 180)*(getPositionY() + getContentSize().height / 2);

		//MoveTo ��������
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



