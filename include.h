#ifndef __HEAD_FILE__
#define __HEAD_FILE__


//各模块共用的库
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <random>


//头文件
#include "config.h" //宏定义配置信息
#include "Console.h" // 控制台状态
#include "Display.h" // UI模块
#include "Plant.h" //植物模块
#include "Bullet.h" //子弹模块
#include "Zombie.h" //僵尸模块
#include "Shop.h" //商店模块
#include "Menu.h" //主菜单


//全局变量，在main.cpp中定义
extern int score; //得分
extern int level; //等级
extern int sunlight; // 阳光数（随时间随机增加，种植向日葵可以加快增加速度）
extern int alive; // 游戏是否存活
extern PlantList plist; // 所有的植物
extern BulletList blist; // 所有的子弹
extern ZombieList zlist; // 所有的僵尸
extern Shop shop; //商店

#endif