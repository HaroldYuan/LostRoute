#include "BodyParent.h"

bool BodyParent::collide(int lethality){
	if (lethality >= hp){
		//���ݻ�
		explode();
		collide();
		return true;
	}
	else
	{
		hp -= lethality; //��ȥ�Է���ɱ����ָ��
		return false;
	}
}

void BodyParent::collide(){
	setVisible(false);
}

void BodyParent::explode(){
}