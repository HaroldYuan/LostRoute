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

	//SmallEnemy直线飞行
	void addSmallEnemy_MoveTo(float dt);

	//BigEnemy直线飞行
	void addBigEnemy_MoveTo(float dt);

	//敌机成排直线飞行
	void addSmallEnemy_MoveToUniform(float dt);

	//从Pool中获取一个SmallEnemy对象，当pool中对象为空时，创建一个新对象
	BigEnemy* produceBigEnemy();

	//从Pool中获取一个BigEnemy对象，当pool中对象为空时，创建一个新对象
	SmallEnemy* produceSmallEnemy();

	CREATE_FUNC(EnemyLayer);
public:
	__Array *enemyContainer;  //存储所有正在飞行的敌机

	__Array* smallEnemy_Pool;  //存储所有可用的smallEnemy

	__Array* bigEnemy_Pool;  //存储所有可用的BigEnemy

private:
	WeaponLayer* myWeaponLayer;
};
#endif // EnemyLayer_h__
