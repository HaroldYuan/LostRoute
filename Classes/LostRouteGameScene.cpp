#include "LostRouteGameScene.h"
#include "LostRouteGameLayer.h"


void LostRouteGameScene::run()
{
	// 'layer' is an autorelease object
	auto layer = LostRouteGameLayer::create();
	if(layer!=nullptr)
	addChild(layer);
	Director::getInstance()->runWithScene(this);
	
}


