#ifndef EnemyLayer_h__
#define EnemyLayer_h__
#include "cocos2d.h"
#include "BodyParent.h"
#include "SmallEnemy1.h"
#include "SmallEnemy2.h"
#include "BigEnemy.h"
#include "WeaponLayer.h"

USING_NS_CC;

class EnemyLayer :public Layer{
public:
	EnemyLayer();

	~EnemyLayer();

	virtual bool init();

	void enemyMovedFinished(Node* sender);

	void addSmallEnemy1_ToPool(SmallEnemy1* enemy);

	void addSmallEnemy2_ToPool(SmallEnemy2* enemy);

	void addBigEnemyToPool(BigEnemy* enemy);

	//SmallEnemy直线飞行
	void addSmallEnemy_MoveTo(float dt);

	//SmallEnemy曲线飞行
	void addSmallEnemy_MoveToBezierLeft(float dt);

	void addSmallEnemy_MoveToBezierRight(float dt);

	//BigEnemy直线飞行
	void addBigEnemy_MoveTo(float dt);

	//敌机成排直线飞行
	void addSmallEnemy_MoveToUniform(float dt);

	void EnemyMove(float dt);

	//从Pool中获取一个BigEnemy对象，当pool中对象为空时，创建一个新对象
	BigEnemy* produceBigEnemy();

	//从Pool中获取一个SmallEnemy1对象，当pool中对象为空时，创建一个新对象
	SmallEnemy1* produceSmallEnemy1();

	//从Pool中获取一个SmallEnemy2对象，当pool中对象为空时，创建一个新对象
	SmallEnemy2* produceSmallEnemy2();

	//更新状态
	void statusUpdate(float dt);

	CREATE_FUNC(EnemyLayer);
public:
	__Array *enemyContainer;  //存储所有正在飞行的敌机

	__Array* smallEnemy1_Pool;  //存储所有可用的smallEnemy1

	__Array* smallEnemy2_Pool;  //存储所有可用的smallEnemy2

	__Array* bigEnemy_Pool;  //存储所有可用的BigEnemy

	static const int arraySize = 4;

	bool statusArray[arraySize];

private:
	WeaponLayer* myWeaponLayer;
};
#endif // EnemyLayer_h__
