#include "include.h"

static int _HP[] = { 100, 120, 120, 1000, 30, 120, 2000, 100, 100000, 160, 1000 }; // 植物血量
static int _ATK[] = { 25, 15, 15, 0, 1000, 20, 0, 1000, 1000, 0, 0 }; // 植物攻击力
static int _AS[] = { 1500, 50, 50, 0, 0, 50, 0, 20, 20, 0, 0 }; // 植物攻击速度，用等待值显示，ms
static int _PLANT_COLOR[] = { DARK_YELLOW, GREEN, GREEN, WHITE, WHITE, CYAN, WHITE, DARK_GREEN, RED, DARK_WHITE, YELLOW }; // 植物颜色
const char* _PLANT_NAME[] = { "向 日 葵", "豌豆射手", "双发射手", "坚 果 墙", "土 豆 雷", "寒冰射手", "高 坚 果", " 窝  瓜 ", "樱桃炸弹", " 大  蒜 ", "南 瓜 头" }; // 植物名字
int _COST[] = { 50, 100, 200, 50, 25, 175, 125, 50, 150, 50, 125 }; // 植物花费
#ifdef DEBUG
int _WAIT[] = { 25, 25, 25, 100, 100, 30, 150, 150, 250, 50, 150 }; // 商店冷却
#else
int _WAIT[] = { 250, 250, 250, 1000, 1000, 300, 1500, 1500, 2500, 500, 1500 }; // 商店冷却
#endif

Plant::Plant(PLANT pid, int r, int c) :
	PLANT_ID(pid), pos(r, c), status_count(0), valid(1)
{
	FULL_HP = _HP[(int)pid];
	ATK = _ATK[(int)pid];
	AS = _AS[(int)pid];
	COLOR = _PLANT_COLOR[(int)pid];
	current_hp = FULL_HP;
	color_count = 0;
}

bool Plant::beEaten(int atk)
{
	current_hp -= atk;
	valid = (current_hp > 0);
	return valid;
}

Pos Plant::getPos() const
{
	return pos;
}

PLANT Plant::getID() const
{
	return PLANT_ID;
}

bool Plant::isValid() const
{
	return valid;
}

PlantList::PlantList() {}

bool PlantList::addPlant(Plant* plant, bool sure)
{
	if (plant->getID() == PLANT::PUMPKIN)
	{
		std::map<Pos, Plant*>::iterator ip = pumpkin_list.find(plant->getPos());
		if (ip != pumpkin_list.end())
		{
			if (sure)
			{
				fixPlant(*pumpkin_list[plant->getPos()]);
				delete pumpkin_list[plant->getPos()];
				pumpkin_list[plant->getPos()] = plant;
				return true;
			}
			else
				return false;
		}
		else
		{
			pumpkin_list.insert(std::pair<Pos, Plant*>(plant->getPos(), plant));
			return true;
		}
	}
	else
	{
		std::map<Pos, Plant*>::iterator ip = plant_list.find(plant->getPos());
		if (ip != plant_list.end())
		{
			if (sure)
			{
				fixPlant(*plant_list[plant->getPos()]);
				delete plant_list[plant->getPos()];
				plant_list[plant->getPos()] = plant;
				return true;
			}
			else
				return false;
		}
		else
		{
			plant_list.insert(std::pair<Pos, Plant*>(plant->getPos(), plant));
			return true;
		}
	}
}

void PlantList::plantsOperate()
{
	for (std::map<Pos, Plant*>::iterator i = plant_list.begin();
		i != plant_list.end();)
	{
		if (i->second->isValid())
		{
			i->second->hit();
			showPlant(*(i->second));
			i++;
		}
		else
		{
			fixPlant(*(i->second));
			delete i->second;
			plant_list.erase(i++);
		}
	}
	for (std::map<Pos, Plant*>::iterator i = pumpkin_list.begin();
		i != pumpkin_list.end();)
	{
		if (i->second->isValid())
		{
			i->second->hit();
			showPlant(*(i->second));
			i++;
		}
		else
		{
			fixPlant(*(i->second));
			delete i->second;
			pumpkin_list.erase(i++);
		}
	}
}

Plant* PlantList::getPlant(int r, int c)
{
	Pos p(r, c);
	auto i = pumpkin_list.find(p);
	if (i != pumpkin_list.end())
		return i->second;
	auto j = plant_list.find(p);
	if (j != plant_list.end())
		return j->second;
	return NULL;
}

Sunflower::Sunflower(int r, int c) :Plant(PLANT::SUNFLOWER, r, c)
{
	// 第一次产生阳光时间较短
	status_count = rand() % 500 + 1000;
}

void Sunflower::hit()
{
	if (status_count >= AS)
	{
		// 产生阳光
		sunlight += ATK;
		COLOR = YELLOW;
		status_count = rand() % 50 - 100;
		color_count = 0;
	}
	else
	{
		// 等待
		status_count++;
		color_count++;
		if (color_count == COLOR_TIME)
			COLOR = _PLANT_COLOR[(int)PLANT_ID];
		//setCursorPos(20, 20);
		//std::cout << std::setw(3) << std::setfill('0') << status_count;
	}
	return;
}

PeaShooter::PeaShooter(int r, int c) :Plant(PLANT::PEA_SHOOTER, r, c) {}

void PeaShooter::hit()
{
	if (status_count >= AS)
	{
		int x = (pos.col + 1) * (COL_WIDTH + 1) - 1;
		int y = pos.row * (ROW_HIGH + 1) + TOP_HIGH + ROW_HIGH / 2;
		auto zombies = zlist.getZombie(pos.row);
		for (auto z : zombies)
		{
			if (z->getPos().col > x)
			{
				// 发出子弹
				Bullet* blt = new Bullet(x, y, 1, ATK, COLOR, BULLET::NORMAL);
				blist.addBullet(blt);
				status_count = 0;
				color_count = 0;
				COLOR = DARK_GREEN;
				break;
			}
		}
	}
	else
	{
		// 等待
		status_count++;
		color_count++;
		if (color_count == COLOR_TIME)
			COLOR = _PLANT_COLOR[(int)PLANT_ID];
	}
	return;
}

DoubleShooter::DoubleShooter(int r, int c) :Plant(PLANT::DOUBLE_SHOOTER, r, c), hit_count(0) {}

void DoubleShooter::hit()
{
	if (status_count >= AS)
	{
		int x = (pos.col + 1) * (COL_WIDTH + 1) - 1;
		int y = pos.row * (ROW_HIGH + 1) + TOP_HIGH + ROW_HIGH / 2;
		auto zombies = zlist.getZombie(pos.row);
		for (auto z : zombies)
		{
			if (z->getPos().col > x)
			{
				// 发出子弹
				Bullet* blt = new Bullet(x, y, 1, ATK, COLOR, BULLET::NORMAL);
				blist.addBullet(blt);
				if (hit_count == 1)
				{
					status_count = 4;
					hit_count = 0;
				}
				else
				{
					status_count = AS - 4;
					hit_count++;
				}
				color_count = 0;
				COLOR = DARK_GREEN;
			}
		}
	}
	else
	{
		// 等待
		status_count++;
		color_count++;
		if (color_count == COLOR_TIME)
			COLOR = _PLANT_COLOR[(int)PLANT_ID];
	}
	return;
}

Nut::Nut(int r, int c, PLANT id) :Plant(id, r, c) {}

void Nut::hit() {}

Potato::Potato(int r, int c) : Plant(PLANT::POTATO, r, c), is_ready(0), ready_count(0) {}

void Potato::hit()
{
	if (is_ready)
	{
		int x = (pos.col + 1) * (COL_WIDTH + 1) - 1;
		int y = pos.row * (ROW_HIGH + 1) + TOP_HIGH;
		Zombie* z = zlist.getZombie(x, y);
		if (z != NULL)
		{
			if (is_ready == 1)
			{
				showBoom(pos.row, pos.col, 0, RED);
				is_ready++;
			}
			else
			{
				z->beHit(ATK);
				fixBoom(pos.row, pos.col, 0);
				valid = 0;
			}
		}
	}
	else if (ready_count == 1000)
	{
		is_ready++;
		COLOR = RED;
	}
	else
	{
		ready_count++;
	}
}

IceShooter::IceShooter(int r, int c) : Plant(PLANT::ICE_SHOOTER, r, c), ice_time(AS * 3) {}

void IceShooter::hit()
{
	if (status_count >= AS && zlist.getZombie(pos.row).size() > 0)
	{
		int x = (pos.col + 1) * (COL_WIDTH + 1) - 1;
		int y = pos.row * (ROW_HIGH + 1) + TOP_HIGH + ROW_HIGH / 2;
		auto zombies = zlist.getZombie(pos.row);
		for (auto z : zombies)
		{
			if (z->getPos().col > x)
			{
				// 发出子弹
				Bullet* blt = new IceBullet(x, y, 1, ATK, COLOR, BULLET::ICE_BULLET, ice_time);
				blist.addBullet(blt);
				status_count = 0;
				color_count = 0;
				COLOR = DARK_CYAN;
			}
		}
	}
	else
	{
		// 等待
		status_count++;
		color_count++;
		if (color_count == COLOR_TIME)
			COLOR = _PLANT_COLOR[(int)PLANT_ID];
	}
	return;
}

HighNut::HighNut(int r, int c) :Nut(r, c, PLANT::HIGH_NUT) {}

Squash::Squash(int r, int c) : Plant(PLANT::SQUASH, r, c), attack(0) {}

void Squash::hit()
{
	int x = (pos.col + 1) * (COL_WIDTH + 1) - 1;
	int y = pos.row * (ROW_HIGH + 1) + TOP_HIGH;
	if (attack == 1)
	{
		current_hp = 100000;
		showBoom(pos.row, pos.col, 0, COLOR);
	}
	if (attack == 2)
	{
		auto zombies = zlist.getZombie(pos.row);
		for (auto i = zombies.begin(); i != zombies.end(); i++)
		{
			if ((*i)->getPos().col >= x - (COL_WIDTH + 1) && (*i)->getPos().col <= x)
				(*i)->beHit(ATK);
		}
		fixBoom(pos.row, pos.col, 0);
		this->valid = 0;
	}
	else if (status_count >= AS)
	{
		//int j = COL_WIDTH + 1;
		//Zombie* zombie = zlist.getZombie(x, y);
		//while (zombie == NULL && j > -COL_WIDTH - 1)
		//	zombie = zlist.getZombie(x + (j--), y);
		auto zombies = zlist.getZombie(pos.row);
		for (auto i = zombies.begin(); i != zombies.end(); i++)
		{
			if ((*i)->getPos().col >= x - (COL_WIDTH + 1) && (*i)->getPos().col < x)
			{
				this->COLOR = RED;
				color_count = 0;
				attack++;
				break;
			}
			else if ((*i)->getPos().col >= x - 2 * (COL_WIDTH + 1) && (*i)->getPos().col < x - (COL_WIDTH + 1))
			{
				if (!attack)
				{
					fixPlant(*this);
					this->pos.col--;
				}
				this->COLOR = RED;
				color_count = 0;
				attack++;
				break;
			}
			else if ((*i)->getPos().col >= x && (*i)->getPos().col <= x + (COL_WIDTH + 1) + 1)
			{
				if (!attack)
				{
					fixPlant(*this);
					this->pos.col++;
				}
				this->COLOR = RED;
				color_count = 0;
				attack++;
				break;
			}
			else if (attack)
				attack++;
		}
		//if (zombie != NULL)
		//{
		//	if (!attack)
		//	{
		//		fixPlant(*this);
		//		this->pos.col++;
		//		this->COLOR = RED;
		//		color_count = 0;
		//	}
		//	attack++;
		//}
		status_count = 0;
	}
	else
	{
		// 等待
		status_count++;
		color_count++;
		if (color_count == COLOR_TIME)
			COLOR = attack ? DARK_RED : _PLANT_COLOR[(int)PLANT_ID];
	}
}

Cherry::Cherry(int r, int c) : Plant(PLANT::CHERRY, r, c), attack(0) {}

void Cherry::hit()
{
	showBoom(pos.row, pos.col, 1, COLOR);
	int x = (pos.col + 1) * (COL_WIDTH + 1) - 1;
	int y = pos.row * (ROW_HIGH + 1) + TOP_HIGH;

	if (attack == 3)
	{
		auto zombies = zlist.getZombie(pos.row);
		for (auto i = zombies.begin(); i != zombies.end(); i++)
		{
			if ((*i)->getPos().col >= x - 2 * (COL_WIDTH - 1) && (*i)->getPos().col < x + COL_WIDTH + 1)
				(*i)->beHit(ATK);
		}
		zombies = zlist.getZombie(pos.row - 1);
		for (auto i = zombies.begin(); i != zombies.end(); i++)
		{
			if ((*i)->getPos().col >= x - 2 * (COL_WIDTH - 1) && (*i)->getPos().col < x + COL_WIDTH + 1)
				(*i)->beHit(ATK);
		}
		zombies = zlist.getZombie(pos.row + 1);
		for (auto i = zombies.begin(); i != zombies.end(); i++)
		{
			if ((*i)->getPos().col >= x - 2 * (COL_WIDTH - 1) && (*i)->getPos().col < x + COL_WIDTH + 1)
				(*i)->beHit(ATK);
		}
		fixBoom(pos.row, pos.col, 1);
		this->valid = 0;
	}
	else if (status_count >= AS)
	{
		this->COLOR = DARK_RED;
		color_count = 0;
		status_count = 0;
		attack++;
	}
	else
	{
		// 等待
		status_count++;
		color_count++;
		if (color_count == COLOR_TIME)
			COLOR = _PLANT_COLOR[(int)PLANT_ID];
	}
}

Garlic::Garlic(int r, int c) : Plant(PLANT::GARLIC, r, c) {}

void Garlic::hit() {}

Pumpkin::Pumpkin(int r, int c) : Plant(PLANT::PUMPKIN, r, c) {}

void Pumpkin::hit() {}
