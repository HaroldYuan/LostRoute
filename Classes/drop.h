#ifndef Drop_h__
#define Drop_h__
#include "cocos2d.h"
#include "BodyParent.h"
USING_NS_CC;

class Drop :public BodyParent{
public:
	virtual bool init();

	void hideDrop();

	CREATE_FUNC(Drop);

	int dropType = addBullet;

	enum type{
		addBullet = 0,
		addLife
	};
};
#endif // Drop_h__
