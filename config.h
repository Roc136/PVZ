#pragma once

//��
#define COL 8 //��
#define ROW 5 //��
#define ROW_HIGH 5 //�и�
#define COL_WIDTH 10 //�п�
#define TOP_HIGH 4 //�������߶�
#define BOTTOM_HIGH 6 //�ײ����߶�
#define WINDOWS_HIGH (ROW * (ROW + 1) + TOP_HIGH + BOTTOM_HIGH + 1) //���ڸ߶�
#define WINDOWS_WIDTH 90 //���ڿ��
#define MESSAGE_LINE 3 //��Ϣ�ڵڼ�����ʾ


#define SLEEP_TIME 10 //ÿ��ѭ���ȴ�ʱ�䣬ms
#define COLOR_TIME 15 //��ɫ��˸ʱ��

#define NEW_ZOMBIE_X 78 //�½�ʬ�ĺ�����
#define SUNLIGHT_ADD_TIME 1500 //��Ȼ������������ʱ��
#define SUNLIGHT_ADD_NUM 25 //��Ȼ����ÿ����������

#define BLACK 0x0
#define DARK_BULE 0x1
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

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ENTER 13
#define ESC 27
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

#define LEVEL_1_SCORE 100
#define LEVEL_2_SCORE 250
#define LEVEL_3_SCORE 600


#define PLANT_KIND_NUM 5
#define ZOMBIE_KIND_NUM 3
//ֲ������
enum class PLANT { SUNFLOWER, PEA_SHOOTER, DOUBLE_SHOOTER, NUT, POTATO, ICE_SHOOTER };
//��ʬ����
enum class ZOMBIE { ORDINARY, BARRICADE, BUCKETHEAD };

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