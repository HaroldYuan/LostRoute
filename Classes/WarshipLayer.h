//
//  WarshipLayer.h
//  starwar
//
//  Created by 李宁 on 15/7/7.
//
//

#ifndef __starwar__WarshipLayer__
#define __starwar__WarshipLayer__
#include <iostream>
#include "cocos2d.h"
#include "Warship.h"
#include "EnemyLayer.h"
#include "Missile.h"
USING_NS_CC;
class WarshipLayer : public Layer
{
private:
    WeaponLayer* mWeaponLayer;
private:
    //  用于为导弹随机选择目标敌机
    void shootMissile(float dt);
public:
    Warship* warship;
    EnemyLayer* enemyLayer;
public:
    virtual bool init();
    //  跟踪目标敌机（计算飞行路径）
    void missileMovedFinished(Node* sender);
    void setWeaponLayer(WeaponLayer* weaponLayer);
    CREATE_FUNC(WarshipLayer)
};


#endif /* defined(__starwar__WarshipLayer__) */
