#include "WarshipWeapon1.h"

bool WarshipWeapon1::init(){
	if (!Sprite::init()){
		return false;
	}
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_WARSHIP_WEAPON1_PICTURE);
	initWithSpriteFrame(spriteFrame);
	hp = 1;
	isWeapon = true;
	return true;
}

void WarshipWeapon1::clear(){
	setVisible(false);
	stopAllActions();
}