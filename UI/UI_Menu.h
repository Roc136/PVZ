#pragma once
#include <qpushbutton.h>
#include "MyBaseButton.h"
#include "Display.h"
#include "Background.h"
#include "UI_Game.h"

class AskWid;
class UI_Menu :public QWidget
{
	Q_OBJECT

public:
	UI_Menu(QWidget* parent = 0);
private:
	Background* bg;
	MyBaseButton* start;
	MyBaseButton* help;
	MyBaseButton* exit;
	MyBaseButton* help_ret;
	MyBaseButton* game_ret;
	QMediaPlayer* music;
	AskWid* game_back_ask_wid;

public slots:
	void start_game();
	void show_help();
	void help_back();
	void game_back_ask();
	void game_back();
	void game_noback();
};

class AskWid: public QWidget
{
	Q_OBJECT
	UI_Menu* menu;
	QLabel* lable_topleft;
	QLabel* lable_topmiddle;
	QLabel* lable_topright;
	QLabel* lable_centerleft;
	QLabel* lable_centermiddle;
	QLabel* lable_centerright;
	QLabel* lable_bottomleft;
	QLabel* lable_bottommiddle;
	QLabel* lable_bottomright;
	MyBaseButton* back;
	MyBaseButton* noback;
	QLabel* info;
public:
	AskWid(QWidget* parent, UI_Menu* menu);
	void show();
	void hide();
};
