#include "Numbers.h"

bool Numbers::init(){
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
	x = spriteFrame->getRect().origin.x;
	y = spriteFrame->getRect().origin.y;
	width = spriteFrame->getRect().size.width / 10;
	height = spriteFrame->getRect().size.height;
	return true;
}

string Numbers::integerToString(int value){
	ostringstream str_stream;
	str_stream << value;
	return str_stream.str();
}

Node* Numbers::generateNumbers(const string &numbers){
	Node* node = Node::create();
	char number;
	for (int i = 0; i < numbers.length(); i++){
		number = numbers.at(i);
		Node* nodeNumber = generateNumber(number - 48);
		nodeNumber->setAnchorPoint(Vec2(0, 0));
		nodeNumber->setPosition(Vec2(i*width, 0));
		node->addChild(nodeNumber);
	}
	return node;
}

Node* Numbers::generateNumber(int number){
	auto sprite = Sprite::createWithSpriteFrameName(spriteFrameName);
	sprite->setTextureRect(Rect(x + number*width, y, width, height));
	return sprite;
}

Numbers* Numbers::createWithSpriteFrameName(const char *spFrameName){
	Numbers *pnum = new Numbers();
	
	if (pnum != nullptr){
		pnum->spriteFrameName = spFrameName;
	}

	if (pnum != nullptr && pnum->init()){
		
		pnum->autorelease();
		return pnum;
	}

	CC_SAFE_DELETE(pnum);
	return nullptr;
}