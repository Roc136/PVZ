#pragma once
#include "config.h"
#include <vector>

class Plant;

class Bullet
{
protected:
	int pos_x;
	int pos_y;
	int speed;
	int atk;
	bool valid;
	int color;
	int status_count;
	BULLET id;
public:
	Bullet(int x, int y, int speed, int atk, int color, BULLET id);
	// 移动，返回子弹是否消亡（撞击敌人或移动到屏幕外消亡）
	virtual bool move();
	BULLET getID() const;
	// 显示子弹，友元函数，在UI模块定义
	friend void showBullet(const Bullet& blt);
	friend void fixBullet(const Bullet& blt);
};

class BulletList
{
private:
	std::vector<Bullet*> bullet_list;
public:
	BulletList();
	// 添加子弹
	void addBullet(Bullet* blt);
	// 子弹移动
	void bulletOperate();
};

class IceBullet : public Bullet
{
private:
	int ice_time;
public:
	IceBullet(int x, int y, int speed, int atk, int color, BULLET id, int ice_time);
	bool move();
};

class Basketball :public Bullet
{
	int target_col;
public:
	Basketball(int x, int y, int speed, int atk, int color, BULLET id, int target_col);
	bool move();
};