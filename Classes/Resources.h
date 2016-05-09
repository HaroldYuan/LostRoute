#ifndef Resources_h__
#define Resources_h__
//飞船图片
#define PATH_WARSHIP_1_PICTURE  "warship.png"
#define PATH_WARSHIP_PLIST "list/warship.plist"

//敌机图片
#define  PATH_SMALLENEMY1_PICTURE "enemy_1.png"
#define  PATH_SMALLENEMY2_PICTURE "enemy_2.png"
#define  PATH_BIGENEMY_PICTURE    "enemy_3.png"
#define  PATH_ENEMY_PLIST        "list/enemy.plist"

//背景图片
#define PATH_BACKGROUND_PICTURE "img_bg_level_1.jpg"
#define PATH_CLOUD_BACKGROUND_PICTURE "cloud_background.png"
#define PATH_IMGBACKGROUND_PLIST "list/img_bg.plist"

//子弹图片
#define PATH_WARSHIP_BULLET_PICTURE "bullet.png"
#define PATH_WARSHIP_WEAPON1_PICTURE "warship_bullet_1.png"
#define PATH_WARSHIP_WEAPON2_PICTURE "warship_bullet_2.png"
#define PATH_ENEMY_WEAPON1_PICTURE   "enemy_bullet_1.png"
#define PATH_ENEMY_WEAPON2_PICTURE   "enemy_bullet_2.png"
#define PATH_WARSHIP_BULLET_PLIST "list/bullet.plist"

//Drop图片
#define PATH_DROP_ADDBULLET_PICTURE "addbullet.png"
#define PATH_DROP_ADDLIFE_PICTURE   "blood.png"
#define PATH_DROP_PLIST "list/drop.plist"

//飞船生命值
#define  WARSHIP_MAX_HP 30

//小型敌机1生命值
#define  SmallEnemy1_MAX_HP 2

//小型敌机2生命值
#define  SmallEnemy2_MAX_HP 2

//大型敌机生命值
#define BigEnemy_MAX_HP 15

//定义PI
#define  PI 3.14

//定义武器类型
#define weapon_lasor   1
#define weapon_torpedo 2

//定义敌机类型
#define smallenemy_1 1
#define smallEnemy_2 2

//爆炸效果
#define PATH_EFFECT1_PLIST "explosion/explosion1.plist"
#define PATH_EFFECT2_PLIST  "explosion/explosion2.plist"

//定义发生碰撞的物体类型
//#define Hero   0
//#define Enemy  1
enum ContactTag{
	Hero = 0,
	Enemy
};

//定义敌机AI动作类型
enum ActionType{
	MoveToBezierLeft = 0,
	MoveToBezierRight,
	MoveToUiniform,
	MoveToLine
};
#endif // Resources_h__
