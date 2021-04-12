#include <iostream>
#include <windows.h>
#include "include.h"
#include "config.h"

int score = 140; //�÷�
int level = 1; //�ȼ������ݵ÷����ӣ�
int sunlight = 0; // ����������ʱ��������ӣ���ֲ���տ����Լӿ������ٶȣ�
int alive = 1; // ��Ϸ�Ƿ���

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
	showMessage("��ӭ����ֲ���ս��ʬ�޾�ģʽ��");
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
			showMessage("�ȼ�������������");
			level = 2;
		}
	}
	//else if (score < LEVEL_3_SCORE)
	//{
	//	if (level == 2)
	//	{
	//		showMessage("�ȼ�������������");
	//		level = 3;
	//	}
	//}
}