#pragma once
#include "config.h"
#include <vector>
#include "Plant.h"

class Zombie
{
protected:
	ZOMBIE ZOMBIE_ID; //僵尸id，表示种类，枚举类型
	int FULL_HP; //僵尸满血血量
	int ATK; //攻击力
	int AS; //攻速
	int MS; //移速
	int COLOR; //僵尸显示颜色
	int ZOMBIE_SCORE; //僵尸死亡得分
	int current_hp; //僵尸当前血量
	bool valid; //是否存活
	Pos pos; //僵尸位置
	int eat_count; //攻击状态计数，达到等待时间后攻击
	int move_count; //移动状态技术
	int color_count; //颜色变化计数
	int slowed;
	int old_ms;
	int old_as;
	int garlic;
public:
	//构造函数，提供僵尸类型和坐标，坐标是所在单元的左上角
	Zombie(ZOMBIE zid, int x, int y);
	//被打，返回存活状态
	virtual bool beHit(int atk);
	//被减速
	void beSlowed(int ice_time);
	//获取僵尸坐标
	Pos getPos() const;
	//获取僵尸存活状态
	bool isValid() const;
	//移动，虚函数
	void move();
	//需特殊处理的内容，虚函数
	virtual int special(int move_flag, int eat_flag, Plant*& plant);
	//显示僵尸，友元函数，在UI模块定义
	friend void showZombie(const Zombie& zombie);
	friend void fixZombie(const Zombie& zombie);
};

class ZombieList
{
private:
	std::vector<Zombie*> zombie_list;
	int create_count;
	int create_time;
public:
	ZombieList();
	~ZombieList();
	void reinit();
	// 添加僵尸
	void addZombie();
	// 遍历每个僵尸做一次 move 函数
	void zombieOperate();
	// 获取某一坐标的僵尸
	Zombie* getZombie(int x, int y);
	// 获取某一行所有僵尸
	std::vector<Zombie*> getZombie(int r);
};

class Barricede : public Zombie
{
public:
	Barricede(int x, int y);
	int special(int move_flag, int eat_flag, Plant*& plant);
};

class Buckethead : public Zombie
{
public:
	Buckethead(int x, int y);
	int special(int move_flag, int eat_flag, Plant*& plant);
};

class Newspaper : public Zombie
{
public:
	Newspaper(int x, int y);
	int special(int move_flag, int eat_flag, Plant*& plant);
};

class PoleVaulting : public Zombie
{
	int rod;
	int jump;
public:
	PoleVaulting(int x, int y);
	int special(int move_flag, int eat_flag, Plant*& plant);
};

class Clown : public Zombie
{
	int boom_time;
	int boom_color;
	int boom_atk;
public:
	Clown(int x, int y);
	int special(int move_flag, int eat_flag, Plant*& plant);
};

class Throw : public Zombie
{
	int basketball;
	int basketball_atk;
	int basketball_as;
	int throw_count;
public:
	Throw(int x, int y);
	int special(int move_flag, int eat_flag, Plant*& plant);
};