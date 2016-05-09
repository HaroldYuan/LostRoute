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
		//��������ֵ
		drop = DropLife::create();
	}
	else{
		//��ǿ(�л�)����
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
	//drop��������Сֵ
	int min_X = dropSize.width / 2;

	//drop���������ֵ
	int max_X = size.width - dropSize.width / 2;

	//BigEnemy������ȡֵ��Χ
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