#pragma once

//宏
//#define DEBUG

//植物种类
#define PLANT_KIND_NUM 11
enum class PLANT {
	SUNFLOWER, //向日葵
	PEA_SHOOTER, //豌豆射手
	DOUBLE_SHOOTER, //双发射手
	ICE_SHOOTER, //寒冰射手
	POTATO, //土豆雷
	NUT, //坚果墙
	HIGH_NUT, //高坚果
	SQUASH, //窝瓜
	CHERRY, //樱桃炸弹
	GARLIC, //大蒜
	PUMPKIN //南瓜头
};

//僵尸种类
#define ZOMBIE_KIND_NUM 7
enum class ZOMBIE {
	ORDINARY, //普通僵尸
	BARRICADE, //路障僵尸
	BUCKETHEAD, //铁桶僵尸
	NEWSPAPER,//读报僵尸
	POLE_VAULTING, //撑杆僵尸
	CLOWN, //小丑僵尸
	THROW //透视僵尸
};

//子弹种类
enum class BULLET {
	NORMAL,
	ICE_BULLET,
	BASKETBALL
};

// 配置
#define COL 8 //行
#define ROW 5 //列
#define ROW_HIGH 6 //行高
#define COL_WIDTH 12 //列宽
#define TOP_HIGH 4 //顶部栏高度
#define BOTTOM_HIGH (2 + 2 * ((PLANT_KIND_NUM + 3) / 4)) //底部栏高度
#define WINDOWS_HIGH (ROW * (ROW_HIGH + 1) + TOP_HIGH + BOTTOM_HIGH + 1) //窗口高度
#define WINDOWS_WIDTH (COL * (COL_WIDTH + 1) + 2) //窗口宽度
#define MESSAGE_LINE 3 //消息在第几行显示
#define FRAME_WIDTH 24 //菜单提示框的宽度
#define FRAME_HIGH 5 //菜单提示框的高度

#define SLEEP_TIME 20 //每次循环等待时间，ms
#define COLOR_TIME 15 //颜色闪烁时间
#define NEW_ZOMBIE_X (WINDOWS_WIDTH - COL_WIDTH) //新僵尸的横坐标
#define SUNLIGHT_ADD_NUM 25 //自然阳光每次增加数量

#ifdef DEBUG
	#define FIRST_ZOMBIE_TIME 20 //首次出现僵尸的时间
	#define SUNLIGHT_ADD_TIME 100 //自然阳光增加所需时间
#else
	#define FIRST_ZOMBIE_TIME 1200 //首次出现僵尸的时间
	#define SUNLIGHT_ADD_TIME 1500 //自然阳光增加所需时间
#endif

// 颜色
#define BLACK 0x0
#define DARK_BLUE 0x1
#define DARK_GREEN 0x2
#define DARK_CYAN 0x3
#define DARK_RED 0x4
#define DARK_PURPLE 0x5
#define DARK_YELLOW 0x6
#define DARK_WHITE 0x7
#define GREY 0x8
#define BLUE 0x9
#define GREEN 0xa
#define CYAN 0xb
#define RED 0xc
#define PURPLE 0xd
#define YELLOW 0xe
#define WHITE 0xf

// 按键
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ENTER 13
#define ESC 27
#define BACKSPACE 8
#define NUM0 48
#define NUM1 (NUM0+1)
#define NUM2 (NUM0+2)
#define NUM3 (NUM0+3)
#define NUM4 (NUM0+4)
#define NUM5 (NUM0+5)
#define NUM6 (NUM0+6)
#define NUM7 (NUM0+7)
#define NUM8 (NUM0+8)
#define NUM9 (NUM0+9)
#define KB_a 97
#define KB_b (KB_a+1)
#define KB_A 65
#define KB_B (KB_A+1)

// 等级
#define LEVEL_1_SCORE 100
#define LEVEL_2_SCORE 250
#define LEVEL_3_SCORE 500
#define LEVEL_4_SCORE 850
#define LEVEL_5_SCORE 1300
#define LEVEL_6_SCORE 1750
#define LEVEL_7_SCORE 2200

//位置
struct Pos
{
	int row;
	int col;
	Pos(int r, int c) { row = r; col = c; }
};
struct Pos_less
{
	bool operator()(Pos x1, Pos x2) const
	{
		return (x1.row < x2.row) || (x1.row == x2.row && x1.col < x2.col);
	}
};