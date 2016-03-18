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
	schedule(schedule_selector(EnemyLayer::addSmallEnemy_MoveTo), 2.0);
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

void EnemyLayer::setWeaponLayer(WeaponLayer* mWeaponLayer){
	myWeaponLayer = mWeaponLayer;
}

void EnemyLayer::addSmallEnemy_MoveTo(float dt){
	auto smallEnemy = produceSmallEnemy();
	auto smallEnemySize = smallEnemy->getContentSize();
	auto size = Director::getInstance()->getWinSize();

	//敌机横坐标最小值
	int min_X = smallEnemySize.width / 2;

	//敌机横坐标最大值
	int max_X = size.width - smallEnemySize.width / 2;

	//敌机横坐标取值范围
	int range_X = max_X - min_X;

	//获取随机的敌机起始横坐标
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

	auto actionSequence = Sequence::create(actionMove, actionDone, NULL);

	smallEnemy->duration = moveDuration;
	smallEnemy->runAction(actionSequence);
	if (smallEnemy->getEnemyTag() == 2){
		smallEnemy->shoot();
	}
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