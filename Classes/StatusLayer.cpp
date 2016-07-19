#include <sstream>
#include "StatusLayer.h"

using std::stringstream;

bool StatusLayer::init(){
	if (!Layer::init()){
		return false;
	}

	Size size = Director::getInstance()->getWinSize();

	//暂停按钮
	auto menuItemPause = MenuItemSprite::create(Sprite::createWithSpriteFrameName(PATH_BUTTON_NORMAL_PICTURE),
		Sprite::createWithSpriteFrameName(PATH_BUTTON_PAUSE_PICTURE), CC_CALLBACK_1(StatusLayer::onClick_Pause
		, this));
	auto menu = Menu::create(menuItemPause, nullptr);
	addChild(menu, 100);

	menuItemPause->setPosition(-size.width / 2 + menuItemPause->getContentSize().width / 2,
		size.height / 2 - menuItemPause->getContentSize().height / 2 - 16);

	//显示得分
	mNumbers = Numbers::createWithSpriteFrameName(PATH_NUMBERS_PICTURE);
	mNumbers->retain();

	//进度条
	mHPValue = ProgressBar::createWithSpriteFrameName(PATH_LIFEBAR_FG_PICTURE, PATH_LIFEBAR_BG_PICTURE);
	mHPValue->setPosition(50, size.height - 20);
	mHPValue->setMaxValue(WARSHIP_MAX_HP);
	mHPValue->setMinValue(0);
	addChild(mHPValue);

	loadData();
	currentScore = 0;
	addScore(0);
	return true;
}

void StatusLayer::saveData(){
	auto userDefault = UserDefault::getInstance();
	userDefault->setIntegerForKey("maxScore", mMaxScore);
	userDefault->flush();
}

void StatusLayer::loadData(){
	auto userDefault = UserDefault::getInstance();
	mMaxScore = userDefault->getIntegerForKey("maxScore");
	updateHighScore();
}

void StatusLayer::updateHP(int newHP){
	mHPValue->setProgress(newHP);
}

void StatusLayer::addScore(int score){
	currentScore += score;
	stringstream ss;
	ss << currentScore;

	Size size = Director::getInstance()->getWinSize();
	string s_Score = ss.str();
	const char* pScore = s_Score.c_str();

	Node* ScoreNode = mNumbers->generateNumbers(pScore);
	ScoreNode->setPosition(size.width / 2 - 40, size.height - 100);

	ScoreNode->setTag(10);
	auto node = getChildByTag(10);
	if (node != nullptr){
		removeChild(node);
	}
	addChild(ScoreNode);

	if (currentScore > mMaxScore){
		mMaxScore = currentScore;
		saveData();
		updateHighScore();
	}
}

void StatusLayer::onClick_Pause(Ref* pSender){
	auto director = Director::getInstance();
	if (director->isPaused()){
		director->resume();
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
	else{
		director->pause();
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
}

void StatusLayer::updateHighScore(){
	stringstream ss;
	ss << mMaxScore;
	Size size = Director::getInstance()->getWinSize();
	string s_Score = ss.str();
	const char* pScore = s_Score.c_str();
	Node* maxScoreNode = mNumbers->generateNumbers(pScore);
	maxScoreNode->setPosition(size.width / 2 - 40, size.height - 60);
	maxScoreNode->setTag(20);
	auto node = getChildByTag(20);
	if (node != nullptr){
		removeChild(node);
	}
	addChild(maxScoreNode);
}

void StatusLayer::resetDefault(){
	updateHP(WARSHIP_MAX_HP);
	addScore(-currentScore);
}