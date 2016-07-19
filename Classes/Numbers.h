#ifndef Numbers_h__
#define Numbers_h__

#include <string>
#include <sstream>
#include "cocos2d.h"
#include "Resources.h"

using std::string;
using std::ostringstream;
USING_NS_CC;

class Numbers :public Ref
{
public:
	bool virtual init();

	static Numbers* createWithSpriteFrameName(const char *spriteFrameName);

	//������ת�����ַ���
	string integerToString(int value);

	//����һ������
	Node* generateNumbers(const string &numbers);

private:
	const char *spriteFrameName;

	//����ͼ��������֡�е�����
	float x;
	float y;

	////����ͼ��������֡�еĿ�Ⱥ͸߶�
	float width;
	float height;

	//������������
	Node* generateNumber(int number);
};
#endif // Numbers_h__
