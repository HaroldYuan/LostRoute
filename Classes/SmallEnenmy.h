#ifndef smallEnenmy_h__
#define smallEnenmy_h__
#include "cocos2d.h"
#include "BodyParent.h"
#include "Resources.h"

USING_NS_CC;

class SmallEnenmy :public BodyParent
{
public:
	virtual bool init();
	CREATE_FUNC(SmallEnenmy);
};
#endif // smallEnenmy_h__
