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

	addChild(WeaponLayer::getInstance());

	myWarshipLayer = WarshipLayer::create();
	addChild(myWarshipLayer);

	mEnemyLayer = EnemyLayer::create();
	addChild(mEnemyLayer);

	mDropLayer = DropLayer::create();
	addChild(mDropLayer);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(LostRouteGameLayer::onContactBegin, this);

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();

	SimpleAudioEngine::getInstance()->playBackgroundMusic(PATH_BACKGROUND_MUSIC, true);

	return true;
}

bool LostRouteGameLayer::onContactBegin(PhysicsContact& contact){
	if (contact.getShapeA()->getBody()->getNode() == nullptr
		|| contact.getShapeB()->getBody()->getNode() == nullptr){
		return true;
	}

	int tagA = contact.getShapeA()->getBody()->getNode()->getTag();
	int tagB = contact.getShapeB()->getBody()->getNode()->getTag();
	//只有敌我双方的Body发生碰撞才进行检测
	if (tagA != tagB){
		BodyParent* bodyA = dynamic_cast<BodyParent*>(contact.getShapeA()->getBody()->getNode());
		BodyParent* bodyB = dynamic_cast<BodyParent*>(contact.getShapeB()->getBody()->getNode());
		if (bodyA != nullptr && bodyB != nullptr){
			if (bodyA->isVisible() && bodyB->isVisible()){
				if (bodyA->isWeapon && bodyB->isWeapon){
					return true;
				}
				//对Drop进行碰撞检测
				auto drop1 = dynamic_cast<Drop*>(bodyA);
				auto drop2 = dynamic_cast<Drop*>(bodyB);

				//如果两个碰撞的Body都是Drop,忽略
				if (drop1 != nullptr && drop2 != nullptr)
				{
					return true;
				}
				auto warship1 = dynamic_cast<Warship*>(bodyA);
				auto warship2 = dynamic_cast<Warship*>(bodyB);

				//如果两个碰撞的Body，一个是Drop,另一个不是飞船，忽略
				if (drop1 != nullptr && warship2 == nullptr)
				{
					return true;
				}
				if (drop2 != nullptr && warship1 == nullptr)
				{
					return true;
				}

				Drop* drop = nullptr;
				Warship* warship = nullptr;

				if (drop1 != nullptr && warship2 != nullptr){
					//bodyA为Drop,bodyB为Warship
					drop = drop1;
					warship = warship2;
				}
				else if (drop2 != nullptr && warship1 != nullptr){
					//bodyB为Drop,bodyA为Warship
					drop = drop2;
					warship = warship1;
				}

				if (drop != nullptr && warship != nullptr){
					SimpleAudioEngine::getInstance()->playEffect(PATH_DROP_MUSIC, false);
					if (drop->dropType == Drop::addBullet){
						warship->changeWeaponType();
						drop->hideDrop();
						return true;
					}
					else{
						warship->addHP(10);
						drop->hideDrop();
						return true;
					}
				}

				int hpA = bodyA->hp;
				int hpB = bodyB->hp;

				bodyA->collide(hpB);
				bodyB->collide(hpA);
			}
		}
	}

	return true;
}

void LostRouteGameLayer::moveBackground(Size &size){
	//移动背景
	bg1->setPosition(bg1->getPositionX(), bg1->getPositionY()
		- 2);
	bg2->setPosition(bg2->getPositionX(), bg2->getPositionY()
		- 2);
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
		- 1.5);
	bgCloud2->setPosition(bgCloud2->getPositionX(), bgCloud2->getPositionY()
		- 1.5);
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