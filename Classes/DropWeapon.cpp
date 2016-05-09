#include "DropWeapon.h"
#include "Resources.h"

bool DropWeapon::init(){
	if (!Drop::init()){
		return false;
	}
	auto DropWeapon_path = PATH_DROP_ADDBULLET_PICTURE;
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(DropWeapon_path);
	initWithSpriteFrame(spriteFrame);
	dropType = addBullet;
	return true;
}