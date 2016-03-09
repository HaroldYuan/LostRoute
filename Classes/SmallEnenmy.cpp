#include "smallEnenmy.h"

bool SmallEnenmy::init(){
	if (!Sprite::init()){
		return false;
	}
	auto enemyPath = PATH_SMALLENEMY1_PICTURE;
	srand((unsigned)time(0));
	if (rand() % 100 > 50){
		enemyPath = PATH_SMALLENEMY2_PICTURE;
	}
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(enemyPath);
	initWithSpriteFrame(spriteFrame);

	hp = 4;
	maxHP = 4;
	isWeapon = true;
	return true;
}