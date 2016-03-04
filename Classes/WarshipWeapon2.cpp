//
//  WarshipWeapon2.cpp
//  starwar
//
//  Created by 李宁 on 15/7/7.
//
//

#include "WarshipWeapon2.h"
#include "Resources.h"
bool WarshipWeapon2::init()
{
    if (!Sprite::init() )
    {
        return false;
    }
    
    auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_WARSHIP_WEAPON2);
    initWithSpriteFrame(spriteFrame);
    
    auto body = PhysicsBody::createBox(getContentSize());
    setPhysicsBody(body);
    //  旋转时要在设置body后面，否则body不会随着sprite转动而转动
    setRotation(90);
    body->setCategoryBitmask(0x01);  // 0001
    body->setContactTestBitmask(0x03);  //  0011
    body->setCollisionBitmask(0x02);   
    setTag(1);
    hp = 2;  //  生命指数为2，也可以认为杀伤力更大
    isWeapon = true;
    return true;
}
