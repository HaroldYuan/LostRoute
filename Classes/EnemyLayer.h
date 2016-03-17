#ifndef EnemyLayer_h__
#define EnemyLayer_h__
#include "cocos2d.h"
#include "WeaponLayer.h"
#include "BodyParent.h"
#include "SmallEnemy.h"
#include "BigEnemy.h"
USING_NS_CC;

class EnemyLayer :public Layer{
public:
	EnemyLayer();

	~EnemyLayer();

	virtual bool init();

	void enemyMovedFinished(Node* sender);

	void addSmallEnemyToPool(SmallEnemy* enemy);

	void addBigEnemyToPool(BigEnemy* enemy);

	void setWeaponLayer(WeaponLayer* myWeaponLayer);

	//敌机直线飞行
	void addSmallEnemy_MoveTo(float dt);

	//从Pool中获取一个对象，当pool中对象为空时，创建一个新对象
	SmallEnemy* produceSmallEnemy();

	CREATE_FUNC(EnemyLayer);
public:
	__Array *enemyContainer;  //存储所有正在飞行的敌机

	__Array* smallEnemy_Pool;  //存储所有可用的smallEnemy

	__Array* bigEnemy_Pool;  //存储所有可用的BigEnemy

	int EnemyCount = 0;

private:
	WeaponLayer* myWeaponLayer;
};
#endif // EnemyLayer_h__
