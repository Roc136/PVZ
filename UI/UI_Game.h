#pragma once
#include <qpushbutton.h>
#include <qtimer.h>
#include "Plant.h"
#include "Zombie.h"
#include "Shop.h"
#include "Bullet.h"
#include "Background.h"

class UI_Menu;

class UI_Game: public QWidget
{
	Q_OBJECT
private:
	static int score;
	static int sunlight;
	static int sunlight_count;
	static int pause;
	static QTimer* timer;
	static void init();
public:
	static PlantList plist;
	static BulletList blist;
	static ZombieList zlist;
	static int alive;
	static int level;
	static Background* bg;
	static Shop* shop;
	static UI_Menu* menu;

	UI_Game(QWidget* parent);
	static void Start();
	static void Pause();
	static void Continue();
	static void Quit();
	static void addScore(int x);
	static int getScore();
	static void levelUp();
	static void addSunlight();
	static int getSunlight();
	static void useSunlight(int x);
	static void addSunlight(int x);

signals:
	void gameover();

public slots:
	void loop();
};

