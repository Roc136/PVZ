#pragma once
#include "config.h"
#include <map>
#include <qwidget.h>
#include <qmovie.h>
#include <qlabel.h>

class Plant: public QWidget
{
protected:
	PLANT PLANT_ID; //ֲ��id����ʾ���࣬ö������
	int FULL_HP; //ֲ����ѪѪ��
	int ATK; //������
	int AS; //����
	int COLOR; //ֲ����ʾ��ɫ
	int current_hp; //ֲ�ﵱǰѪ��
	bool valid; //�Ƿ���
	Pos pos; //ֲ��λ��
	int status_count; //����״̬�������ﵽ�ȴ�ʱ��󹥻�
	int color_count; //��ɫ�仯����
	int status;
	QMovie* movie;
	QLabel* processLabel;
public:
	//���캯�����ṩֲ�����ͺ�����
	Plant(PLANT pid, int x, int y);
	~Plant();
	//���ԣ����ش��״̬
	bool beEaten(int atk);
	//��ȡֲ������
	Pos getPos() const;
	//��ȡֲ��ID
	PLANT getID() const;
	//��ȡֲ����״̬
	bool isValid() const;
	//���������麯�����ھ����ֲ�����ж���
	virtual void hit() = 0;
	//��ʾֲ���Ԫ��������UIģ�鶨��
	//friend void showPlant(const Plant& plant);
	//friend void fixPlant(const Plant& plant);
	void changeMovie(const char* path, int width, int high);
};

class PlantList
{
private:
	std::map<Pos, Plant*, Pos_less> plant_list;
	std::map<Pos, Plant*, Pos_less> pumpkin_list;
public:
	PlantList();
	~PlantList();
	void reinit();
	// ���ֲ�sure������ʾȷ�����Ǿ�ֲ��
	bool addPlant(Plant* plant, bool sure = 0);
	// ����ÿ��ֲ����һ�� hit ����
	void plantsOperate();
	Plant* getPlant(int r, int c);
	Plant* getNormalPlant(int r, int c);
	Plant* getPumkin(int r, int c);
};

class Sunflower : public Plant
{
public:
	// ���캯�����������к�
	Sunflower(int r, int c);
	// ���տ��ù���������Ϊ�������տ��ĺ���
	void hit();
};

class PeaShooter : public Plant
{
public:
	// ���캯�����������к�
	PeaShooter(int r, int c);
	// ��������
	void hit();
};

class DoubleShooter : public Plant
{
private:
	int hit_count;
public:
	// ���캯�����������к�
	DoubleShooter(int r, int c);
	// ��������
	void hit();
};

class Nut : public Plant
{
public:
	Nut(int r, int c, PLANT id = PLANT::NUT);
	void hit();
};

class Potato : public Plant
{
	int is_ready;
	int ready_count;
public:
	Potato(int r, int c);
	void hit();
};

class IceShooter : public Plant
{
	int ice_time;
public:
	IceShooter(int r, int c);
	void hit();
};

class HighNut : public Nut
{
public:
	HighNut(int r, int c);
	void hit();
};

class Squash : public Plant
{
	int attack;
public:
	Squash(int r, int c);
	void hit();
};

class Cherry : public Plant
{
	int attack;
public:
	Cherry(int r, int c);
	void hit();
};

class Garlic : public Plant
{
public:
	Garlic(int r, int c);
	void hit();
};

class Pumpkin : public Plant
{
	QMovie* back_movie;
	QLabel* backLabel;
public:
	Pumpkin(int r, int c);
	~Pumpkin();
	void hit();
};