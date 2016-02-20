#include "WarshipWeapon2.h"

bool WarshipWeapon2::init(){
	if(!Sprite::init()){
		return false;
	}

	angles[0]=-30;
	angles[1]=30;
	auto spriteFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_WARSHIP_WEAPON2_PICTURE);
	initWithSpriteFrame(spriteFrame);

	hp = 1;
	isWeapon = true;
	return true;
}

void WarshipWeapon2::setAngleIndex( int index ){
	if(index>=0 && index<=1){
		setRotation(angles[index]);
	}
}



