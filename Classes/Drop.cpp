#include "Drop.h"
#include "Resources.h"

bool Drop::init(){
	if (!Sprite::init()){
		return false;
	}

	auto body = PhysicsBody::createBox(getContentSize());
	setPhysicsBody(body);
	body->setCategoryBitmask(0x01);       //0001
	body->setContactTestBitmask(0x03);    //0011
	body->setCollisionBitmask(0x02);      //0010
	setTag(Enemy);
	return true;
}

void Drop::hideDrop(){
	stopAllActions();
	getParent()->removeChild(this);
}