#include "BodyParent.h"

bool BodyParent::collide(int lethality){
	if (lethality >= hp){
		//被摧毁
		explode();
		collide();
		return true;
	}
	else
	{
		hp -= lethality; //减去对方的杀伤力指数
		return false;
	}
}

void BodyParent::collide(){
	setVisible(false);
}

void BodyParent::explode(){
}