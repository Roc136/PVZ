#pragma once
#include "config.h"
#include <map>

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
	int status_count; //攻击状态计数，达到等待时间后攻击
	int color_count; //颜色变化计数
public:
	//构造函数，提供僵尸类型和坐标，坐标是所在单元的左上角
	Zombie(ZOMBIE zid, int x, int y);
	//被打，返回存活状态
	virtual bool beHit(int atk);
	//获取僵尸坐标
	Pos getPos() const;
	//获取僵尸存活状态
	bool isValid() const;
	//攻击，虚函数
	virtual void eat(Plant* plant);
	//移动，虚函数
	virtual void move();
	//显示僵尸，友元函数，在UI模块定义
	friend void showZombie(const Zombie& zombie);
	friend void fixZombie(const Zombie& zombie);
};

class ZombieList
{
private:
	std::map<Pos, Zombie*, Pos_less> zombie_list;
	int create_count;
	int create_time;
public:
	ZombieList();
	// 添加僵尸
	void addZombie(Zombie* zombie);
	// 遍历每个僵尸做一次 move 函数
	void zombieOperate();
	Zombie* getZombie(int x, int y);
};

class Barricede : public Zombie
{
public:
	Barricede(int x, int y);
	void eat(Plant* plant);
	void move();
};