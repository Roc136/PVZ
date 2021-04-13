#include <iostream>
#include <windows.h>
#include <conio.h>
#include "include.h"
#include "config.h"

int score = 0; //�÷�
int level = 1; //�ȼ������ݵ÷����ӣ�
int sunlight = 50; // ����������ʼ50
int alive = 1; // ��Ϸ�Ƿ���

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
	initWindow();
	while (Game());
	while (1)
	{
		int ch = _getch();
		std::cout << ch << " ";
	}
	while (1);
	return 0;
}

bool Game()
{
	int regame = 0;
	showMap();
	showMessage("��ӭ����ֲ���ս��ʬ�޾�ģʽ��");
	while (alive)
	{
		Sleep(SLEEP_TIME);
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