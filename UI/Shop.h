#pragma once
#include "Plant.h"
#include <qobject.h>
#include <qpushbutton.h>
#include <QMouseEvent>

extern int _WAIT[]; // �̵���ȴ
class UI_Menu;

class PlantSelector
{
private:
	int pid;
public:
	PlantSelector();
	~PlantSelector();
	void reinit();
	void move(int direction);
	void setPlant(int pid);
	int getPlant() const;
};

class MapSelector: public QWidget
{
	Q_OBJECT
private:
	Pos pos;
public:
	MapSelector(QWidget* parent);
	~MapSelector();
	void reinit();
	void move(int direction);
	Pos getPos() const;
	//void contextMenuEvent(QContextMenuEvent* event)override;
	//������¼�
	void mousePressEvent(QMouseEvent* event);
	//����ƶ��¼�
	void mouseMoveEvent(QMouseEvent* event);
	//����ͷ��¼�
	void mouseReleaseEvent(QMouseEvent* event);
	void show();
	void hide();
signals:
	void unchoose();
signals:
	void changePlace(QPoint);
signals:
	void planted();
};

class Shop : public QWidget
{
	Q_OBJECT
private:
	PlantSelector ps;
	MapSelector ms;
	int status; // 0ѡ��ֲ�1ѡ���ͼλ�ã�2����ֲ���ͻ
	int* wait_time;
	QWidget* seedbank;
	QPushButton* seedpackets[11];
	QLabel* waiting_shadows[11];
	QLabel* valid_shawods[11];
	QLabel* select_shawods[11];
	QColor* color[11];
	QLabel* sunlight;
	QLabel* numbers[4];
	QLabel* tmp_plant;
	UI_Menu* menu;
	int buyPlant(int sure);
public:
	Shop(QWidget* parent = NULL, UI_Menu* menu = NULL);
	~Shop();
	void reinit(int regame);
	// ѡ��ֲ��
	void choosePlant();
	// ���в���
	//void shopOperate(int key);
	// ��ȴ
	void wait();
	//��ʾ�̵���Ϣ
	void show();
	void hide();
	void show_numbers(int number);

public slots:
	// ѡ��ֲ��
	void choosePlant(int pid);
	// ȡ��ѡ��ֲ��
	void unchoosePlant();
	void buyPlant();
	void changePlace(QPoint p);
};

