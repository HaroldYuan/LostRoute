//
//  WarshipWeapon2.h
//  starwar
//
//  Created by 李宁 on 15/7/7.
//
//

#ifndef __starwar__WarshipWeapon2__
#define __starwar__WarshipWeapon2__

#include <iostream>
#include "cocos2d.h"
#include "BodyParent.h"
USING_NS_CC;
using namespace std;
class WarshipWeapon2 : public BodyParent
{
public:
    virtual bool init();
    CREATE_FUNC(WarshipWeapon2)
};


#endif /* defined(__starwar__WarshipWeapon2__) */
