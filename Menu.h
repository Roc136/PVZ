#pragma once

class Menu
{
	static int selector; //��ǰѡ����
	static int lines; // �˵�����
public:
	Menu();
	~Menu();
	// �޸�ѡ����
	static void change_selector(int key);
	// ѡ��ĳ��
	static int choose();
	// ��Ԫ����ʾ�˵�
	friend void showMenu();
	friend void showHelp();
	friend void showExit();
};
