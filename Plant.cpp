#include "include.h"

static int _HP[] = { 100, 120, 120, 1000, 30, 120 }; // 植物血量
static int _ATK[] = { 25, 15, 15, 0, 1000, 20 }; // 植物攻击力
static int _AS[] = { 1500, 50, 50, 0, 0, 50 }; // 植物攻击速度，用等待值显示，ms
static int _PLANT_COLOR[] = { DARK_YELLOW, GREEN, GREEN, WHITE, WHITE, CYAN }; // 植物颜色
const char* _PLANT_NAME[] = { "向日葵", "豌豆射手", "双发射手", "坚果墙", "土豆雷", "寒冰射手" }; // 植物名字
int _COST[] = { 50, 100, 200, 50, 25, 175 }; // 植物花费

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

bool Plant::isValid() const
{
	return valid;
}

PlantList::PlantList() {}

bool PlantList::addPlant(Plant* plant, bool sure)
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
}

Plant* PlantList::getPlant(int r, int c)
{
	Pos p(r, c);
	auto i = plant_list.find(p);
	if (i != plant_list.end())
		return i->second;
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
	if (status_count >= AS && zlist.getZombie(pos.row).size() > 0)
	{
		// 发出子弹
		int x = (pos.col + 1) * (COL_WIDTH + 1) - 1;
		int y = pos.row * (ROW_HIGH + 1) + 7;
		Bullet blt(x, y, 1, ATK, COLOR);
		blist.addBullet(blt);
		status_count = 0;
		color_count = 0;
		COLOR = DARK_GREEN;
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
	if (status_count >= AS && zlist.getZombie(pos.row).size() > 0)
	{
		// 发出子弹
		int x = (pos.col + 1) * (COL_WIDTH + 1) - 1;
		int y = pos.row * (ROW_HIGH + 1) + TOP_HIGH + 3;
		Bullet blt(x, y, 1, ATK, COLOR);
		blist.addBullet(blt);
		if (hit_count == 1)
		{
			status_count = 0;
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

Nut::Nut(int r, int c) :Plant(PLANT::NUT, r, c) {}

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
			z->beHit(ATK);
			valid = 0;
		}
	}
	else if (ready_count == 1000)
	{
		is_ready = 1;
		COLOR = RED;
	}
	else
	{
		ready_count++;
	}
}
