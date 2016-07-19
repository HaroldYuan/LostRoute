#include "BodyParent.h"

bool BodyParent::collide(int lethality){
	if (lethality >= currentHp){
		//被摧毁
		explode();
		collide();
		return true;
	}
	else
	{
		currentHp -= lethality; //减去对方的杀伤力指数
		return false;
	}
}

void BodyParent::collide(){
	setVisible(false);
	unscheduleAllSelectors();
}

void BodyParent::explode(){
}

bool BodyParent::init(){
	if (!Sprite::init()){
		return false;
	}
	return true;
}