#include "include.h"
#include <windows.h>
#include <time.h>

void initWindow()
{
	SetConsoleTitleA("Plant VS. Zombies! | version = 1.0  | @Roc"); //修改窗口名字
	//设置窗口大小不可变
	HWND hWnd = GetConsoleWindow();
	RECT rc;
	GetWindowRect(hWnd, &rc);
	SetWindowLongPtr(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
	SetWindowPos(hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, NULL);
	//修改窗口大小
	system("mode con cols=90 lines=35");
	//隐藏光标
	setCursorHide(0);
	setColor();
	srand((unsigned)time(0));
}

void setCursorHide(bool visible)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = visible; //隐藏或显示控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
	return;
}

void setCursorPos(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}

void setColor(int font_color, int background_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), background_color << 4 | font_color);
}