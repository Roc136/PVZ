#include <windows.h>
#include <conio.h>
#include <time.h>
#include "include.h"
#include "config.h"

#ifdef DEBUG
	int score = 2200; //�÷�
	int level = 7; //�ȼ������ݵ÷����ӣ�
	int sunlight = 5000; // ����������ʼ50
	int alive = 1; // ��Ϸ�Ƿ���
#else
	int score = 0; //�÷�
	int level = 1; //�ȼ������ݵ÷����ӣ�
	int sunlight = 50; // ����������ʼ50
	int alive = 1; // ��Ϸ�Ƿ���
#endif // DEBUG

PlantList plist;
BulletList blist;
ZombieList zlist;
Shop shop;

bool Game();
void levelOperate();
static int sunlight_count = SUNLIGHT_ADD_TIME * 2 / 3; // ��һ������ʱ�����
void sunlightAdd();

int main()
{
	//while (1)
	//{
	//	if (_kbhit())
	//	{
	//		int key = _getch();
	//		if (key == 161 || key == 163)
	//			continue;
	//		printf("%d ", key);
	//	}
	//	//printf("a");
	//}
	initWindow();
	while (Game());
	while (1);
	return 0;
}

bool Game()
{
	int regame = 0;
	ULONGLONG last_time = GetTickCount64();
	showMap();
	showMessage("��ӭ����ֲ���ս��ʬ�޾�ģʽ��");
	while (alive)
	{
		while (GetTickCount64() - last_time < SLEEP_TIME);
		last_time = GetTickCount64();
		showInfo();
		if (_kbhit())
		{
			int key = _getch();
			if (key == 224)
				key = _getch();
			shop.shopOperate(key);
		}
		plist.plantsOperate();
		blist.bulletOperate();
		zlist.zombieOperate();
		shop.wait();
		showShop();
		levelOperate();
		sunlightAdd();
	}
	showMessage("Game Over! ��ʬ�Ե���������ӣ�");
	return regame;
}

void levelOperate()
{
	if (score < LEVEL_1_SCORE)
		return;
	else if (score < LEVEL_2_SCORE)
	{
		if (level == 1)
		{
			showMessage("�ȼ�������������");
			level = 2;
		}
	}
	else if (score < LEVEL_3_SCORE)
	{
		if (level == 2)
		{
			showMessage("�ȼ�������������");
			level = 3;
		}
	}
	else if (score < LEVEL_4_SCORE)
	{
		if (level == 3)
		{
			showMessage("�ȼ��������ļ���");
			level = 4;
		}
	}
	else if (score < LEVEL_5_SCORE)
	{
		if (level == 4)
		{
			showMessage("�ȼ��������弶��");
			level = 5;
		}
	}
	else if (score < LEVEL_6_SCORE)
	{
		if (level == 5)
		{
			showMessage("�ȼ�������������");
			level = 6;
		}
	}
	else if (score < LEVEL_7_SCORE)
	{
		if (level == 6)
		{
			showMessage("�ȼ��������߼���");
			level = 7;
		}
	}
}

void sunlightAdd()
{
	if (sunlight_count == SUNLIGHT_ADD_TIME)
	{
		sunlight += SUNLIGHT_ADD_NUM;
		sunlight_count = rand() % 1000 - 500; // �� SUNLIGHT_ADD_TIME Ϊ����ǰ��һ����Χ�����ʱ��
	}
	else
	{
		sunlight_count++;
	}
}

/*
TODO��
�����б����������
��ӽ�ʬ
*/