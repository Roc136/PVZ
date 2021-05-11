#pragma once

//��
//#define DEBUG

//ֲ������
#define PLANT_KIND_NUM 11
enum class PLANT {
	SUNFLOWER, //���տ�
	PEA_SHOOTER, //�㶹����
	DOUBLE_SHOOTER, //˫������
	ICE_SHOOTER, //��������
	POTATO, //������
	NUT, //���ǽ
	HIGH_NUT, //�߼��
	SQUASH, //�ѹ�
	CHERRY, //ӣ��ը��
	GARLIC, //����
	PUMPKIN //�Ϲ�ͷ
};

//��ʬ����
#define ZOMBIE_KIND_NUM 7
enum class ZOMBIE {
	ORDINARY, //��ͨ��ʬ
	BARRICADE, //·�Ͻ�ʬ
	BUCKETHEAD, //��Ͱ��ʬ
	NEWSPAPER,//������ʬ
	POLE_VAULTING, //�Ÿ˽�ʬ
	CLOWN, //С��ʬ
	THROW //͸�ӽ�ʬ
};

//�ӵ�����
enum class BULLET {
	NORMAL,
	ICE_BULLET,
	BASKETBALL
};

// ����
#define COL 8 //��
#define ROW 5 //��
#define ROW_HIGH 6 //�и�
#define COL_WIDTH 12 //�п�
#define TOP_HIGH 4 //�������߶�
#define BOTTOM_HIGH (2 + 2 * ((PLANT_KIND_NUM + 3) / 4)) //�ײ����߶�
#define WINDOWS_HIGH (ROW * (ROW_HIGH + 1) + TOP_HIGH + BOTTOM_HIGH + 1) //���ڸ߶�
#define WINDOWS_WIDTH (COL * (COL_WIDTH + 1) + 2) //���ڿ��
#define MESSAGE_LINE 3 //��Ϣ�ڵڼ�����ʾ
#define FRAME_WIDTH 24 //�˵���ʾ��Ŀ��
#define FRAME_HIGH 5 //�˵���ʾ��ĸ߶�

#define SLEEP_TIME 20 //ÿ��ѭ���ȴ�ʱ�䣬ms
#define COLOR_TIME 15 //��ɫ��˸ʱ��
#define NEW_ZOMBIE_X (WINDOWS_WIDTH - COL_WIDTH) //�½�ʬ�ĺ�����
#define SUNLIGHT_ADD_NUM 25 //��Ȼ����ÿ����������

#ifdef DEBUG
	#define FIRST_ZOMBIE_TIME 20 //�״γ��ֽ�ʬ��ʱ��
	#define SUNLIGHT_ADD_TIME 100 //��Ȼ������������ʱ��
#else
	#define FIRST_ZOMBIE_TIME 1200 //�״γ��ֽ�ʬ��ʱ��
	#define SUNLIGHT_ADD_TIME 1500 //��Ȼ������������ʱ��
#endif

// ��ɫ
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

// ����
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

// �ȼ�
#define LEVEL_1_SCORE 100
#define LEVEL_2_SCORE 250
#define LEVEL_3_SCORE 500
#define LEVEL_4_SCORE 850
#define LEVEL_5_SCORE 1300
#define LEVEL_6_SCORE 1750
#define LEVEL_7_SCORE 2200

//λ��
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