#ifndef _Body_Parent 
#define _Body_Parent
#include "cocos2d.h"
USING_NS_CC;

//�����˸���(Body)�й��õķ����ͳ�Ա����
class BodyParent :public Sprite
{
public:
	int hp=1;     //��ǰBody������ֵ
	int maxHP=1;   //��ǰBodyd���������ֵ
	bool selected=false;     //��ǰ�Ƿ񱻵���ѡ��
	BodyParent* node=nullptr; //�����ڵ�ǰBody������Node
	BodyParent* missle=nullptr;

	bool isWeapon;

public:

	//���ڲ�����ըЧ������Ч
	virtual void explode();

	//lethality��ʾɱ����ָ������������һ��Body��hpֵ
	virtual bool collide(int lethality);

	//���κ�����£�һ���Դݻ�Body,ͨ�����ڵ���
	virtual void collide();
};
#endif // _Body_Parent
