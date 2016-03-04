//
//  Resources.h
//  Thunder
//
//  Created by 李宁 on 15/6/11.
//
//

#ifndef Resources_h
#define Resources_h

#define DEFAULT_SCREEN_WIDTH  480.0
#define DEFAULT_SCREEN_HEIGHT 800.0


//  CCNode Tag
//  Warship
#define TAG_WARSHIP 1

//  Warship Max HP
#define WARSHIP_MAX_HP 100

//  动画
#define ANIM_WARSHIP1 "animation1"
#define ANIM_WARSHIP2 "animation2"

#define ANIM_WEAPON_PHOTONTORPEDO "warshipweapon1"
#define ANIM_WEAPON_MISSILE "warshipmissile"

//  定义plist和对应的png图像路径
#define PATH_USER_INTERFACE_LIST "list/user_interface.plist"
#define PATH_USER_INTERFACE_PICTURE "list/user_interface.png"
#define PATH_GAME_UIS_LIST "list/game_uis.plist"
#define PATH_PLAYER_LIST "list/player.plist"
#define PATH_BULLET_LIST "list/bullet.plist"
#define PATH_ENEMYS_LIST "list/enemys.plist"
#define PATH_EXPLOSION_LIST "list/explosion.plist"
#define PATH_BOMB_LIST "list/bomb.plist"
#define PATH_DROP_LIST "list/drops.plist"

#define PATH_GAME_UIS_PICTURE "list/game_uis.png"
#define PATH_GAME_UI1_LIST "list/game_ui1.plist"
#define PATH_GAME_UI1_PICTURE "list/game_ui1.png"
#define PATH_PLAYER_PICTURE "list/player.png"
#define PATH_BULLET_PICTURE "list/bullet.png"
#define PATH_ENEMYS_PICTURE "list/enemys.png"
#define PATH_EXPLOSION_PICTURE "list/explosion.png"
#define PATH_BOMB_PICTURE "list/bomb.png"
#define PATH_DROP_PICTURE "list/drops.png"

//  定义plist中图像的路径

//  PATH_USER_INTERFACE_LIST
#define PATH_BACKGROUND_PICTURE "background.jpg"
#define PATH_GAME_BACKGROUND_PICTURE "game_background.jpg"
#define PATH_CLOUD_BACKGROUND_PICTURE "cloud_background.png"
#define PATH_THUNDER_TITLE_PICTURE  "thunder_title.png"
#define PATH_NEWGAME_NORMAL_PICTURE "btn_newgame_n.png"
#define PATH_NEWGAME_PUSH_PICTURE "btn_newgame_p.png"
#define PATH_SET_NORMAL_PICTURE "btn_set_n.png"
#define PATH_SET_PUSH_PICTURE "btn_set_p.png"
#define PATH_HOWTOPLAY_NORMAL_PICTURE "btn_howtoplay_n.png"
#define PATH_HOWTOPLAY_PUSH_PICTURE "btn_howtoplay_p.png"

#define PATH_NUMBER1_PICTURE "num_pet_lv.png"
#define PATH_NUMBER2_PICTURE "number1.png"


//  PATH_GAME_UIS_LIST
#define PATH_GAME_STATUS_BACKGROUND_PICTURE "bg_game_status.png"
#define PATH_BUTTON_PAUSE_NORMAL_PICTURE  "btn_pause_n.png"
#define PATH_BUTTON_PAUSE_PUSH_PICTURE "btn_pause_p.png"
#define PATH_TEXT_SCORE_PICTURE "text_score_hp.png"

// drops.plist
#define PATH_DROP_COIN_PICTURE1 "drop_0_0.png"
#define PATH_DROP_COIN_PICTURE2 "drop_0_1.png"
#define PATH_DROP_LIFE_PICTURE1 "drop_1_0.png"
#define PATH_DROP_LIFE_PICTURE2 "drop_1_1.png"
#define PATH_DROP_WEAPON1_PICTURE1 "drop_2_0.png"
#define PATH_DROP_WEAPON1_PICTURE2 "drop_2_1.png"
#define PATH_DROP_WEAPON2_PICTURE1 "drop_3_0.png"
#define PATH_DROP_WEAPON2_PICTURE2 "drop_3_1.png"

#define PATH_DROP_BOMB_PICTURE1 "drop_5_0.png"
#define PATH_DROP_BOMB_PICTURE2 "drop_5_1.png"
   
// Enemys 
#define PATH_ENEMY1 "e10.png"
#define PATH_ENEMY2 "e20.png"
#define PATH_ENEMY3 "e30.png"
#define PATH_ENEMY4 "e40.png"
#define PATH_ENEMY5 "e50.png"
#define PATH_ENEMY6 "e60.png"
#define PATH_ENEMY7 "e70.png"
//  Warship Weapon
#define PATH_WARSHIP_WEAPON1 "bullet_s_0.png"
#define PATH_WARSHIP_WEAPON2 "bullet_o_0.png"
#define PATH_WARSHIP_MISSILE "trackingmissile_0.png"

#define PATH_WARSHIP "player00_l.png"

//  各种移动效果（主要针对Enemy）
#define EFFECT_MOTION_UP_DOWN_UNIFORM  1                        //  从上到下匀速运动
#define EFFECT_MOTION_LEFT_RIGHT_UNIFORM 2                      //  从左到右匀速运动
#define EFFECT_MOTION_UP_DOWN_UNIFORM_ACCELERATION 3            //  从上到下先匀速，然后加速运动
#define EFFECT_MOTION_UP_DOWN_UNIFORM_BEZIER_ACCELERATION 4     //  从上到下先匀速，然后贝塞尔曲线加速运动
#define EFFECT_MOTION_UP_DOWN_UNIFORM_BEZIER 5                  //  从上到下使用贝塞尔曲线运动（先匀速，再加速）
#define EFFECT_MOTION_LEFT_RIGHT_BEZIER_UNIFORM 6               //  从左到右使用贝塞尔曲线匀速运动
#define EFFECT_MOTION_RIGHT_LEFT_BEZIER_ACCELERATION 7          //  从左到右使用贝塞尔曲线加速运动
#define EFFECT_MOTION_DOWN_UP_UNIFORM_ACCELERATION 8            //  从下到上先匀速，再加速运动

//  各种爆炸效果
#define EFFECT_EXPLOSION_BURNINGFLARE       "explosion/burningFlare.plist"
#define EFFECT_EXPLOSION_BURSTFLARE         "explosion/burstFlare.plist"
#define EFFECT_EXPLOSION_DUSTBURST          "explosion/dustBurst.plist"
#define EFFECT_EXPLOSION_DUSTRISE           "explosion/dustRise.plist"
#define EFFECT_EXPLOSION_GROWINGFLARE       "explosion/growingFlare.plist"
#define EFFECT_EXPLOSION_STARGLOW           "explosion/starGlow.plist"

//  与爆炸效果对应的类型
#define TYPE_EFFECT_EXPLOSION_BURNINGFLARE       1
#define TYPE_EFFECT_EXPLOSION_BURSTFLARE         2
#define TYPE_EFFECT_EXPLOSION_DUSTBURST          3
#define TYPE_EFFECT_EXPLOSION_DUSTRISE           4
#define TYPE_EFFECT_EXPLOSION_GROWINGFLARE       5


//  各种音频效果

#define EFFECT_SOUND_BACKGROUND             "sounds/background.mp4"

#define EFFECT_SOUND_EXPLOSION1             "sounds/explosion1.wav"
#define EFFECT_SOUND_EXPLOSION2             "sounds/explosion2.wav"
#define EFFECT_SOUND_EXPLOSION3             "sounds/explosion3.wav"
#define EFFECT_SOUND_MISSILE1               "sounds/missile1.wav"
#define EFFECT_SOUND_MISSILE2               "sounds/missile2.wav"
#define EFFECT_SOUND_MISSILE3               "sounds/missile3.wav"

//  与音频效果对应的类型
#define TYPE_EFFECT_SOUND_EXPLOSION1        1
#define TYPE_EFFECT_SOUND_EXPLOSION2        2
#define TYPE_EFFECT_SOUND_EXPLOSION3        3
#define TYPE_EFFECT_SOUND_MISSILE1          21
#define TYPE_EFFECT_SOUND_MISSILE2          22
#define TYPE_EFFECT_SOUND_MISSILE3          23

//  敌人的武器
#define WEAPON_SMALL_ENEMY "bomb1.png"
#define WEAPON_BIG_ENEMY "bomb10.png"

// maths
#define PI 3.1415926
#define ator(angle) angle * PI / 180
#define rtoa(radian) radian * 180 / PI


#endif /* Resources_h */
