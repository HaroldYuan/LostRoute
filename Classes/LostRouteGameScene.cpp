#include "LostRouteGameScene.h"
#include "LostRouteGameLayer.h"

void LostRouteGameScene::run()
{
	// 'layer' is an autorelease object
	auto layer = LostRouteGameLayer::create();
	if (layer != nullptr){
		addChild(layer);
		Vect gravity = Vect(0.0f, 0.0f);
		getPhysicsWorld()->setGravity(gravity);
		//getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		Director::getInstance()->runWithScene(this);
	}
}