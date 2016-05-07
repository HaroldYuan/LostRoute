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

	//SmallEnemyֱ�߷���
	void addSmallEnemy_MoveTo(float dt);

	//SmallEnemy���߷���
	void addSmallEnemy_MoveToBezierLeft(float dt);

	void addSmallEnemy_MoveToBezierRight(float dt);

	//BigEnemyֱ�߷���
	void addBigEnemy_MoveTo(float dt);

	//�л�����ֱ�߷���
	void addSmallEnemy_MoveToUniform(float dt);

	void EnemyMove(float dt);

	//��Pool�л�ȡһ��BigEnemy���󣬵�pool�ж���Ϊ��ʱ������һ���¶���
	BigEnemy* produceBigEnemy();

	//��Pool�л�ȡһ��SmallEnemy1���󣬵�pool�ж���Ϊ��ʱ������һ���¶���
	SmallEnemy1* produceSmallEnemy1();

	//��Pool�л�ȡһ��SmallEnemy2���󣬵�pool�ж���Ϊ��ʱ������һ���¶���
	SmallEnemy2* produceSmallEnemy2();

	//����״̬
	void statusUpdate(float dt);

	CREATE_FUNC(EnemyLayer);
public:
	__Array *enemyContainer;  //�洢�������ڷ��еĵл�

	__Array* smallEnemy1_Pool;  //�洢���п��õ�smallEnemy1

	__Array* smallEnemy2_Pool;  //�洢���п��õ�smallEnemy2

	__Array* bigEnemy_Pool;  //�洢���п��õ�BigEnemy

	static const int arraySize = 4;

	bool statusArray[arraySize];

private:
	WeaponLayer* myWeaponLayer;
};
#endif // EnemyLayer_h__
