#include "WarshipLayer.h"

bool WarshipLayer::init(){
	if (!Layer::init()){
		return false;
	}

	auto size = Director::getInstance()->getWinSize();
	warship = Warship::create();
	warship->setPosition(size.width / 2, size.height / 2);
	addChild(warship);
	warship->shoot();
	return true;
}