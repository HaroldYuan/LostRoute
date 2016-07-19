#include "LostRouteGameScene.h"
#include "LostRouteGameLayer.h"

Scene* LostRouteGameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = LostRouteGameLayer::create();
	if (layer != nullptr){
		scene->addChild(layer);
		Vect gravity = Vect(0.0f, 0.0f);
		scene->getPhysicsWorld()->setGravity(gravity);
		//getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		return scene;
	}
}