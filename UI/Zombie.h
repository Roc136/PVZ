#pragma once
#include "config.h"
#include <vector>
#include "Plant.h"
#include "qmultimedia.h"

class Zombie: public QWidget
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
	int eat_count; //����״̬�������ﵽ�ȴ�ʱ��󹥻�
	int move_count; //�ƶ�״̬����
	int color_count; //��ɫ�仯����
	int status; // ״̬��0-�ƶ���1-������2-����������Ͷ����
	int slowed;
	int old_ms;
	int old_as;
	int garlic; 
	QMovie* movie;
	QLabel* processLabel;
public:
	//���캯�����ṩ��ʬ���ͺ����꣬���������ڵ�Ԫ�����Ͻ�
	Zombie(ZOMBIE zid, int x, int y);
	~Zombie();
	//���򣬷��ش��״̬
	virtual bool beHit(int atk);
	//������
	void beSlowed(int ice_time);
	//��ȡ��ʬ����
	Pos getPos() const;
	//��ȡ��ʬ���״̬
	bool isValid() const;
	//�ƶ����麯��
	void move();
	//�����⴦������ݣ��麯��
	virtual int special(int move_flag, int eat_flag, Plant*& plant);
	//��ʾ��ʬ����Ԫ��������UIģ�鶨��
	//friend void showZombie(const Zombie& zombie);
	//friend void fixZombie(const Zombie& zombie);
	void fix();
	void show();
	void hide();
	void changeMovie(const char* path);
};

class ZombieList
{
private:
	std::vector<Zombie*> zombie_list;
	int create_count;
	int create_time;
	int flag = 1;
public:
	ZombieList();
	~ZombieList();
	void reinit();
	// ��ӽ�ʬ
	void addZombie();
	// ����ÿ����ʬ��һ�� move ����
	void zombieOperate();
	// ��ȡĳһ����Ľ�ʬ
	Zombie* getZombie(int x, int y);
	// ��ȡĳһ�����н�ʬ
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