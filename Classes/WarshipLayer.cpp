//
//  WarshipLayer.cpp
//  starwar
//
//  Created by 李宁 on 15/7/7.
//
//

#include "WarshipLayer.h"
bool WarshipLayer::init()
{
    if (!Layer::init() )
    {
        return false;
    }
    Size size = Director::getInstance()->getWinSize();
    warship = Warship::create();
    warship->setPosition(size.width / 2, 200);
    addChild(warship);
    
    schedule(schedule_selector(WarshipLayer::shootMissile),3.0f);
    return true;
}
void WarshipLayer::setWeaponLayer(WeaponLayer* weaponLayer)
{
    mWeaponLayer = weaponLayer;
    
    warship->setWeaponLayer(mWeaponLayer);

}

void WarshipLayer::shootMissile(float dt)
{
    
    if(enemyLayer != nullptr)
    {
        
        BodyParent* enemy1 = nullptr;
        BodyParent* enemy2 = nullptr;
        Size size = Director::getInstance()->getWinSize();
        
        //  选择左侧导弹跟踪的敌机
        for(ssize_t i = enemyLayer->enemyContainer->count() - 1; i >= 0 ;i--)
        {
            BodyParent* tempEnemy = dynamic_cast<BodyParent*>(enemyLayer->enemyContainer->getObjectAtIndex(i));
            if(tempEnemy != nullptr)
            {
                if(!tempEnemy->selected && tempEnemy->isVisible() && tempEnemy->getPositionY() > warship->getPositionY())
                {
                    enemy1 = tempEnemy;
                    tempEnemy->selected = true;
                    break;
                    
                }
            }
        }
        //  选择右侧导弹跟踪的敌机
        for(int i = 0; i < enemyLayer->enemyContainer->count();i++)
        {
            BodyParent* tempEnemy = dynamic_cast<BodyParent*>(enemyLayer->enemyContainer->getObjectAtIndex(i));
            if(tempEnemy != nullptr)
            {
                if(!tempEnemy->selected && tempEnemy->isVisible() && tempEnemy->getPositionY() > warship->getPositionY())
                {
                    
                    enemy2 = tempEnemy;
                    //  保证选中的两个enemy不同
                    if(enemy1 != enemy2)
                    {
                        tempEnemy->selected = true;
                        break;
                    }
                }
            }
        }
        if(enemy1 != nullptr && enemy2 != nullptr)
        {
            //  左侧导弹尽量锁定左侧的敌机，右侧导弹尽量锁定右侧的敌机
            if(enemy1->getPositionX() > enemy2->getPositionX())
            {
                auto tempEnemy = enemy1;
                enemy1 = enemy2;
                enemy2 = tempEnemy;
            }
        }
        if(enemy1 != nullptr)
        {
            
            auto missile = Missile::create();
            missile->setPosition(warship->getPositionX() - warship->getContentSize().width / 2,warship->getPositionY());
            mWeaponLayer->addChild(missile);
            
            mWeaponLayer->weaponContainer->addObject(missile);
            missile->node = enemy1;
            missile->weaponLayer = mWeaponLayer;
            enemy1->missile = missile;
            missileMovedFinished(missile);
        }
        if(enemy2 != nullptr)
        {
            auto missile = Missile::create();
            missile->setPosition(warship->getPositionX() + warship->getContentSize().width / 2,warship->getPositionY());
            mWeaponLayer->addChild(missile);
            
            mWeaponLayer->weaponContainer->addObject(missile);
            missile->node = enemy2;
            missile->weaponLayer = mWeaponLayer;
            enemy2->missile = missile;
            missileMovedFinished(missile);
        }
    }
}
void WarshipLayer::missileMovedFinished(Node* sender)
{
    auto missile = dynamic_cast<Missile*>(sender);
    
    if(missile != nullptr)
    {
        auto enemy = dynamic_cast<BodyParent*>(missile->node);
        if(enemy == nullptr)
        {
            
            return;
        }
        auto size = Director::getInstance()->getWinSize();
        if(!enemy->isVisible())
        {
            if(missile->longDistance)
            {
                
                auto actionMove = MoveTo::create(3, Vec2(missile->longDistanceX, missile->longDistanceY));
                auto actionDone = CallFuncN::create(CC_CALLBACK_1(WeaponLayer::weaponMovedFinished, mWeaponLayer));
                auto sequence = Sequence::create(actionMove,actionDone, nullptr);
                missile->runAnimAction(sequence);
                
            }

            
            return;
        }
        float x = 0;
        float y = 0;
        float radian = 0;
        float angle = 0;
        float endX = 0;
        float endY = 0;
        //  左上角
        if(enemy->getPositionX() < missile->getPositionX() && enemy->getPositionY() > missile->getPositionY())
        {
            x = missile->getPositionX() - enemy->getPositionX();
            y = enemy->getPositionY() - missile->getPositionY();
            radian = atan(y/x);
            angle = rtoa(radian);
            missile->setRotation(angle - 180);
            endX = missile->getPositionX() - 30 * cos(radian);
            endY = missile->getPositionY() + 30 * sin(radian);
            missile->longDistanceX = missile->getPositionX() - size.height * cos(radian);
            missile->longDistanceY = missile->getPositionY() + size.height * sin(radian);
            
        }
        //  右上角
        else if(enemy->getPositionX() > missile->getPositionX() && enemy->getPositionY() > missile->getPositionY())
        {
            x = enemy->getPositionX() - missile->getPositionX();
            y = enemy->getPositionY() - missile->getPositionY();
            radian = atan(y/x);
            angle = rtoa(radian);
            missile->setRotation(-angle);
            endX = missile->getPositionX() + 30 * cos(radian);
            endY = missile->getPositionY() + 30 * sin(radian);
            missile->longDistanceX = missile->getPositionX() + size.height * cos(radian);
            missile->longDistanceY = missile->getPositionY() + size.height * sin(radian);
        }
        //  左下角
        else if(enemy->getPositionX() < missile->getPositionX() && enemy->getPositionY() < missile->getPositionY())
        {
            x = missile->getPositionX() - enemy->getPositionX();
            y = missile->getPositionY() - enemy->getPositionY();
            radian = atan(y/x);
            angle = rtoa(radian);
            missile->setRotation(180-angle);
            endX = missile->getPositionX() - 30 * cos(radian);
            endY = missile->getPositionY() - 30 * sin(radian);
            
            missile->longDistanceX = missile->getPositionX() - size.height * cos(radian);
            missile->longDistanceY = missile->getPositionY() - size.height * sin(radian);
        }
        //  右下角
        else
        {
            x = enemy->getPositionX() - missile->getPositionX();
            y = missile->getPositionY() - enemy->getPositionY();
            radian = atan(y/x);
            angle = rtoa(radian);
            missile->setRotation(angle);
            endX = missile->getPositionX() + 30 * cos(radian);
            endY = missile->getPositionY() - 30 * sin(radian);
            missile->longDistanceX = missile->getPositionX() + size.height * cos(radian);
            missile->longDistanceY = missile->getPositionY() - size.height * sin(radian);
        }
        missile->longDistance = true;
        
        if(endX < 0 || endX > size.width || endY < 0 || endY > size.height)
        {
            mWeaponLayer->weaponMovedFinished(missile);
            return;
        }
        
        auto actionMove = MoveTo::create(0.05, Vec2(endX , endY));
        auto actionDone = CallFuncN::create(CC_CALLBACK_1(WarshipLayer::missileMovedFinished, this));
        auto sequence = Sequence::create(actionMove,actionDone, nullptr);
        missile->runAnimAction(sequence);
    }
}
