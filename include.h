#ifndef __HEAD_FILE__
#define __HEAD_FILE__


//��ģ�鹲�õĿ�
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <random>


//ͷ�ļ�
#include "config.h" //�궨��������Ϣ
#include "Console.h" // ����̨״̬
#include "Display.h" // UIģ��
#include "Plant.h" //ֲ��ģ��
#include "Bullet.h" //�ӵ�ģ��
#include "Zombie.h" //��ʬģ��
#include "Shop.h" //�̵�ģ��
#include "Menu.h" //���˵�


//ȫ�ֱ�������main.cpp�ж���
extern int score; //�÷�
extern int level; //�ȼ�
extern int sunlight; // ����������ʱ��������ӣ���ֲ���տ����Լӿ������ٶȣ�
extern int alive; // ��Ϸ�Ƿ���
extern PlantList plist; // ���е�ֲ��
extern BulletList blist; // ���е��ӵ�
extern ZombieList zlist; // ���еĽ�ʬ
extern Shop shop; //�̵�

#endif