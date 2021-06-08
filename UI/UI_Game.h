#pragma once
#include <qpushbutton.h>
#include "Plant.h"
#include "Zombie.h"
#include "Shop.h"
#include "Bullet.h"

class UI_Game: public QWidget
{
	Q_OBJECT
private:
	static int score;
	static int sunlight;
	static int sunlight_count;
	static int pause;
	static void init();
public:
	static PlantList plist;
	static BulletList blist;
	static ZombieList zlist;
	static Shop shop;
	static int alive;
	static int level;

	UI_Game(QWidget* parent);
	static void Start();
	static void addScore(int x);
	static void levelUp();
	static void addSunlight();
	static int getSunlight();
	static void useSunlight(int x);
	static void addSunlight(int x);

	static void Pause();
	static void Continue();
	static void Quit();
};

