#pragma once
#include "include.h"

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
	bool buyPlant(int sure);
public:
	Shop() :status(0) {}
	// ѡ��ֲ��
	void choosePlant();
	// ȡ��ѡ��ֲ��
	void unchoosePlant();
	// ���в���
	void shopOperate(int key);
	//��ʾ�̵���Ϣ
	friend void showShop();
	friend void fixShop();
};

