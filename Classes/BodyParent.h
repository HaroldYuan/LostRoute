#ifndef _Body_Parent
#define _Body_Parent
#include "cocos2d.h"
USING_NS_CC;

//定义了刚体(Body)中公用的方法和成员变量
class BodyParent :public Sprite
{
public:
	//lethality表示杀伤力指数，就是另外一个Body的hp值
	virtual bool collide(int lethality);

	//在任何情况下，一次性摧毁Body,通常用于导弹
	virtual void collide();

	//用于产生爆炸效果的特效
	virtual void explode();

	virtual bool init();

	CREATE_FUNC(BodyParent);

	//用于敌机恢复为初始状态
	virtual void clear(){}

public:
	int currentHp = 1;     //当前Body的生命值
	int maxHp = 1;  //Body的最大生命值
	BodyParent* node = nullptr; //保存于当前Body关联的Node
	bool isWeapon;
};
#endif // _Body_Parent
