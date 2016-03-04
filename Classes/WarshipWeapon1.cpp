//
//  WarshipWeapon1.cpp
//  starwar
//
//  Created by 李宁 on 15/7/7.
//
//

#include "WarshipWeapon1.h"
#include "Resources.h"
bool WarshipWeapon1::init()
{
    if (!Sprite::init() )
    {
        return false;
    }
    angles[0] = -120;
    angles[1] = -100;
    angles[2] = -90;
    angles[3] = -80;
    angles[4] = -60;
    auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_WARSHIP_WEAPON1);
    initWithSpriteFrame(spriteFrame);
    auto body = PhysicsBody::createBox(getContentSize());
    setPhysicsBody(body);
    body->setCategoryBitmask(0x01);  // 0001
    body->setContactTestBitmask(0x03);  //  0011
    body->setCollisionBitmask(0x02);
    
    setTag(1);
    hp = 1;
    isWeapon = true;
    return true;
}

void WarshipWeapon1::setAngleIndex(int i)
{
    if(i >= 0 && i <= 4)
    {
        setRotation(angles[i]);
    }
    else
    {
        setRotation(angles[2]);
    }
}

