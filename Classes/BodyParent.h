//
//  BodyParent.h
//  starwar
//
//  Created by 李宁 on 15/7/7.
//
//

#ifndef __starwar__BodyParent__
#define __starwar__BodyParent__
#include "cocos2d.h"


USING_NS_CC;
//  定义了刚体（Body）中公用的方法和成员变量
class BodyParent : public Sprite
{
    
public:
    int hp = 1;  //  当前Body的生命值
    int maxHP = 1;  //  最大Body的生命值
    bool selected = false;  //  当前被导弹选中
    BodyParent* node = nullptr;  // 保存与当前Body相关的Node
    BodyParent* missile = nullptr;
    bool isWeapon = false;
public:
    //  用于产生爆炸效果的特效，不一定每一个Body都实现
    virtual void explode();
    //  不同的body，可能碰撞一次不会被摧毁，所有的Body必须实现
    //  lethality表示杀伤力指数，当两个Body碰撞时，需要考虑这两个Body的杀伤力指数，如果杀伤力指数相同
    //  同归于尽，否则，杀伤力指数小的Body被销毁。杀伤力大的Body的hp也同时会减小
    virtual bool collide(int lethality);
    //  在任何情况下，一次性摧毁body。通常用于核弹。
    virtual void collide();
    
    
};



#endif /* defined(__starwar__BodyParent__) */
