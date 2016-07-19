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

	//将数字转换成字符串
	string integerToString(int value);

	//产生一串数字
	Node* generateNumbers(const string &numbers);

private:
	const char *spriteFrameName;

	//数字图像在整个帧中的坐标
	float x;
	float y;

	////数字图像在整个帧中的宽度和高度
	float width;
	float height;

	//产生单个数字
	Node* generateNumber(int number);
};
#endif // Numbers_h__
