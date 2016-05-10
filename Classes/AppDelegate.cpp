#include "AppDelegate.h"
#include "LostRouteGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
	//�������������
	srand((unsigned)time(0));
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLView::create("My Game");
		glview->setFrameSize(320, 600);
		director->setOpenGLView(glview);
	}

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	//���ر�������֡����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_IMGBACKGROUND_PLIST);
	//���طɴ�����֡����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_WARSHIP_PLIST);
	//�����ӵ�����֡����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_WARSHIP_BULLET_PLIST);
	//���صл�����֡����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_ENEMY_PLIST);
	//����Drop�ྫ��֡����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_DROP_PLIST);

	//��ʼ����������
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(PATH_BACKGROUND_MUSIC);

	//��ʼ����Ч
	SimpleAudioEngine::getInstance()->preloadEffect(PATH_WARSHIP_WEAPON_MUSIC);
	SimpleAudioEngine::getInstance()->preloadEffect(PATH_ENEMY_WEAPON_MUSIC);
	SimpleAudioEngine::getInstance()->preloadEffect(PATH_ENEMY_EXPLOSION_MUSIC);
	SimpleAudioEngine::getInstance()->preloadEffect(PATH_WARSHIP_EXPLOSION_MUSIC);
	SimpleAudioEngine::getInstance()->preloadEffect(PATH_DROP_MUSIC);
	SimpleAudioEngine::getInstance()->preloadEffect(PATH_SWITCHWEAPON_MUSIC);

	// create a scene. it's an autorelease object
	auto scene = (LostRouteGameScene*)LostRouteGameScene::createWithPhysics();
	// run
	//director->runWithScene(scene);
	scene->run();
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	SimpleAudioEngine::getInstance()->stopAllEffects();
	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
	if (!Director::getInstance()->isPaused()){
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		SimpleAudioEngine::getInstance()->resumeAllEffects();
	}
	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}