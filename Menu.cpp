#include "include.h"
#include <conio.h>

extern bool Game();

const char* _MENU_NAME[] = { "开始游戏", "查看帮助", "退出游戏" };
int Menu::selector = 0;
int Menu::lines = sizeof(_MENU_NAME) / sizeof(_MENU_NAME[0]);

Menu::Menu() {}

Menu::~Menu() {}

void Menu::change_selector(int key)
{
	switch (key)
	{
	case UP: case LEFT:
		selector += lines - 1;
		break;
	case DOWN: case RIGHT:
		selector++;
		break;
	default:
		break;
	}
	selector %= lines;
}

int Menu::choose()
{
	switch (selector)
	{
	case 0:
		while (Game());
		return 1;
	case 1:
		showHelp();
		while (_getch() != ENTER);
		fixFrame();
		return 1;
	case 2:
	{
		showExit();
		int key = _getch();
		while (key != ENTER && key != ESC) key = _getch();
		fixFrame();
		if (key == ENTER)
			return 0;
		else
			return 1; 
	}
	default:
		return 1;
	}
}
