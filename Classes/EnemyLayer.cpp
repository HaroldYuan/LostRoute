#include "EnemyLayer.h"

EnemyLayer::EnemyLayer(){
	enemyContainer = __Array::create();
	enemyContainer->retain();

	smallEnemy_Pool = __Array::create();
	smallEnemy_Pool->retain();

	bigEnemy_Pool = __Array::create();
	bigEnemy_Pool->retain();
}

EnemyLayer::~EnemyLayer(){
	CC_SAFE_RELEASE_NULL(enemyContainer);
	CC_SAFE_RELEASE_NULL(smallEnemy_Pool);
	CC_SAFE_RELEASE_NULL(bigEnemy_Pool);
}

bool EnemyLayer::init(){
	if (!Layer::init()){
		return false;
	}
	srand((unsigned)time(0));
	//schedule(schedule_selector(EnemyLayer::addSmallEnemy_MoveTo), 1.5);
	//schedule(schedule_selector(EnemyLayer::addSmallEnemy_MoveToUniform), 2.0);
	schedule(schedule_selector(EnemyLayer::addBigEnemy_MoveTo), 3.0);
	return true;
}

void EnemyLayer::enemyMovedFinished(Node* sender){
	auto enemy = dynamic_cast<BodyParent*>(sender);
	if (enemy != nullptr){
		enemy->clear();
		enemyContainer->removeObject(enemy);
		auto smallEnemy = dynamic_cast<SmallEnemy*>(sender);
		if (smallEnemy != nullptr){
			addSmallEnemyToPool(smallEnemy);
		}
		else{
			auto bigEnemy = dynamic_cast<BigEnemy*>(sender);
			if (bigEnemy != nullptr){
				addBigEnemyToPool(bigEnemy);
			}
		}
	}
}

void EnemyLayer::addSmallEnemyToPool(SmallEnemy* enemy){
	smallEnemy_Pool->addObject(enemy);
}

void EnemyLayer::addBigEnemyToPool(BigEnemy* enemy){
	bigEnemy_Pool->addObject(enemy);
}

void EnemyLayer::addSmallEnemy_MoveTo(float dt){
	auto smallEnemy = produceSmallEnemy();
	auto smallEnemySize = smallEnemy->getContentSize();
	auto size = Director::getInstance()->getWinSize();

	//SmallEnemy横坐标最小值
	int min_X = smallEnemySize.width / 2;

	//SmallEnemy横坐标最大值
	int max_X = size.width - smallEnemySize.width / 2;

	//SmallEnemy横坐标取值范围
	int range_X = max_X - min_X;

	//获取随机的SmallEnemy起始横坐标
	int startX = min_X + (rand() % range_X);

	smallEnemy->setPosition(startX, size.height + smallEnemySize.height / 2);

	if (smallEnemy->getParent() == nullptr){
		addChild(smallEnemy);
	}
	enemyContainer->addObject(smallEnemy);

	float minDuration = 4;
	float maxDuration = 6;
	int rangeDuration = maxDuration - minDuration;

	auto moveDuration = 4 + CCRANDOM_0_1()*rangeDuration;

	auto actionMove = MoveTo::create(moveDuration, Vec2(startX, -smallEnemySize.height / 2));

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMovedFinished, this));

	auto actionSequence = Sequence::create(actionMove, actionDone, nullptr);

	smallEnemy->duration = moveDuration;
	smallEnemy->runAction(actionSequence);
	if (smallEnemy->getEnemyTag() == 2){
		smallEnemy->shoot();
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

	float minDuration = 6;
	float maxDuration = 8;
	int rangeDuration = maxDuration - minDuration;

	auto moveDuration = 6 + CCRANDOM_0_1()*rangeDuration;

	auto actionMove = MoveTo::create(moveDuration, Vec2(startX, -bigEnemySize.height / 2));

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMovedFinished, this));

	auto actionSequence = Sequence::create(actionMove, actionDone, nullptr);

	bigEnemy->runAction(actionSequence);
	bigEnemy->shoot();
}

void EnemyLayer::addSmallEnemy_MoveToUniform(float dt){
	int flag = rand() % 5;
	if (flag > 2){
		return;
	}
	//一排敌机的数量
	int enemyCount = 1 + rand() % 6;
	float minDuration = 4;
	float maxDuration = 8;
	auto size = Director::getInstance()->getWinSize();

	int rangeDuration = maxDuration - minDuration;
	int moveDuration = 4 + CCRANDOM_0_1()*rangeDuration;
	int startX = 0;   //最左边敌机的横坐标
	int actualX = 0;  //敌机的实际横坐标

	for (int i = 0; i < enemyCount; i++){
		SmallEnemy* smallEnemy = produceSmallEnemy();
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
		}
	}
}

BigEnemy* EnemyLayer::produceBigEnemy(){
	BigEnemy* enemy = nullptr;
	if (smallEnemy_Pool->count() > 0){
		enemy = dynamic_cast<BigEnemy*>(smallEnemy_Pool->getLastObject());
		smallEnemy_Pool->removeObject(enemy);
	}
	else{
		enemy = BigEnemy::create();
	}
	enemy->setVisible(true);
	return enemy;
}

SmallEnemy* EnemyLayer::produceSmallEnemy(){
	SmallEnemy* enemy = nullptr;
	if (smallEnemy_Pool->count() > 0){
		enemy = dynamic_cast<SmallEnemy*>(smallEnemy_Pool->getLastObject());
		smallEnemy_Pool->removeObject(enemy);
	}
	else{
		enemy = SmallEnemy::create();
	}
	enemy->setVisible(true);
	return enemy;
}