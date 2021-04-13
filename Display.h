#pragma once
#include "Plant.h"
#include "Bullet.h"
#include "Zombie.h"

//显示地图
void showMap();
//显示状态信息
void showInfo();
//显示提示信息
void showMessage(const char* message);
//显示植物
void showPlant(const Plant& plant);
void fixPlant(const Plant& plant);
//显示子弹
void showBullet(const Bullet& blt);
void fixBullet(const Bullet& blt);
//显示僵尸
void showZombie(const Zombie& zombie);
void fixZombie(const Zombie& zombie);
//显示商店
void showShop();
void fixShop();