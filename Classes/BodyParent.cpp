#include "BodyParent.h"

bool BodyParent::collide(int lethality){
	if (lethality >= currentHp){
		//���ݻ�
		explode();
		collide();
		return true;
	}
	else
	{
		currentHp -= lethality; //��ȥ�Է���ɱ����ָ��
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