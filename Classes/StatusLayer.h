#ifndef StatusLayer_h__
#define StatusLayer_h__
#include "cocos2d.h"
#include "ProgressBar.h"
#include "Numbers.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

class StatusLayer :public Layer
{
public:
	bool virtual init();

	CREATE_FUNC(StatusLayer);
public:
	void updateHP(int newHP);
	void addScore(int score);
	void onClick_Pause(Ref* pSender);
	void updateHighScore();
	void resetDefault();

private:
	void saveData();
	void loadData();

private:
	int currentScore = 0;        //当前分数
	int mMaxScore = 0;     //历史最高分
	int mHP = WARSHIP_MAX_HP;
	ProgressBar* mHPValue;
	Numbers* mNumbers;
};
#endif // StatusLayer_h__
