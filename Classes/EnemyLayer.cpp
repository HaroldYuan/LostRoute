#include "EnemyLayer.h"

EnemyLayer::EnemyLayer(){
	enemyContainer = __Array::create();
	enemyContainer->retain();

	smallEnemy1_Pool = __Array::create();
	smallEnemy1_Pool->retain();

	smallEnemy2_Pool = __Array::create();
	smallEnemy2_Pool->retain();

	bigEnemy_Pool = __Array::create();
	bigEnemy_Pool->retain();
}

EnemyLayer::~EnemyLayer(){
	CC_SAFE_RELEASE_NULL(enemyContainer);
	CC_SAFE_RELEASE_NULL(smallEnemy1_Pool);
	CC_SAFE_RELEASE_NULL(smallEnemy2_Pool);
	CC_SAFE_RELEASE_NULL(bigEnemy_Pool);
}

bool EnemyLayer::init(){
	if (!Layer::init()){
		return false;
	}
	for (int Index = 0; Index < arraySize; Index++){
		statusArray[Index] = false;
	}
	schedule(schedule_selector(EnemyLayer::statusUpdate), 3.0);
	schedule(schedule_selector(EnemyLayer::EnemyMove), 6.0);
	return true;
}

//随机调度一个飞行路径算法
void EnemyLayer::EnemyMove(float dt){
	if (statusArray[MoveToBezierLeft]){
		schedule(schedule_selector(EnemyLayer::addSmallEnemy_MoveToBezierLeft), 0.5, 10, 0);
		return;
	}
	if (statusArray[MoveToBezierRight]){
		schedule(schedule_selector(EnemyLayer::addSmallEnemy_MoveToBezierRight), 0.5, 10, 0);
		return;
	}
	if (statusArray[MoveToUiniform]){
		schedule(schedule_selector(EnemyLayer::addSmallEnemy_MoveToUniform), 1, 2, 0);
		return;
	}
	if (statusArray[MoveToLine]){
		schedule(schedule_selector(EnemyLayer::addBigEnemy_MoveTo), 1, 2, 0);
		return;
	}
}

void EnemyLayer::enemyMovedFinished(Node* sender){
	auto enemy = dynamic_cast<BodyParent*>(sender);
	if (enemy != nullptr){
		enemy->clear();
		enemyContainer->removeObject(enemy);
		auto smallEnemy1 = dynamic_cast<SmallEnemy1*>(sender);
		if (smallEnemy1 != nullptr){
			addSmallEnemy1_ToPool(smallEnemy1);
		}
		auto smallEnemy2 = dynamic_cast<SmallEnemy2*>(sender);
		if (smallEnemy2 != nullptr){
			addSmallEnemy2_ToPool(smallEnemy2);
		}
		else {
			auto bigEnemy = dynamic_cast<BigEnemy*>(sender);
			if (bigEnemy != nullptr){
				addBigEnemyToPool(bigEnemy);
			}
		}
	}
}

void EnemyLayer::addSmallEnemy1_ToPool(SmallEnemy1* enemy){
	smallEnemy1_Pool->addObject(enemy);
}

void EnemyLayer::addSmallEnemy2_ToPool(SmallEnemy2* enemy){
	smallEnemy2_Pool->addObject(enemy);
}

void EnemyLayer::addBigEnemyToPool(BigEnemy* enemy){
	bigEnemy_Pool->addObject(enemy);
}

void EnemyLayer::addSmallEnemy_MoveToBezierLeft(float dt){
	auto smallEnemy = produceSmallEnemy2();
	enemyContainer->addObject(smallEnemy);
	auto smallEnemySize = smallEnemy->getContentSize();
	auto size = Director::getInstance()->getWinSize();
	smallEnemy->setPosition(Vec2(0, 400));
	smallEnemy->setRotation(90);
	if (smallEnemy->getParent() == nullptr){
		addChild(smallEnemy);
	}
	ccBezierConfig bezier;
	bezier.endPosition = Vec2(0, 10);
	bezier.controlPoint_1 = Vec2(250, 300);
	bezier.controlPoint_2 = Vec2(180, 150);

	auto actionMove = BezierTo::create(3.f, bezier);
	auto actionRotate = RotateBy::create(3.0f, 180);
	auto actionSpawn = Spawn::create(actionMove, actionRotate, nullptr);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMovedFinished, this));
	auto actionSequence = Sequence::create(actionSpawn, actionDone, nullptr);
	smallEnemy->runAction(actionSequence);
}

void EnemyLayer::addSmallEnemy_MoveToBezierRight(float dt){
	auto smallEnemy = produceSmallEnemy2();
	enemyContainer->addObject(smallEnemy);
	auto smallEnemySize = smallEnemy->getContentSize();
	auto size = Director::getInstance()->getWinSize();
	smallEnemy->setPosition(Vec2(size.width, 500));
	smallEnemy->setRotation(-90);
	if (smallEnemy->getParent() == nullptr){
		addChild(smallEnemy);
	}
	ccBezierConfig bezier;
	bezier.endPosition = Vec2(size.width, 110);
	bezier.controlPoint_1 = Vec2(size.width - 250, 300);
	bezier.controlPoint_2 = Vec2(size.width - 180, 150);

	auto actionMove = BezierTo::create(3.f, bezier);
	auto actionRotate = RotateBy::create(3.0f, -180);
	auto actionSpawn = Spawn::create(actionMove, actionRotate, nullptr);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMovedFinished, this));
	auto actionSequence = Sequence::create(actionSpawn, actionDone, nullptr);
	smallEnemy->runAction(actionSequence);
}

void EnemyLayer::addSmallEnemy_MoveToUniform(float dt){
	int flag = rand() % 5;
	if (flag > 2){
		return;
	}
	//一排敌机的数量
	int enemyCount = 2 + rand() % 4;
	float minDuration = 4;
	float maxDuration = 5;
	auto size = Director::getInstance()->getWinSize();

	int rangeDuration = maxDuration - minDuration;
	int moveDuration = 4 + CCRANDOM_0_1()*rangeDuration;
	int startX = 0;   //最左边敌机的横坐标
	int actualX = 0;  //敌机的实际横坐标

	for (int i = 0; i < enemyCount; i++){
		SmallEnemy1* smallEnemy = produceSmallEnemy1();
		enemyContainer->addObject(smallEnemy);
		auto smallEnemySize = smallEnemy->getContentSize();
		int  minX = smallEnemySize.width / 2;
		int  maxX = size.width - smallEnemySize.width / 2;
		int  rangeX = maxX - minX;
		if (startX == 0){//生成最左边敌机的横坐标
			startX = minX + rand() % rangeX*(1.0 / 4);
			actualX = startX;
		}
		else{
			actualX = startX + (smallEnemySize.width + 20)*i;
		}

		if (actualX <= size.width - smallEnemySize.width / 2){//检查生成的飞机横坐标的有效性
			smallEnemy->setPosition(actualX, size.height + smallEnemySize.height / 2);
			if (smallEnemy->getParent() == nullptr){
				addChild(smallEnemy);
			}

			auto actionMove = MoveTo::create(moveDuration, Vec2(actualX, -smallEnemySize.height / 2));
			auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMovedFinished, this));
			auto actionSequence = Sequence::create(actionMove, actionDone, nullptr);
			smallEnemy->runAction(actionSequence);
			smallEnemy->shoot();
		}
	}
}

void EnemyLayer::addBigEnemy_MoveTo(float dt){
	int flag = rand() % 10;
	if (flag > 4){
		return;
	}
	auto bigEnemy = produceBigEnemy();
	auto bigEnemySize = bigEnemy->getContentSize();
	auto size = Director::getInstance()->getWinSize();

	//BigEnemy横坐标最小值
	int min_X = bigEnemySize.width / 2;

	//BigEnemy横坐标最大值
	int max_X = size.width - bigEnemySize.width / 2;

	//BigEnemy横坐标取值范围
	int range_X = max_X - min_X;

	//获取随机的BigEnemy起始横坐标
	int startX = min_X + (rand() % range_X);

	bigEnemy->setPosition(startX, size.height + bigEnemySize.height / 2);

	if (bigEnemy->getParent() == nullptr){
		addChild(bigEnemy);
	}
	enemyContainer->addObject(bigEnemy);

	float minDuration = 4;
	float maxDuration = 6;
	int rangeDuration = maxDuration - minDuration;

	auto moveDuration = 4 + CCRANDOM_0_1()*rangeDuration;

	auto actionMove = MoveTo::create(moveDuration, Vec2(startX, -bigEnemySize.height / 2));

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMovedFinished, this));

	auto actionSequence = Sequence::create(actionMove, actionDone, nullptr);

	bigEnemy->runAction(actionSequence);
	bigEnemy->shoot();
}

BigEnemy* EnemyLayer::produceBigEnemy(){
	BigEnemy* enemy = nullptr;
	if (bigEnemy_Pool->count() > 0){
		enemy = dynamic_cast<BigEnemy*>(bigEnemy_Pool->getLastObject());
		bigEnemy_Pool->removeObject(enemy);
	}
	else{
		enemy = BigEnemy::create();
	}
	enemy->setVisible(true);
	return enemy;
}

SmallEnemy1* EnemyLayer::produceSmallEnemy1(){
	SmallEnemy1* enemy = nullptr;
	if (smallEnemy1_Pool->count() > 0){
		enemy = dynamic_cast<SmallEnemy1*>(smallEnemy1_Pool->getLastObject());
		smallEnemy1_Pool->removeObject(enemy);
	}
	else{
		enemy = SmallEnemy1::create();
	}
	enemy->setVisible(true);
	return enemy;
}

SmallEnemy2* EnemyLayer::produceSmallEnemy2(){
	SmallEnemy2* enemy = nullptr;
	if (smallEnemy2_Pool->count() > 0){
		enemy = dynamic_cast<SmallEnemy2*>(smallEnemy2_Pool->getLastObject());
		smallEnemy2_Pool->removeObject(enemy);
	}
	else{
		enemy = SmallEnemy2::create();
	}
	enemy->setVisible(true);
	return enemy;
}

void EnemyLayer::statusUpdate(float dt){
	//产生随机数种子
	srand((unsigned)time(0));
	for (int Index = 0; Index < arraySize; Index++){
		statusArray[Index] = false;
	}
	statusArray[rand() % arraySize] = true;
}