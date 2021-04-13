#include "include.h"

static int _HP[] = { 120, 240, 360 }; // 僵尸血量
static int _ATK[] = { 5, 5, 5 }; // 僵尸攻击力
static int _AS[] = { 25, 25, 25 }; // 僵尸攻击速度，用等待值显示，ms
static int _MS[] = { 25, 25, 25 }; // 僵尸移动速度，用等待值显示，ms
static int _ZOMBIE_SCORE[] = { 10, 15, 25 };
static int _ZOMBIE_COLOR[] = { WHITE, DARK_YELLOW, GREY }; // 僵尸颜色
const char* _ZOMBIE_NAME[] = { "普通僵尸", "路障僵尸", "铁桶僵尸" }; // 僵尸名字
static int _ZID[] = {
	//level - 5,
	//level - 4,
	//level - 4,
	level - 3,
	level - 3,
	level - 3,
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
	{
		fixZombie(*this);
		score += ZOMBIE_SCORE;
	}
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
	create_time = 1200; //首次出现僵尸的时间
}

void ZombieList::addZombie(Zombie* zombie)
{
	zombie_list.push_back(zombie);
}

void ZombieList::zombieOperate()
{
	for (std::vector<Zombie*>::iterator i = zombie_list.begin();
		i != zombie_list.end();)
	{
		if ((*i)->isValid())
		{
			Pos pos = (*i)->getPos();
			int r = (pos.row - 4) / (ROW_HIGH + 1);
			int c = pos.col / (COL_WIDTH + 1);
			Plant* p = plist.getPlant(r, c);
			//setCursorPos(20, 20);
			//std::cout << r << " " << c;
			if (p == NULL)
			{
				(*i)->move();
			}
			else
				(*i)->eat(p);
			showZombie(*(*i));
			i++;
		}
		else
		{
			delete (*i);
			i = zombie_list.erase(i);
		}
	}
	if (create_count >= create_time)
	{
		create_count = 0;
		if (create_time == 1000)
			create_time = 800;
		else if (create_time > 200)
			create_time = create_time - rand() % level;
		int zid_idx = rand() % (sizeof(_ZID) / sizeof(int));
		int zid = _ZID[zid_idx] >= 0 ? _ZID[zid_idx] : 0;
		int r = rand() % ROW;
		int y = r * (ROW_HIGH + 1) + 4;
		if (zlist.getZombie(NEW_ZOMBIE_X, y) || zlist.getZombie(NEW_ZOMBIE_X - 1, y) || zlist.getZombie(NEW_ZOMBIE_X - 2, y) || zlist.getZombie(r).size() > level * 1.3)
		{
			zid = -1; // 不产生僵尸
		}
		switch (zid)
		{
		case -1:
			break;
		case 0:
		{
			Zombie* z = new Zombie(ZOMBIE::ORDINARY, NEW_ZOMBIE_X, y);
			addZombie(z);
			break;
		}
		case 1:
		{
			Barricede* z = new Barricede(NEW_ZOMBIE_X, y);
			addZombie(z);
			break;
		}
		case 2:
		{
			Buckethead* z = new Buckethead(NEW_ZOMBIE_X, y);
			addZombie(z);
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
	for (std::vector<Zombie*>::iterator i = zombie_list.begin();
		i != zombie_list.end(); i++)
	{
		if (((*i)->getPos().col - x) == 0 && (*i)->getPos().row == y)
			return *i;
	}
	return NULL;
}

std::vector<Zombie*> ZombieList::getZombie(int r)
{
	int y = r * (ROW_HIGH + 1) + 4;
	std::vector<Zombie*> zombies;
	for (std::vector<Zombie*>::iterator i = zombie_list.begin();
		i != zombie_list.end(); i++)
	{
		if ((*i)->getPos().row == y)
			zombies.push_back(*i);
	}
	return zombies;
}

Barricede::Barricede(int x, int y) :Zombie(ZOMBIE::BARRICADE, x, y) {}

void Barricede::eat(Plant* plant)
{
	if (status_count >= AS)
	{
		// 吃
		plant->beEaten(ATK);
		status_count = 0;
		color_count = 0;
		COLOR = YELLOW;
	}
	else
	{
		// 等待
		status_count++;
		color_count++;
		if (color_count == COLOR_TIME)
		{
			if (current_hp < FULL_HP / 2)
				COLOR = WHITE;
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

Buckethead::Buckethead(int x, int y) :Zombie(ZOMBIE::BUCKETHEAD, x, y) {}

void Buckethead::eat(Plant* plant)
{
	if (status_count >= AS)
	{
		// 吃
		plant->beEaten(ATK);
		status_count = 0;
		color_count = 0;
		COLOR = YELLOW;
	}
	else
	{
		// 等待
		status_count++;
		color_count++;
		if (color_count == COLOR_TIME)
		{
			if (current_hp < FULL_HP * 2 / 3)
				COLOR = GREY;
			else if (current_hp < FULL_HP / 3)
				COLOR = WHITE;
			else
				COLOR = _ZOMBIE_COLOR[(int)ZOMBIE_ID];
		}
	}
	return;
}

void Buckethead::move()
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
			if (current_hp < FULL_HP / 3)
				COLOR = WHITE;
			else if (current_hp < FULL_HP * 2 / 3)
				COLOR = DARK_WHITE;
			else
				COLOR = _ZOMBIE_COLOR[(int)ZOMBIE_ID];
		}
	}
	return;
}
