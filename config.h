#pragma once

//��
#define COL 8 //��
#define ROW 5 //��
#define ROW_HIGH 5 //�и�
#define COL_WIDTH 10 //�п�
#define WINDOWS_HIGH 35 //���ڸ߶�
#define WINDOWS_WIDTH 90 //���ڿ��

#define SLEEP_TIME 10 //ÿ��ѭ���ȴ�ʱ�䣬ms
#define COLOR_TIME 15 //��ɫ��˸ʱ��

#define NEW_ZOMBIE_X 78 //�½�ʬ�ĺ�����

#define BLACK 0x0
#define DARK_BULE 0x1
#define DARK_GREEN 0x2
#define DARK_CYAN 0x3
#define DARK_RED 0x4
#define DARK_PURPLE 0x5
#define DARK_YELLOW 0x6
#define DARK_WHITE 0x7
#define GREY 0x8
#define BULE 0x9
#define GREEN 0xa
#define CYAN 0xb
#define RED 0xc
#define PURPLE 0xd
#define YELLOW 0xe
#define WHITE 0xf

#define LEVEL_1_SCORE 150
#define LEVEL_2_SCORE 400
#define LEVEL_3_SCORE 750


//ֲ������
enum class PLANT { SUNFLOWER, PEA_SHOOTER, DOUBLE_SHOOTER, ICE_SHOOTER, NUT };
//��ʬ����
enum class ZOMBIE { ORDINARY, BARRICADE };

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