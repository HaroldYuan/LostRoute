#ifndef LostRouteGameLayer_h__
#define LostRouteGameLayer_h__

#include "cocos2d.h"
#include "Resources.h"
#include "WarshipLayer.h"
#include "SmallEnenmy.h"

USING_NS_CC;
class LostRouteGameLayer :public Layer{
private:
	Sprite* bg1;
	Sprite* bg2;
	Sprite* bgCloud1;
	Sprite* bgCloud2;

	WarshipLayer* myWarshipLayer;
	WeaponLayer*  mWeaponLayer;
private:
	//¹ö¶¯±³¾°Í¼
	void moveBackground(Size &size);
public:
	CREATE_FUNC(LostRouteGameLayer);
	virtual bool init();
	virtual void update(float time);
private:
};

#endif // LostRouteGameLayer_h__
