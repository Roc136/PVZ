#pragma once
#include "config.h"
#include <map>

class Plant
{
protected:
	PLANT PLANT_ID; //植物id，表示种类，枚举类型
	int FULL_HP; //植物满血血量
	int ATK; //攻击力
	int AS; //攻速
	int COLOR; //植物显示颜色
	int current_hp; //植物当前血量
	bool valid; //是否存活
	Pos pos; //植物位置
	int status_count; //攻击状态计数，达到等待时间后攻击
	int color_count; //颜色变化计数
public:
	//构造函数，提供植物类型和坐标
	Plant(PLANT pid, int x, int y);
	//被吃，返回存活状态
	bool beEaten(int atk);
	//获取植物坐标
	Pos getPos() const;
	//获取植物存活状态
	bool isValid() const;
	//攻击，纯虚函数，在具体的植物类中定义
	virtual void hit() = 0;
	//显示植物，友元函数，在UI模块定义
	friend void showPlant(const Plant& plant);
	friend void fixPlant(const Plant& plant);
};

class PlantList
{
private:
	std::map<Pos, Plant*, Pos_less> plant_list;
public:
	PlantList();
	// 添加植物，sure参数表示确定覆盖旧植物
	bool addPlant(Plant* plant, bool sure = 0);
	// 遍历每个植物做一次 hit 函数
	void plantsOperate();
	Plant* getPlant(int r, int c);
};

class Sunflower : public Plant
{
public:
	// 构造函数，传递行列号
	Sunflower(int r, int c);
	// 向日葵用攻击函数作为产生向日葵的函数
	void hit();
};

class PeaShooter : public Plant
{
public:
	// 构造函数，传递行列号
	PeaShooter(int r, int c);
	// 攻击函数
	void hit();
};