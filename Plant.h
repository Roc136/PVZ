#pragma once
#include "config.h"
#include <map>

class Plant
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
public:
	//���캯�����ṩֲ�����ͺ�����
	Plant(PLANT pid, int x, int y);
	//���ԣ����ش��״̬
	bool beEaten(int atk);
	//��ȡֲ������
	Pos getPos() const;
	//��ȡֲ����״̬
	bool isValid() const;
	//���������麯�����ھ����ֲ�����ж���
	virtual void hit() = 0;
	//��ʾֲ���Ԫ��������UIģ�鶨��
	friend void showPlant(const Plant& plant);
	friend void fixPlant(const Plant& plant);
};

class PlantList
{
private:
	std::map<Pos, Plant*, Pos_less> plant_list;
public:
	PlantList();
	// ���ֲ�sure������ʾȷ�����Ǿ�ֲ��
	bool addPlant(Plant* plant, bool sure = 0);
	// ����ÿ��ֲ����һ�� hit ����
	void plantsOperate();
	Plant* getPlant(int r, int c);
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