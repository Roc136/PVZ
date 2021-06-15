#pragma once
#include <qpushbutton.h>
#include "MyBaseButton.h"
#include "Display.h"
#include "Background.h"
#include "UI_Game.h"

class AskWid;
class overWid;
class ensureWid;
class UI_Menu :public QWidget
{
	Q_OBJECT

public:
	UI_Menu(QWidget* parent = 0);
	void show_numbers(int number);
	void setGame(UI_Game* game) { 
		this->game = game;
		connect(game, SIGNAL(gameover()), this, SLOT(gameoverWid()));
	}
	void showMessage(const char* path);
private:
	Background* bg;
	MyBaseButton* start;
	MyBaseButton* help;
	MyBaseButton* exit;
	MyBaseButton* help_ret;
	MyBaseButton* game_ret;
	QMediaPlayer* music;
	ensureWid* game_back_ask_wid;
	overWid* gameover_wid;
	QLabel* score;
	QLabel* numbers[4];
	QLabel* level;
	QLabel* level_number;
	UI_Game* game;
	QLabel* message;
	QTimer* timer;

public slots:
	void start_game();
	void show_help();
	void help_back();
	void game_back_ask();
	void game_back();
	void game_noback();
	void gameoverWid();
	void hideMessage();
};

class AskWid: public QWidget
{
	Q_OBJECT
protected:
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
	virtual void setConfig()=0;
	void show();
	void hide();
};

class ensureWid : public AskWid
{
public:
	ensureWid(QWidget* parent, UI_Menu* menu);
	void setConfig() override;
};

class overWid : public AskWid
{
public:
	overWid(QWidget* parent, UI_Menu* menu);
	void setConfig() override;
};