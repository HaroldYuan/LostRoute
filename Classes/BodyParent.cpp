//
//  BodyParent.cpp
//  starwar
//
//  Created by 李宁 on 15/7/7.
//
//

#include "BodyParent.h"
bool BodyParent::collide(int lethality)
{
    if(lethality >= hp)
    {
        //  默认情况下，只有Body被销毁时才会显示爆炸效果，如果要改变这一默认值，需要重写collide方法
        explode();
        collide();
        
        return true;
    }
    else
    {
        hp -= lethality;
        return false;
    }
}
//  在任何情况下，一次性摧毁body。通常用于核弹。
void BodyParent::collide()
{
    setVisible(false);
    unscheduleAllCallbacks();
}

void BodyParent::explode()
{
    
}

