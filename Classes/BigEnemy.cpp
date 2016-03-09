#include "BigEnemy.h"

bool BigEnemy::init(){
	if (!Sprite::init()){
		return false;
	}
	auto enemyPath = PATH_BIGENEMY_PICTURE;
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_BIGENEMY_PICTURE);
	initWithSpriteFrame(spriteFrame);
	hp = 10;
	maxHP = 10;
	return true;
}