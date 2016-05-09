#include "Drop.h"
#include "Resources.h"

bool Drop::init(){
	if (!Sprite::init()){
		return false;
	}
	auto dropPath_bullet = PATH_DROP_ADDBULLET_PICTURE;
	auto spriteFrame_bullet = SpriteFrameCache::getInstance()->getSpriteFrameByName(dropPath_bullet);

	auto dropPath_life = PATH_DROP_ADDBULLET_PICTURE;
	auto spriteFrame_life = SpriteFrameCache::getInstance()->getSpriteFrameByName(dropPath_life);
	initWithSpriteFrame(spriteFrame_bullet);

	auto body = PhysicsBody::createBox(getContentSize());
	setPhysicsBody(body);
	body->setCategoryBitmask(0x01);       //0001
	body->setContactTestBitmask(0x03);    //0011
	body->setCollisionBitmask(0x02);      //0010

	setTag(Enemy);
	return true;
}

void Drop::hideDrop(float dt){
	stopAllActions();
	getParent()->removeChild(this);
}