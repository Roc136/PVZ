#pragma once
#include "config.h"
#include <map>

class Zombie
{
protected:
	ZOMBIE ZOMBIE_ID; //��ʬid����ʾ���࣬ö������
	int FULL_HP; //��ʬ��ѪѪ��
	int ATK; //������
	int AS; //����
	int MS; //����
	int COLOR; //��ʬ��ʾ��ɫ
	int ZOMBIE_SCORE; //��ʬ�����÷�
	int current_hp; //��ʬ��ǰѪ��
	bool valid; //�Ƿ���
	Pos pos; //��ʬλ��
	int status_count; //����״̬�������ﵽ�ȴ�ʱ��󹥻�
	int color_count; //��ɫ�仯����
public:
	//���캯�����ṩ��ʬ���ͺ����꣬���������ڵ�Ԫ�����Ͻ�
	Zombie(ZOMBIE zid, int x, int y);
	//���򣬷��ش��״̬
	virtual bool beHit(int atk);
	//��ȡ��ʬ����
	Pos getPos() const;
	//��ȡ��ʬ���״̬
	bool isValid() const;
	//�������麯��
	virtual void eat(Plant* plant);
	//�ƶ����麯��
	virtual void move();
	//��ʾ��ʬ����Ԫ��������UIģ�鶨��
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
	// ��ӽ�ʬ
	void addZombie(Zombie* zombie);
	// ����ÿ����ʬ��һ�� move ����
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