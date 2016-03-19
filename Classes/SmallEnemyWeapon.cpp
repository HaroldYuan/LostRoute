#include "SmallEnemyWeapon.h"

bool SmallEnemyWeapon::init(){
	if (!Sprite::init()){
		return false;
	}
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_ENEMY_WEAPON2_PICTURE);
	initWithSpriteFrame(spriteFrame);

	hp = 1;
	maxHP = 1;
	isWeapon = true;
	return true;
}

void SmallEnemyWeapon::clear(){
	setVisible(false);
	stopAllActions();
}