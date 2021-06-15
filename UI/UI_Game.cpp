#include "UI_Game.h"
#include "UI_Menu.h"
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <qmultimedia.h>

#ifdef DEBUG
int UI_Game::sunlight = 5432; // 阳光数，初始50
#else
int UI_Game::sunlight = 50; // 阳光数，初始50
#endif // DEBUG
int UI_Game::alive = 1; // 游戏是否存活
int UI_Game::score = 0; //得分
int UI_Game::level = 1; //等级（根据得分增加）
int UI_Game::sunlight_count = SUNLIGHT_ADD_TIME * 2 / 3;
int UI_Game::pause = 0;
QTimer* UI_Game::timer = NULL;
PlantList UI_Game::plist = PlantList();
BulletList UI_Game::blist = BulletList();
ZombieList UI_Game::zlist = ZombieList();
Background* UI_Game::bg = NULL;
Shop* UI_Game::shop = NULL;
UI_Menu* UI_Game::menu = NULL;

void UI_Game::init()
{
	shop->reinit(1);
	plist.reinit();
	blist.reinit();
	zlist.reinit();
}

void UI_Game::loop()
{
	plist.plantsOperate();
	blist.bulletOperate();
	zlist.zombieOperate();
	shop->wait();
	menu->show_numbers(getScore());
	levelUp();
	addSunlight();
	if (UI_Game::alive == 0)
	{
		emit gameover();
		Pause();
	}
}

UI_Game::UI_Game(QWidget* parent): QWidget(parent)
{
	init();
	UI_Game::menu = (UI_Menu*)parent;
	UI_Game::timer = new QTimer(this);
	UI_Game::timer->setInterval(SLEEP_TIME);
	connect(UI_Game::timer, SIGNAL(timeout()), this, SLOT(loop()));
}

void UI_Game::Start()
{
	//init();
	qDebug() << "Game Started!";
	shop->show();
	UI_Game::timer->start();
#ifdef DEBUG
	UI_Game::sunlight = 5432; // 阳光数，初始50
#else
	UI_Game::sunlight = 50; // 阳光数，初始50
#endif // DEBUG
	UI_Game::alive = 1;
	UI_Game::score = 0;
	UI_Game::level = 1;
	UI_Game::sunlight_count = SUNLIGHT_ADD_TIME * 2 / 3;
	UI_Game::pause = 0;
}

void UI_Game::Quit()
{
	qDebug() << "Game Quited!";
	shop->hide();
	init();
}

void UI_Game::Pause()
{
	qDebug() << "Game Paused!";
	timer->stop();
	shop->hide();
	pause = 1;
}

void UI_Game::Continue()
{
	qDebug() << "Game Continuing!";
	timer->start();
	shop->show();
	pause = 0;
}

void UI_Game::addScore(int x)
{
	UI_Game::score += x;
}

int UI_Game::getScore()
{
	return score;
}

void UI_Game::levelUp()
{
	int flag = 0;
	if (UI_Game::score < LEVEL_1_SCORE)
		return;
	else if (UI_Game::score < LEVEL_2_SCORE)
	{
		if (UI_Game::level == 1)
		{
			UI_Game::level = 2;
			flag = 1;
		}
	}
	else if (UI_Game::score < LEVEL_3_SCORE)
	{
		if (UI_Game::level == 2)
		{
			UI_Game::level = 3;
			flag = 1;
		}
	}
	else if (UI_Game::score < LEVEL_4_SCORE)
	{
		if (UI_Game::level == 3)
		{
			UI_Game::level = 4;
			flag = 1;
		}
	}
	else if (UI_Game::score < LEVEL_5_SCORE)
	{
		if (UI_Game::level == 4)
		{
			UI_Game::level = 5;
			flag = 1;
		}
	}
	else if (UI_Game::score < LEVEL_6_SCORE)
	{
		if (UI_Game::level == 5)
		{
			UI_Game::level = 6;
			flag = 1;
		}
	}
	else if (UI_Game::score < LEVEL_7_SCORE)
	{
		if (UI_Game::level == 6)
		{
			UI_Game::level = 7;
			flag = 1;
		}
	}
	if(flag)
	{
		QMediaPlayer* music = new QMediaPlayer(UI_Game::bg);
		music->setMedia(QUrl::fromLocalFile("Resource/sounds/level_up.mp3"));
		music->setVolume(40);
		music->play();
		menu->showMessage("Resource/images/interface/level_up.png");
		qDebug() << "Level Up to" << level;
	}
}

void UI_Game::addSunlight()
{
	if (UI_Game::sunlight_count == SUNLIGHT_ADD_TIME)
	{
		printf("Create sunlight %d\n", SUNLIGHT_ADD_NUM);
		UI_Game::sunlight += SUNLIGHT_ADD_NUM;
		UI_Game::sunlight_count = rand() % 1000 - 500; // 以 SUNLIGHT_ADD_TIME 为中心前后一定范围内随机时间
		shop->show_numbers(sunlight);
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
	printf("Use sunlight %d\n", x);
	sunlight -= x;
	shop->show_numbers(sunlight);
}

void UI_Game::addSunlight(int x)
{
	printf("Add sunlight %d\n", x);
	sunlight += x;
	shop->show_numbers(sunlight);
}