#include "include.h"

Bullet::Bullet(int x, int y, int speed, int atk, int color) : 
	pos_x(x), pos_y(y), speed(speed), atk(atk), color(color), valid(1),status_count(0) {}

bool Bullet::move()
{
	if (status_count >= speed)
	{
		int x = pos_x - 1;
		int y = pos_y - 3;
		pos_x++;
		Zombie* zombie = zlist.getZombie(x, y);
		if (zombie == NULL)
			zombie = zlist.getZombie(x + 1, y);
		if (zombie == NULL)
		{
			status_count = 0;
			if (pos_x >= WINDOWS_WIDTH - 1)
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

BulletList::BulletList() {}

void BulletList::addBullet(Bullet blt)
{
	bullet_list.push_back(blt);
}

void BulletList::bulletOperate()
{
	for (std::vector<Bullet>::iterator i = bullet_list.begin();
		i != bullet_list.end();)
	{
		if (!(*i).move())
		{
			fixBullet(*i);
			i = bullet_list.erase(i);
		}
		else
		{
			showBullet(*i);
			i++;
		}
	}
}
