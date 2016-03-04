//
//  Warship.h
//  starwar
//
//  Created by 李宁 on 15/7/7.
//
//

#ifndef __starwar__Warship__
#define __starwar__Warship__

#include "cocos2d.h"
#include "Resources.h"
#include "BodyParent.h"
#include "WeaponLayer.h"
USING_NS_CC;
class Warship :public BodyParent
{
private:
    WeaponLayer* mWeaponLayer;
    bool mTouchFlag = false;
public:
    int weaponCount;  // 武器数，奇数个数：1、3、5
    int weaponType;  //  武器类型   1或2
public:

    virtual bool init();
    void shoot();
    void repeatShoot1(float dt);
    void repeatShoot2(float dt);
    void setWeaponLayer(WeaponLayer* weaponLayer);
    void changeWeaponCount(int newType);
    void changeWeaponType(int newType);
    void addHP(int hp);
    
    CREATE_FUNC(Warship)
};


#endif /* defined(__starwar__Warship__) */
