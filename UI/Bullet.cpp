#include "Bullet.h"
#include "Plant.h"
#include "Zombie.h"
#include "include.h"

const char* _BULLET_PATH[] = { "PB00", "PB10", "Basketball" };

Bullet::Bullet(int x, int y, int speed, int atk, int color, BULLET id) :
	pos_x(x), pos_y(y), speed(speed), atk(atk), color(color), id(id), valid(1),status_count(0), QWidget(UI_Game::bg)
{
	int x_ = LEFT_WIDTH + pos_x - 35;
	int y_ = pos_y - 20;
	setGeometry(x_, y_, 56, 34);
	setStyleSheet("background-image:url();");
	char movie_path[100] = "";
	sprintf(movie_path, "Resource/images/Plants/%s.gif", _BULLET_PATH[(int)id]);
	movie = new QMovie(movie_path);
	processLabel = new QLabel(this);
	processLabel->setMovie(movie);
	processLabel->setGeometry(0, 0, 56, 34);
	processLabel->setAttribute(Qt::WA_TranslucentBackground, true);
	processLabel->show();
	movie->start();
	raise();
	show();
}

bool Bullet::move()
{
	if (status_count >= speed)
	{
		int x = pos_x - 1;
		int y = pos_y - ROW_HIGH / 2;
		int i = 0;
		pos_x += 5;
		fix();
		Zombie* zombie = UI_Game::zlist.getZombie(x - 5, y);
		while (zombie == NULL && i < 6)
			zombie = UI_Game::zlist.getZombie(x + (i++) - 5, y);
		if (zombie == NULL)
		{
			status_count = 0;
			if (pos_x >= WINDOWS_WIDTH + 10)
				valid = 0;
		}
		else
		{
			zombie->beHit(atk);
			valid = 0;
		}
	}
	else
		status_count++;
	return valid;
}

void Bullet::fix()
{
	int x_ = LEFT_WIDTH + pos_x - 35;
	int y_ = pos_y - 20;
	setGeometry(x_, y_, 56, 34);
	hide();
	repaint();
	show();
}

void Bullet::show()
{
	QWidget::show();
	processLabel->show();
}

void Bullet::hide()
{
	QWidget::hide();
	processLabel->hide();
}

BULLET Bullet::getID() const
{
	return id;
}

void BulletList::reinit()
{
	for (auto i = bullet_list.begin(); i != bullet_list.end();)
	{
		delete (*i);
		i = bullet_list.erase(i);
	}
}

BulletList::BulletList() {}

BulletList::~BulletList()
{
	reinit();
}

void BulletList::addBullet(Bullet* blt)
{
	bullet_list.push_back(blt);
}

void BulletList::bulletOperate()
{
	for (std::vector<Bullet*>::iterator i = bullet_list.begin();
		i != bullet_list.end();)
	{
		if (!(*i)->move())
		{
			//fixBullet(**i);
			delete (*i);
			i = bullet_list.erase(i);
		}
		else
		{
			//showBullet(**i);
			i++;
		}
	}
}

IceBullet::IceBullet(int x, int y, int speed, int atk, int color, BULLET id, int ice_time) :
	Bullet(x, y, speed, atk, color, id), ice_time(ice_time)
{}

bool IceBullet::move()
{
	if (status_count >= speed)
	{
		int x = pos_x - 1;
		int y = pos_y - ROW_HIGH / 2;
		int i = 0;
		pos_x += 5;
		fix();
		Zombie* zombie = UI_Game::zlist.getZombie(x - 5, y);
		while (zombie == NULL && i < 6)
			zombie = UI_Game::zlist.getZombie(x + (i++) - 5, y);
		if (zombie == NULL)
		{
			status_count = 0;
			if (pos_x >= WINDOWS_WIDTH + 10)
				valid = 0;
		}
		else
		{
			zombie->beHit(atk);
			zombie->beSlowed(ice_time);
			valid = 0;
		}
	}
	else
		status_count++;
	return valid;
}

Basketball::Basketball(int x, int y, int speed, int atk, int color, BULLET id, int target_col) :
	Bullet(x, y, speed, atk, color, id), target_col(target_col)
{}

bool Basketball::move()
{
	if (status_count >= speed)
	{
		status_count = 0;
		pos_x -= 5;
		fix();
		if (pos_x <= 0)
			valid = 0;
		int r = (pos_y - 1- TOP_HIGH) / (ROW_HIGH + 1);
		int c = (pos_x + COL_WIDTH / 2) / (COL_WIDTH + 1);
		if (c == target_col)
		{
			Plant* p = UI_Game::plist.getPlant(r, c);
			if (p)
				p->beEaten(atk);
			valid = 0;
		}
	}
	else
		status_count++;
	return valid;
}
