#ifndef _Body_Parent
#define _Body_Parent
#include "cocos2d.h"
USING_NS_CC;

//�����˸���(Body)�й��õķ����ͳ�Ա����
class BodyParent :public Sprite
{
public:
	//lethality��ʾɱ����ָ������������һ��Body��hpֵ
	virtual bool collide(int lethality);

	//���κ�����£�һ���Դݻ�Body,ͨ�����ڵ���
	virtual void collide();

	//���ڲ�����ըЧ������Ч
	virtual void explode();

	virtual bool init();

	CREATE_FUNC(BodyParent);

	//���ڵл��ָ�Ϊ��ʼ״̬
	virtual void clear(){}

public:
	int currentHp = 1;     //��ǰBody������ֵ
	int maxHp = 1;  //Body���������ֵ
	BodyParent* node = nullptr; //�����ڵ�ǰBody������Node
	bool isWeapon;
};
#endif // _Body_Parent
