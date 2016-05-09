#ifndef DropLayer_h__
#define DropLayer_h__

#include "cocos2d.h"
#include "DropLife.h"
#include "DropWeapon.h"
USING_NS_CC;

class DropLayer :public Layer
{
public:
	virtual bool init();

	void generateDrop(float dt);

	CREATE_FUNC(DropLayer);
private:
	//随机产生一个Drop
	Drop* generateDropType();
};
#endif // DropLayer_h__
