//
//  WeaponLayer.h
//  starwar
//
//  Created by 李宁 on 15/7/7.
//
//

#ifndef __starwar__WeaponLayer__
#define __starwar__WeaponLayer__

#include "cocos2d.h"
USING_NS_CC;
class WeaponLayer : public Layer
{
public:
    __Array *weaponContainer;
    
public:
    WeaponLayer();
    ~WeaponLayer();
    virtual bool init();
    void weaponMovedFinished(Node* sender);
    CREATE_FUNC(WeaponLayer)
};


#endif /* defined(__starwar__WeaponLayer__) */
