#include "include.h"
#include <windows.h>
#include <time.h>

void initWindow()
{
	SetConsoleTitleA("Plant VS. Zombies! | version = 1.0  | @Roc"); //�޸Ĵ�������
	//���ô��ڴ�С���ɱ�
	HWND hWnd = GetConsoleWindow();
	RECT rc;
	GetWindowRect(hWnd, &rc);
	SetWindowLongPtr(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
	SetWindowPos(hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, NULL);
	//�޸Ĵ��ڴ�С
	system("mode con cols=90 lines=35");
	//���ع��
	setCursorHide(0);
	setColor();
	srand((unsigned)time(0));
}

void setCursorHide(bool visible)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = visible; //���ػ���ʾ����̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
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