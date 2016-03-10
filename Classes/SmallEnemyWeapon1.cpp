#include "SmallEnemyWeapon1.h"

bool SmallEnemyWeapon1::init(){
	if (!Sprite::init()){
		return false;
	}
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_ENEMY_WEAPON1_PICTURE);
	initWithSpriteFrame(spriteFrame);

	hp = 1;
	maxHP = 1;
	isWeapon = true;
	return true;
}