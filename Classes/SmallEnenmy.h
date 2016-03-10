#ifndef smallEnenmy_h__
#define smallEnenmy_h__
#include "cocos2d.h"
#include "BodyParent.h"
#include "Resources.h"
#include "WeaponLayer.h"
#include "SmallEnemyWeapon1.h"
#include "SmallEnemyWeapon2.h"

USING_NS_CC;

class SmallEnenmy :public BodyParent
{
public:
	virtual bool init();

	CREATE_FUNC(SmallEnenmy);

	void setWeaponLayer(WeaponLayer* mWeaponLayer);

	void shoot();

	void repeatShoot(float dt);

	int getEnemyTag() const;

	void setEnemyTag(int tag);
private:
	int EnemyTag = 1;
	WeaponLayer* myWeaponLayer;
};
#endif // smallEnenmy_h__
