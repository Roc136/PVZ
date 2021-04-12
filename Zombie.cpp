#include "include.h"

static int _HP[] = { 120, 240 }; // 僵尸血量
static int _ATK[] = { 5, 5 }; // 僵尸攻击力
static int _AS[] = { 25, 25 }; // 僵尸攻击速度，用等待值显示，ms
static int _MS[] = { 50, 50 }; // 僵尸移动速度，用等待值显示，ms
static int _ZOMBIE_SCORE[] = { 10, 15 };
static int _ZOMBIE_COLOR[] = { WHITE, DARK_YELLOW }; // 僵尸颜色
static int _ZID[] = {
	//level - 5,
	//level - 4,
	//level - 4,
	//level - 3,
	//level - 3,
	//level - 3,
	level - 2,
	level - 2,
	level - 2,
	level - 2,
	level - 1,
	level - 1,
	level - 1,
	level - 1,
	level - 1,
}; // 随机产生僵尸种类，等级越高产生的僵尸种类难度越高

Zombie::Zombie(ZOMBIE zid, int x, int y) :
	ZOMBIE_ID(zid), pos(y, x), status_count(0), valid(1)
{
	FULL_HP = _HP[(int)zid];
	ATK = _ATK[(int)zid];
	AS = _AS[(int)zid];
	MS = _MS[(int)zid];
	COLOR = _ZOMBIE_COLOR[(int)zid];
	ZOMBIE_SCORE = _ZOMBIE_SCORE[(int)zid];
	current_hp = FULL_HP;
	color_count = 0;
}

bool Zombie::beHit(int atk)
{
	current_hp -= atk;
	color_count = 0;
	COLOR = RED;
	valid = (current_hp > 0);
	if (valid == 0)
		score += ZOMBIE_SCORE;
	return valid;
}

Pos Zombie::getPos() const
{
	return pos;
}

bool Zombie::isValid() const
{
	return valid;
}

void Zombie::eat(Plant* plant)
{
	if (status_count >= AS)
	{
		// 吃
		plant->beEaten(ATK);
		status_count = 0;
		color_count = 0;
		COLOR = GREY;
	}
	else
	{
		// 等待
		status_count++;
		color_count++;
		if (color_count == COLOR_TIME)
			COLOR = _ZOMBIE_COLOR[(int)ZOMBIE_ID];
	}
	return;
}

void Zombie::move()
{
	if (status_count >= MS)
	{
		// 移动
		pos.col--;
		if (pos.col == 0)
			alive = 0;
		status_count = 0;
	}
	else
	{
		// 等待
		status_count++;
		color_count++;
		if (color_count == COLOR_TIME)
			COLOR = _ZOMBIE_COLOR[(int)ZOMBIE_ID];
	}
	return;
}

ZombieList::ZombieList()
{
	create_count = 0;
	create_time = rand() % (1500 / level / level) + (1000 / level / level);
}

void ZombieList::addZombie(Zombie* zombie)
{
	Pos pos = zombie->getPos();
	zombie_list.insert(std::pair<Pos, Zombie*>(pos, zombie));
}

void ZombieList::zombieOperate()
{
	for (std::map<Pos, Zombie*>::iterator i = zombie_list.begin();
		i != zombie_list.end();)
	{
		if (i->second->isValid())
		{
			Pos pos = i->second->getPos();
			int r = (pos.row - 4) / (ROW_HIGH + 1);
			int c = pos.col / (COL_WIDTH + 1);
			Plant* p = plist.getPlant(r, c);
			//setCursorPos(20, 20);
			//std::cout << r << " " << c;
			if (p == NULL)
			{
				i->second->move();
			}
			else
				i->second->eat(p);
			showZombie(*(i->second));
			i++;
		}
		else
		{
			fixZombie(*(i->second));
			delete i->second;
			zombie_list.erase(i++);
		}
	}
	if (create_count >= create_time)
	{
		create_count = 0;
		create_time = rand() % (1500 / level / level) + (1000 / level / level);
		int zid_idx = rand() % (sizeof(_ZID) / sizeof(int));
		int zid = _ZID[zid_idx] > 0 ? _ZID[zid_idx] : 0;
		int r = rand() % ROW;
		int y = r * (ROW_HIGH + 1) + 4;
		switch (zid)
		{
		case (int)ZOMBIE::ORDINARY:
		{
			Zombie* z = new Zombie(ZOMBIE::ORDINARY, NEW_ZOMBIE_X, y);
			addZombie(z);
			break;
		}
		case (int)ZOMBIE::BARRICADE:
		{
			Barricede* b = new Barricede(NEW_ZOMBIE_X, y);
			addZombie(b);
			break;
		}
		default:
		{
			Zombie* z = new Zombie(ZOMBIE::ORDINARY, NEW_ZOMBIE_X, y);
			addZombie(z);
		}
		}
	}
	else
		create_count++;
}

Zombie* ZombieList::getZombie(int x, int y)
{
	Pos p(y, x);
	for (std::map<Pos, Zombie*>::iterator i = zombie_list.begin();
		i != zombie_list.end(); i++)
	{
		if ((i->second->getPos().col - x) <= 1 && i->second->getPos().row == y)
			return i->second;
	}
	return NULL;
}

Barricede::Barricede(int x, int y):Zombie(ZOMBIE::BARRICADE, x, y){}

void Barricede::eat(Plant* plant)
{
	if (status_count >= AS)
	{
		// 吃
		plant->beEaten(ATK);
		status_count = 0;
		color_count = 0;
		COLOR = GREY;
	}
	else
	{
		// 等待
		status_count++;
		color_count++;
		if (color_count == COLOR_TIME)
		{
			if (current_hp < FULL_HP / 2)
				COLOR = _ZOMBIE_COLOR[0];
			else
				COLOR = _ZOMBIE_COLOR[(int)ZOMBIE_ID];
		}
	}
	return;
}

void Barricede::move()
{
	if (status_count >= MS)
	{
		// 移动
		pos.col--;
		if (pos.col == 0)
			alive = 0;
		status_count = 0;
	}
	else
	{
		// 等待
		status_count++;
		color_count++;
		if (color_count == COLOR_TIME)
		{
			if (current_hp < FULL_HP / 2)
				COLOR = _ZOMBIE_COLOR[0];
			else
				COLOR = _ZOMBIE_COLOR[(int)ZOMBIE_ID];
		}
	}
	return;
}
