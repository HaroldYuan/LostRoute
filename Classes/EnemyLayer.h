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

	//�л�ֱ�߷���
	void addSmallEnemy_MoveTo(float dt);

	//��Pool�л�ȡһ�����󣬵�pool�ж���Ϊ��ʱ������һ���¶���
	SmallEnemy* produceSmallEnemy();

	CREATE_FUNC(EnemyLayer);
public:
	__Array *enemyContainer;  //�洢�������ڷ��еĵл�

	__Array* smallEnemy_Pool;  //�洢���п��õ�smallEnemy

	__Array* bigEnemy_Pool;  //�洢���п��õ�BigEnemy

	int EnemyCount = 0;

private:
	WeaponLayer* myWeaponLayer;
};
#endif // EnemyLayer_h__
