#include "LostRouteGameLayer.h"

bool LostRouteGameLayer::init(){
	if (!Layer::init()){
		return false;
	}
	auto size = Director::getInstance()->getVisibleSize();
	//显示背景
	bg1 = Sprite::createWithSpriteFrameName(PATH_BACKGROUND_PICTURE);
	bg2 = Sprite::createWithSpriteFrameName(PATH_BACKGROUND_PICTURE);
	bgCloud1 = Sprite::createWithSpriteFrameName(PATH_CLOUD_BACKGROUND_PICTURE);
	bgCloud2 = Sprite::createWithSpriteFrameName(PATH_CLOUD_BACKGROUND_PICTURE);
	bg1->setAnchorPoint(Vec2(0, 0));
	bg2->setAnchorPoint(Vec2(0, 0));
	bgCloud1->setAnchorPoint(Vec2(0, 0));
	bgCloud2->setAnchorPoint(Vec2(0, 0));

	bg1->setPosition(0, 0);
	bg2->setPosition(0, size.height);
	bgCloud1->setPosition(0, 0);
	bgCloud2->setPosition(0, size.height);

	addChild(bg1);
	addChild(bg2);
	addChild(bgCloud1);
	addChild(bgCloud2);

	mWeaponLayer = WeaponLayer::create();
	addChild(mWeaponLayer);

	myWarshipLayer = WarshipLayer::create();
	addChild(myWarshipLayer);
	myWarshipLayer->setWeaponLayer(mWeaponLayer);
	auto mySmallEnemy = SmallEnenmy::create();
	mySmallEnemy->setPosition(Vec2(200, 400));
	mySmallEnemy->setWeaponLayer(mWeaponLayer);
	mySmallEnemy->shoot();
	addChild(mySmallEnemy);
	scheduleUpdate();

	return true;
}

void LostRouteGameLayer::moveBackground(Size &size){
	//移动背景
	bg1->setPosition(bg1->getPositionX(), bg1->getPositionY()
		- 3);
	bg2->setPosition(bg2->getPositionX(), bg2->getPositionY()
		- 3);
	if (bg2->getPositionY() < 0){
		auto bg1Y = bg2->getPositionY() + size.height;
		bg1->setPosition(bg2->getPositionX(), bg1Y);
	}
	if (bg1->getPositionY() < 0){
		auto bg2Y = bg1->getPositionY() + size.height;
		bg2->setPosition(bg1->getPositionX(), bg2Y);
	}

	//移动云背景
	bgCloud1->setPosition(bgCloud1->getPositionX(), bgCloud1->getPositionY()
		- 2);
	bgCloud2->setPosition(bgCloud2->getPositionX(), bgCloud2->getPositionY()
		- 2);
	if (bgCloud2->getPositionY() < 0){
		auto bgCloud1Y = bgCloud2->getPositionY() + size.height;
		bgCloud1->setPosition(bgCloud2->getPositionX(), bgCloud1Y);
	}
	if (bgCloud1->getPositionY() < 0){
		auto bgCloud2Y = bgCloud1->getPositionY() + size.height;
		bgCloud2->setPosition(bgCloud1->getPositionX(), bgCloud2Y);
	}
}

void LostRouteGameLayer::update(float time){
	auto size = Director::getInstance()->getWinSize();
	//移动背景
	moveBackground(size);
}