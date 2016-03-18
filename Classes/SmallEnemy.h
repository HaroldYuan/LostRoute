#ifndef smallEnenmy_h__
#define smallEnenmy_h__
#include "cocos2d.h"
#include "BodyParent.h"
#include "Resources.h"
#include "WeaponLayer.h"
#include "SmallEnemyWeapon.h"

USING_NS_CC;

class SmallEnemy :public BodyParent
{
public:
	virtual bool init();

	CREATE_FUNC(SmallEnemy);

	void shoot();

	void repeatShoot(float dt);

	int getEnemyTag() const;

	void setEnemyTag(int tag);

	virtual void clear();
public:
	float duration = 0;
private:
	int EnemyTag = 1;
	float UpdateTimeCount = 0;
};
#endif // smallEnenmy_h__
