#include "AppDelegate.h"
#include "LostRouteGameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLView::create("My Game");
		glview->setFrameSize(320, 600);
		director->setOpenGLView(glview);
	}

	// turn on display FPS
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	//¼ÓÔØ±³¾°¾«ÁéÖ¡»º´æ
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_IMGBACKGROUND_PLIST);
	//¼ÓÔØ·É´¬¾«ÁéÖ¡»º´æ
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_WARSHIP_PLIST);
	//¼ÓÔØ×Óµ¯¾«ÁéÖ¡»º´æ
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_WARSHIP_BULLET_PLIST);
	//¼ÓÔØµÐ»ú¾«ÁéÖ¡»º´æ
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_ENEMY_PLIST);

	// create a scene. it's an autorelease object
	//auto scene = HelloWorld::createScene();
	auto scene = (LostRouteGameScene*)LostRouteGameScene::createWithPhysics();
	// run
	//director->runWithScene(scene);
	scene->run();
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}