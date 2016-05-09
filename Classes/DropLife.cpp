#include "DropLife.h"
#include "Resources.h"

bool DropLife::init(){
	if (!Drop::init()){
		return false;
	}
	auto DropLife_path = PATH_DROP_ADDLIFE_PICTURE;
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(DropLife_path);
	initWithSpriteFrame(spriteFrame);
	dropType = addLife;
	return true;
}