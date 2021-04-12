#include <iostream>
#include <windows.h>
#include "include.h"
#include "config.h"

int score = 140; //得分
int level = 1; //等级（根据得分增加）
int sunlight = 0; // 阳光数（随时间随机增加，种植向日葵可以加快增加速度）
int alive = 1; // 游戏是否存活

PlantList plist;
BulletList blist;
ZombieList zlist;

bool Game();
void levelOperate();

int main()
{
	initWindow();
	while (Game());
	while (1);
	return 0;
}

void f()
{
	//PeaShooter* p1 = new PeaShooter(1, 1);
	Sunflower* p1 = new Sunflower(1, 1);
	PeaShooter* p2 = new PeaShooter(1, 0);
	plist.addPlant(p1);
	plist.addPlant(p2);
	Zombie* z = new Zombie(ZOMBIE::ORDINARY, 78, 10);
	//Barricede* z = new Barricede(78, 10);
	zlist.addZombie(z);
}

bool Game()
{
	f();
	showMap();
	showMessage("欢迎来到植物大战僵尸无尽模式！");
	while (alive)
	{
		Sleep(SLEEP_TIME);
		showInfo();
		plist.plantsOperate();
		zlist.zombieOperate();
		blist.bulletOperate();
		levelOperate();
	}
	showMessage("Game Over!");
	return 0;
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
	//else if (score < LEVEL_3_SCORE)
	//{
	//	if (level == 2)
	//	{
	//		showMessage("等级提升到三级！");
	//		level = 3;
	//	}
	//}
}