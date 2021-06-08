#include "UI_Game.h"
#include <windows.h>
#include <conio.h>
#include <time.h>

#ifdef DEBUG
int UI_Game::score = 2200; //得分
int UI_Game::level = 7; //等级（根据得分增加）
int UI_Game::sunlight = 5000; // 阳光数，初始50
int UI_Game::alive = 1; // 游戏是否存活
#else
int UI_Game::score = 0; //得分
int UI_Game::level = 1; //等级（根据得分增加）
int UI_Game::sunlight = 50; // 阳光数，初始50
int UI_Game::alive = 1; // 游戏是否存活
#endif // DEBUG
int UI_Game::sunlight_count = SUNLIGHT_ADD_TIME * 2 / 3;
int UI_Game::pause = 0;
PlantList UI_Game::plist = PlantList();
BulletList UI_Game::blist = BulletList();
ZombieList UI_Game::zlist = ZombieList();
Shop UI_Game::shop = Shop();

void UI_Game::init()
{
	shop.reinit(1);
	plist.reinit();
	blist.reinit();
	zlist.reinit();
	alive = 1;
	sunlight_count = SUNLIGHT_ADD_TIME * 2 / 3;
#ifdef DEBUG
	score = 2200;
	level = 7;
	sunlight = 5000;
#else
	score = 0;
	level = 1;
	sunlight = 50;
#endif // DEBUG
}

UI_Game::UI_Game(QWidget* parent): QWidget(parent)
{
	init();
}

void UI_Game::Start()
{
	init();
}

void UI_Game::addScore(int x)
{
	UI_Game::score += x;
}

void UI_Game::levelUp()
{
	if (UI_Game::score < LEVEL_1_SCORE)
		return;
	else if (UI_Game::score < LEVEL_2_SCORE)
	{
		if (UI_Game::level == 1)
		{
			//showMessage("等级提升到二级！");
			UI_Game::level = 2;
		}
	}
	else if (UI_Game::score < LEVEL_3_SCORE)
	{
		if (UI_Game::level == 2)
		{
			//showMessage("等级提升到三级！");
			UI_Game::level = 3;
		}
	}
	else if (UI_Game::score < LEVEL_4_SCORE)
	{
		if (UI_Game::level == 3)
		{
			//showMessage("等级提升到四级！");
			UI_Game::level = 4;
		}
	}
	else if (UI_Game::score < LEVEL_5_SCORE)
	{
		if (UI_Game::level == 4)
		{
			//showMessage("等级提升到五级！");
			UI_Game::level = 5;
		}
	}
	else if (UI_Game::score < LEVEL_6_SCORE)
	{
		if (UI_Game::level == 5)
		{
			//showMessage("等级提升到六级！");
			UI_Game::level = 6;
		}
	}
	else if (UI_Game::score < LEVEL_7_SCORE)
	{
		if (UI_Game::level == 6)
		{
			//showMessage("等级提升到七级！");
			UI_Game::level = 7;
		}
	}
}

void UI_Game::addSunlight()
{
	if (UI_Game::sunlight_count == SUNLIGHT_ADD_TIME)
	{
		UI_Game::sunlight += SUNLIGHT_ADD_NUM;
		UI_Game::sunlight_count = rand() % 1000 - 500; // 以 SUNLIGHT_ADD_TIME 为中心前后一定范围内随机时间
	}
	else
	{
		UI_Game::sunlight_count++;
	}
}

int UI_Game::getSunlight()
{
	return sunlight;
}

void UI_Game::useSunlight(int x)
{
	sunlight -= x;
}

void UI_Game::addSunlight(int x)
{
	sunlight += x;
}

void UI_Game::Quit()
{
	init();
}

void UI_Game::Pause()
{
	pause = 1;
}

void UI_Game::Continue()
{
	pause = 0;
}