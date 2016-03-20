#include "BigEnemyWeapon.h"

bool BigEnemyWeapon::init(){
	if (!Sprite::init()){
		return false;
	}
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_ENEMY_WEAPON2_PICTURE);
	initWithSpriteFrame(spriteFrame);

	hp = 2;
	isWeapon = true;
	return true;
}