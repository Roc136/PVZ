#pragma once
#include "include.h"

extern int _WAIT[]; // �̵���ȴ

class PlantSelector
{
private:
	int pid;
public:
	PlantSelector();
	void move(int direction);
	void setPant(int pid);
	int getPlant() const;
};

class MapSelector
{
private:
	Pos pos;
public:
	MapSelector();
	void move(int direction);
	Pos getPos() const;
};

class Shop
{
private:
	PlantSelector ps;
	MapSelector ms;
	int status; // 0ѡ��ֲ�1ѡ���ͼλ�ã�2����ֲ���ͻ
	int* wait_time;
	int buyPlant(int sure);
public:
	Shop();
	// ѡ��ֲ��
	void choosePlant();
	// ȡ��ѡ��ֲ��
	void unchoosePlant();
	// ���в���
	void shopOperate(int key);
	// ��ȴ
	void wait();
	//��ʾ�̵���Ϣ
	friend void showShop();
	friend void fixShop();
};

