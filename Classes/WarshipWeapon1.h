//
//  WarshipWeapon1.h
//  starwar
//
//  Created by 李宁 on 15/7/7.
//
//

#ifndef __starwar__WarshipWeapon1__
#define __starwar__WarshipWeapon1__

#include <iostream>
#include "cocos2d.h"
#include "BodyParent.h"
USING_NS_CC;
using namespace std;
class WarshipWeapon1 : public BodyParent
{
private:
    int angles[5];
public:
    
    virtual bool init();
    void setAngleIndex(int i);  // i：0到4
    CREATE_FUNC(WarshipWeapon1)
};

#endif /* defined(__starwar__WarshipWeapon1__) */
