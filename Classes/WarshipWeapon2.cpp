#include "WarshipWeapon2.h"

bool WarshipWeapon2::init(){
	if (!Sprite::init()){
		return false;
	}
	angles[0] = 50;
	angles[1] = 30;
	angles[2] = 0;
	angles[3] = -30;
	angles[4] = -50;
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_WARSHIP_WEAPON2_PICTURE);
	initWithSpriteFrame(spriteFrame);
	hp = 2;
	isWeapon = true;
	return true;
}

void WarshipWeapon2::setAngleIndex(int index){
	if (index >= 0 && index <= 4){
		setRotation(angles[index]);
	}
}

int WarshipWeapon2::getAngle(int index){
	if (index >= 0 && index <= 4){
		return angles[index];
	}
	else{
		return angles[0];
	}
}