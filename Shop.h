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
	int status; // 0选择植物，1选择地图位置，2购买植物冲突
	bool buyPlant(int sure);
public:
	Shop() :status(0) {}
	// 选定植物
	void choosePlant();
	// 取消选定植物
	void unchoosePlant();
	// 进行操作
	void shopOperate(int key);
	//显示商店信息
	friend void showShop();
	friend void fixShop();
};

