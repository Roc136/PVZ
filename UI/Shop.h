#pragma once
#include "include.h"

extern int _WAIT[]; // 商店冷却

class PlantSelector
{
private:
	int pid;
public:
	PlantSelector();
	~PlantSelector();
	void reinit();
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
	~MapSelector();
	void reinit();
	void move(int direction);
	Pos getPos() const;
};

class Shop
{
private:
	PlantSelector ps;
	MapSelector ms;
	int status; // 0选择植物，1选择地图位置，2购买植物冲突
	int* wait_time;
	int buyPlant(int sure);
public:
	Shop();
	~Shop();
	void reinit(int regame);
	// 选定植物
	void choosePlant();
	// 取消选定植物
	void unchoosePlant();
	// 进行操作
	void shopOperate(int key);
	// 冷却
	void wait();
	//显示商店信息
	friend void showShop();
	friend void fixShop();
};

