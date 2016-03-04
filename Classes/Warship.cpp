//
//  Warship.cpp
//  starwar
//
//  Created by 李宁 on 15/7/7.
//
//

#include "Warship.h"
#include "WarshipWeapon1.h"
#include "WarshipWeapon2.h"
bool Warship::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    weaponCount = 1;
    weaponType = 1;
    auto cache = AnimationCache::getInstance();
    auto animation = cache->getAnimation(ANIM_WARSHIP1);
    animation->setLoops(-1);
    auto animate = Animate::create(animation);
    runAction(animate);
    auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(PATH_WARSHIP);
    initWithSpriteFrame(spriteFrame);
    
    auto width = getContentSize().width;
    auto height = getContentSize().height;
    Vec2 points[] = { Vec2(0, height/2), Vec2(width/2, -20), Vec2(-width/2, -20)};
    auto body = PhysicsBody::createPolygon(points, 3);
    
    setPhysicsBody(body);
    body->setCategoryBitmask(0x01);  // 0001
    body->setContactTestBitmask(0x03);  //  0011
    body->setCollisionBitmask(0x02);
    //  用手指拖动飞船
    auto listener = EventListenerTouchOneByOne::create();

    
    // 使用 lambda 表达式实现 onTouchBegan 事件回调函数
    listener->onTouchBegan = [&](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        
        Rect rect = Rect(0,0, s.width, s.height);
        // 移动当前按钮精灵的坐标位置
        //  printf("%f\n",-s.width/2);
        if (rect.containsPoint(locationInNode))
        {
       

            mTouchFlag = true;
         }
        return true;
    };
    // 使用 lambda 实现 onTouchMoved 事件回调函数
    listener->onTouchMoved = [&](Touch* touch, Event* event){
        if(Director::getInstance()->isPaused())
        {
            return;
        }
         auto target = static_cast<Sprite*>(event->getCurrentTarget());
    
        if (mTouchFlag)
        {
            target->setPosition(target->getPosition() + touch->getDelta());
        }
        
    };
    listener->onTouchEnded = [&](Touch* touch, Event* event){
         mTouchFlag = false;

    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    setTag(1);
    hp = WARSHIP_MAX_HP;
    return true;
}
void Warship::setWeaponLayer(WeaponLayer* weaponLayer)
{
    mWeaponLayer = weaponLayer;
}
void Warship::shoot()
{
    if(weaponType == 1)
    {
        if(isScheduled(schedule_selector(Warship::repeatShoot1)))
        {
            //  武器1已经启动
            return;
        }
        if(isScheduled(schedule_selector(Warship::repeatShoot2)))
        {
            //  当启动武器1时，如果武器2已经启动，需要关闭武器2
            unschedule(schedule_selector(Warship::repeatShoot2));
        }
        
        schedule(schedule_selector(Warship::repeatShoot1),0.3);
    }
    else if(weaponType == 2)
    {
        if(isScheduled(schedule_selector(Warship::repeatShoot2)))
        {
            //  武器2已经启动
            return;
        }
        if(isScheduled(schedule_selector(Warship::repeatShoot1)))
        {
            //  当启动武器2时，如果武器1已经启动，需要关闭武器1
            unschedule(schedule_selector(Warship::repeatShoot1));
        }
        schedule(schedule_selector(Warship::repeatShoot2),0.3);
    }

}

void Warship::repeatShoot1(float dt)
{
    auto size = Director::getInstance()->getWinSize();
    int angles[] = {50, 30, 0, -30, -50};
    int weaponOffset[] = {20, 10, 0, -10, -20};   //  Weapon1水平偏移量
    for(int i = 0; i < weaponCount;i++)
    {
        auto weapon = WarshipWeapon1::create();
        //  根据weaponCount的值算出新索引
        //  weaponCount：1  索引从2开始   weaponCount：3  索引从1开始   weaponCount：5  索引从0开始
        auto index = i + 2 - weaponCount / 2;
        weapon->setAngleIndex(index);
        auto weaponStartX = getPositionX() - weaponOffset[index];
        auto weaponStartY = getPositionY() + getContentSize().height / 2 + weapon->getContentSize().height / 2 ;
        
        weapon->setPosition(weaponStartX,weaponStartY);
        
        mWeaponLayer->addChild(weapon);
        auto moveDuration = 2 * (size.height - weaponStartY) / size.height;
        //  计算Weapon移动的目标位置
        auto weaponEndX = getPositionX() ;
        
        auto weaponEndY = size.height + weapon->getContentSize().height / 2;

        weaponEndX -= tan(angles[index] * PI/180) * (getPositionY() + getContentSize().height / 2);
        auto actionMove = MoveTo::create(moveDuration, Vec2(weaponEndX, weaponEndY));
        
        auto actionDone = CallFuncN::create(CC_CALLBACK_1(WeaponLayer::weaponMovedFinished, mWeaponLayer));
        
        auto sequence = Sequence::create(actionMove,actionDone,nullptr);
        mWeaponLayer->weaponContainer->addObject(weapon);
        weapon->setVisible(true);
        weapon->runAction(sequence);
        
    }

}

void Warship::repeatShoot2(float dt)
{
    auto size = Director::getInstance()->getWinSize();
    int weaponOffset[] = {20, 10, 0, -10, -20};   //  Weapon2水平偏移量
    for(int i = 0; i < weaponCount;i++)
    {
        auto weapon = WarshipWeapon2::create();
        //  根据weaponCount的值算出新索引
        //  weaponCount：1  索引从2开始   weaponCount：3  索引从1开始   weaponCount：5  索引从0开始
        auto index = i + 2 - weaponCount / 2;
        auto weaponStartX = getPositionX() - weaponOffset[index];
        auto weaponStartY = getPositionY() + getContentSize().height / 2 + 6 ;
        
        weapon->setPosition(weaponStartX,weaponStartY);
        
        mWeaponLayer->addChild(weapon);
        auto moveDuration = 2 * (size.height - weaponStartY) / size.height;
        //  计算Weapon移动的目标位置
        auto weaponEndX = weaponStartX ;
        
        auto weaponEndY = size.height + weapon->getContentSize().height / 2;
        
        auto actionMove = MoveTo::create(moveDuration, Vec2(weaponEndX, weaponEndY));
        
        auto actionDone = CallFuncN::create(CC_CALLBACK_1(WeaponLayer::weaponMovedFinished, mWeaponLayer));
        
        auto sequence = Sequence::create(actionMove,actionDone,nullptr);
        mWeaponLayer->weaponContainer->addObject(weapon);
        weapon->setVisible(true);
        weapon->runAction(sequence);
        
    }
    
}
void Warship::changeWeaponCount(int newType)
{
    //  只有碰到的Type与当前Type相同，才会变化武器数量
    if(newType != weaponType)
    {
        return;
    }
    
    if(weaponCount == 5)
    {
        weaponCount = 1;
    }
    else
    {
        weaponCount += 2;
    }
}
void Warship::changeWeaponType(int newType)
{
    if(newType == weaponType)
    {
        return;
    }
    
    if(weaponType == 1)
    {
        weaponType = 2;
    }
    else
    {
        weaponType = 1;
    }
    weaponCount = 1;
    shoot();
}
void Warship::addHP(int hp)
{
    if(hp + this->hp > WARSHIP_MAX_HP)
    {
        this->hp = WARSHIP_MAX_HP;
    }
    else
    {
        this->hp += hp;
    }
}