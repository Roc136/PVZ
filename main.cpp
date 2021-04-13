#include <iostream>
#include <windows.h>
#include <conio.h>
#include "include.h"
#include "config.h"

int score = 0; //得分
int level = 1; //等级（根据得分增加）
int sunlight = 50; // 阳光数，初始50
int alive = 1; // 游戏是否存活

PlantList plist;
BulletList blist;
ZombieList zlist;
Shop shop;

bool Game();
void levelOperate();
static int sunlight_count = SUNLIGHT_ADD_TIME * 2 / 3; // 第一次所需时间较少
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
	showMessage("欢迎来到植物大战僵尸无尽模式！");
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
	showMessage("Game Over! 僵尸吃掉了你的脑子！");
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
			showMessage("等级提升到二级！");
			level = 2;
		}
	}
	else if (score < LEVEL_3_SCORE)
	{
		if (level == 2)
		{
			showMessage("等级提升到三级！");
			level = 3;
		}
	}
}

void sunlightAdd()
{
	if (sunlight_count == SUNLIGHT_ADD_TIME)
	{
		sunlight += SUNLIGHT_ADD_NUM;
		sunlight_count = rand() % 1000 - 500; // 以 SUNLIGHT_ADD_TIME 为中心前后一定范围内随机时间
	}
	else
	{
		sunlight_count++;
	}
}