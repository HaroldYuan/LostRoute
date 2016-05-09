#include "DropLayer.h"

bool DropLayer::init(){
	if (!Layer::init()){
		return false;
	}
	schedule(schedule_selector(DropLayer::generateDrop), 15);
	return true;
}

Drop* DropLayer::generateDropType(){
	Drop* drop = nullptr;

	auto rand_value = rand() % 100;
	if (rand_value <= 30){
		//增加生命值
		drop = DropLife::create();
	}
	else{
		//增强(切换)武器
		drop = DropWeapon::create();
	}
	return drop;
}

void DropLayer::generateDrop(float dt){
	Size size = Director::getInstance()->getWinSize();
	auto drop = generateDropType();

	if (drop == nullptr){
		return;
	}
	auto dropSize = drop->getContentSize();
	//drop横坐标最小值
	int min_X = dropSize.width / 2;

	//drop横坐标最大值
	int max_X = size.width - dropSize.width / 2;

	//BigEnemy横坐标取值范围
	int range_X = max_X - min_X;

	int startX = min_X + CCRANDOM_0_1()*range_X;

	drop->setPosition(Vec2(startX, size.height - dropSize.height));
	addChild(drop);
	int EndX = drop->getPositionX();
	int EndY = -drop->getContentSize().height / 2;

	auto actionMove = MoveTo::create(2, Vec2(EndX, EndY));
	auto actionDone = CallFunc::create([=](){
		drop->removeFromParent();
	});
	auto actionSequence = Sequence::create(actionMove, actionDone, nullptr);
	drop->runAction(actionSequence);
}