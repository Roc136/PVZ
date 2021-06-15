#pragma once
#include "config.h"
#include <vector>
#include <qwidget.h>
#include <qlabel.h>
#include <qmultimedia.h>

class Plant;

class Bullet: public QWidget
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
	QMovie* movie;
	QLabel* processLabel;
public:
	Bullet(int x, int y, int speed, int atk, int color, BULLET id);
	// �ƶ��������ӵ��Ƿ�������ײ�����˻��ƶ�����Ļ��������
	virtual bool move();
	BULLET getID() const;
	// ��ʾ�ӵ�����Ԫ��������UIģ�鶨��
	//friend void showBullet(const Bullet& blt);
	//friend void fixBullet(const Bullet& blt);
	void fix();
	void show();
	void hide();
};

class BulletList
{
private:
	std::vector<Bullet*> bullet_list;
public:
	BulletList();
	~BulletList();
	void reinit();
	// ����ӵ�
	void addBullet(Bullet* blt);
	// �ӵ��ƶ�
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