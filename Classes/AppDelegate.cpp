#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Resources.h"
#include "StarwarGameScene.h"
USING_NS_CC;
using namespace CocosDenshion;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    director->getOpenGLView()->setDesignResolutionSize(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, ResolutionPolicy::EXACT_FIT);
    register_all_packages();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_USER_INTERFACE_LIST, PATH_USER_INTERFACE_PICTURE);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_GAME_UIS_LIST, PATH_GAME_UIS_PICTURE);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_GAME_UI1_LIST, PATH_GAME_UI1_PICTURE);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_PLAYER_LIST, PATH_PLAYER_PICTURE);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_BULLET_LIST, PATH_BULLET_PICTURE);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_ENEMYS_LIST, PATH_ENEMYS_PICTURE);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_BOMB_LIST, PATH_BOMB_PICTURE);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_DROP_LIST, PATH_DROP_PICTURE);
    
    
    AnimationCache::getInstance()->addAnimationsWithFile(PATH_PLAYER_LIST);
    AnimationCache::getInstance()->addAnimationsWithFile(PATH_BULLET_LIST);
    
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(EFFECT_SOUND_BACKGROUND);
    
    SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_SOUND_EXPLOSION1);
    SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_SOUND_EXPLOSION2);
    SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_SOUND_EXPLOSION3);
    
    SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_SOUND_MISSILE1);
    SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_SOUND_MISSILE2);
    SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_SOUND_MISSILE3);
    // create a scene. it's an autorelease object
  //  auto scene = HelloWorld::createScene();

    // run
   // director->runWithScene(scene);
    auto scene = (StarwarGameScene*)StarwarGameScene::createWithPhysics();
    scene->run();
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
     SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    if(!Director::getInstance()->isPaused())
    {
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        SimpleAudioEngine::getInstance()->resumeAllEffects();
    }
    // if you use SimpleAudioEngine, it must resume here
    //
}
