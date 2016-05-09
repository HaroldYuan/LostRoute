#ifndef Resources_h__
#define Resources_h__
//�ɴ�ͼƬ
#define PATH_WARSHIP_1_PICTURE  "warship.png"
#define PATH_WARSHIP_PLIST "list/warship.plist"

//�л�ͼƬ
#define  PATH_SMALLENEMY1_PICTURE "enemy_1.png"
#define  PATH_SMALLENEMY2_PICTURE "enemy_2.png"
#define  PATH_BIGENEMY_PICTURE    "enemy_3.png"
#define  PATH_ENEMY_PLIST        "list/enemy.plist"

//����ͼƬ
#define PATH_BACKGROUND_PICTURE "img_bg_level_1.jpg"
#define PATH_CLOUD_BACKGROUND_PICTURE "cloud_background.png"
#define PATH_IMGBACKGROUND_PLIST "list/img_bg.plist"

//�ӵ�ͼƬ
#define PATH_WARSHIP_BULLET_PICTURE "bullet.png"
#define PATH_WARSHIP_WEAPON1_PICTURE "warship_bullet_1.png"
#define PATH_WARSHIP_WEAPON2_PICTURE "warship_bullet_2.png"
#define PATH_ENEMY_WEAPON1_PICTURE   "enemy_bullet_1.png"
#define PATH_ENEMY_WEAPON2_PICTURE   "enemy_bullet_2.png"
#define PATH_WARSHIP_BULLET_PLIST "list/bullet.plist"

//DropͼƬ
#define PATH_DROP_ADDBULLET_PICTURE "addbullet.png"
#define PATH_DROP_ADDLIFE_PICTURE   "blood.png"
#define PATH_DROP_PLIST "list/drop.plist"

//�ɴ�����ֵ
#define  WARSHIP_MAX_HP 30

//С�͵л�1����ֵ
#define  SmallEnemy1_MAX_HP 2

//С�͵л�2����ֵ
#define  SmallEnemy2_MAX_HP 2

//���͵л�����ֵ
#define BigEnemy_MAX_HP 15

//����PI
#define  PI 3.14

//������������
#define weapon_lasor   1
#define weapon_torpedo 2

//����л�����
#define smallenemy_1 1
#define smallEnemy_2 2

//��ըЧ��
#define PATH_EFFECT1_PLIST "explosion/explosion1.plist"
#define PATH_EFFECT2_PLIST  "explosion/explosion2.plist"

//���巢����ײ����������
//#define Hero   0
//#define Enemy  1
enum ContactTag{
	Hero = 0,
	Enemy
};

//����л�AI��������
enum ActionType{
	MoveToBezierLeft = 0,
	MoveToBezierRight,
	MoveToUiniform,
	MoveToLine
};
#endif // Resources_h__
