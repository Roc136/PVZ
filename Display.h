#pragma once
#include "Plant.h"
#include "Bullet.h"
#include "Zombie.h"

//��ʾ��ͼ
void showMap();
//��ʾ״̬��Ϣ
void showInfo();
//��ʾ��ʾ��Ϣ
void showMessage(const char* message);
//��ʾֲ��
void showPlant(const Plant& plant);
void fixPlant(const Plant& plant);
//��ʾ�ӵ�
void showBullet(const Bullet& blt);
void fixBullet(const Bullet& blt);
//��ʾ��ʬ
void showZombie(const Zombie& zombie);
void fixZombie(const Zombie& zombie);
//��ʾ�̵�
void showShop();
void fixShop();