#pragma once
#include <vector>

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
public:
	Bullet(int x, int y, int speed, int atk, int color);
	// �ƶ��������ӵ��Ƿ�������ײ�����˻��ƶ�����Ļ��������
	virtual bool move();
	// ��ʾ�ӵ�����Ԫ��������UIģ�鶨��
	friend void showBullet(const Bullet& blt);
	friend void fixBullet(const Bullet& blt);
};

class BulletList
{
private:
	std::vector<Bullet> bullet_list;
public:
	BulletList();
	// ����ӵ�
	void addBullet(Bullet blt);
	// �ӵ��ƶ�
	void bulletOperate();
};