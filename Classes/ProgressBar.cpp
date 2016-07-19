#include "ProgressBar.h"

bool ProgressBar::init(){
	if (!Sprite::init()){
		return false;
	}
	fgSprite = Sprite::createWithSpriteFrameName(fg_spriteFrameName);
	bgSprite = Sprite::createWithSpriteFrameName(bg_spriteFrameName);
	addChild(fgSprite);
	addChild(bgSprite);
	originWidth = fgSprite->getTextureRect().size.width;
	return true;
}

ProgressBar* ProgressBar::createWithSpriteFrameName(const char *fgName, const char *bgName){
	ProgressBar *ret = new ProgressBar();
	if (ret != nullptr){
		ret->fg_spriteFrameName = fgName;
		ret->bg_spriteFrameName = bgName;
	}

	if (ret != nullptr && ret->init()){
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return nullptr;
}

int ProgressBar::getMaxValue() const{
	return maxValue;
}

void ProgressBar::setMaxValue(int val){
	maxValue = val;
}

int ProgressBar::getMinValue() const{
	return minValue;
}

void ProgressBar::setMinValue(int val){
	minValue = val;
}

int ProgressBar::getProgress() const{
	return progress;
}

void ProgressBar::setProgress(int val){
	if (val < minValue || val>maxValue){
		return;
	}

	progress = val;
	int x = fgSprite->getTextureRect().origin.x;
	int y = fgSprite->getTextureRect().origin.y;
	int width = originWidth*progress / maxValue;
	int height = fgSprite->getTextureRect().size.height;
	fgSprite->setTextureRect(Rect(x, y, width, height));
	fgSprite->setAnchorPoint(Vec2(0, 0));
	bgSprite->setAnchorPoint(Vec2(0, 0));
	fgSprite->setPosition(Vec2(0, 0));
	bgSprite->setPosition(Vec2(0, 0));
}