#pragma once
#include "Plant.h"
#include <qobject.h>
#include <qpushbutton.h>
#include <QMouseEvent>

extern int _WAIT[]; // 商店冷却
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
	//鼠标点击事件
	void mousePressEvent(QMouseEvent* event);
	//鼠标移动事件
	void mouseMoveEvent(QMouseEvent* event);
	//鼠标释放事件
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
	int status; // 0选择植物，1选择地图位置，2购买植物冲突
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
	// 选定植物
	void choosePlant();
	// 进行操作
	//void shopOperate(int key);
	// 冷却
	void wait();
	//显示商店信息
	void show();
	void hide();
	void show_numbers(int number);

public slots:
	// 选定植物
	void choosePlant(int pid);
	// 取消选定植物
	void unchoosePlant();
	void buyPlant();
	void changePlace(QPoint p);
};

