#pragma once

class Menu
{
	static int selector; //当前选择项
	static int lines; // 菜单行数
public:
	Menu();
	~Menu();
	// 修改选择子
	static void change_selector(int key);
	// 选定某项
	static int choose();
	// 友元，显示菜单
	friend void showMenu();
	friend void showHelp();
	friend void showExit();
};
