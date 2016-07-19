#ifndef ProgressBar_h__
#define ProgressBar_h__

#include "cocos2d.h"
#include "Resources.h"
USING_NS_CC;

class ProgressBar :public Sprite
{
public:
	bool virtual init();

	static ProgressBar* createWithSpriteFrameName(const char *fg_spriteFrameName, const char *bg_spriteFrameName);

	int  getMaxValue() const;
	void setMaxValue(int val);

	int getMinValue() const;
	void setMinValue(int val);

	int  getProgress() const;
	void setProgress(int val);

private:
	Sprite *fgSprite;
	Sprite *bgSprite;

	const char *fg_spriteFrameName;
	const char *bg_spriteFrameName;

	int maxValue;
	int minValue;
	int progress;
	int originWidth;
};
#endif // ProgressBar_h__
