#include "Plant.h"
#include "Bullet.h"
#include "Zombie.h"
#include "include.h"

static int _HP[] = { 100, 120, 120, 120, 30, 1000, 2000, 100, 100000, 160, 1000 }; // 植物血量
static int _ATK[] = { 25, 15, 15, 20, 1000, 0, 0, 1000, 1000, 0, 0 }; // 植物攻击力
static int _AS[] = { 1500, 50, 50, 50, 0, 0, 0, 20, 20, 0, 0 }; // 植物攻击速度，用等待值显示，ms
static int _PLANT_COLOR[] = { DARK_YELLOW, GREEN, GREEN, CYAN, WHITE, WHITE, WHITE, DARK_GREEN, RED, DARK_WHITE, YELLOW }; // 植物颜色
const char* _PLANT_NAME[] = { "SunFlower", "Peashooter", "Repeater", "SnowPea", "PotatoMine", "WallNut", "TallNut", "Squash", "CherryBomb", "Gralic", "PumpkinHead" };
//const char* _PLANT_NAME[] = { "向 日 葵", "豌豆射手", "双发射手", "寒冰射手", "土 豆 雷", "坚 果 墙", "高 坚 果", " 窝  瓜 ", "樱桃炸弹", " 大  蒜 ", "南 瓜 头" }; // 植物名字
const char* _PLANT_PATH[] = { "SunFlower", "Peashooter", "Repeater", "SnowPea", "PotatoMine", "WallNut", "TallNut", "Squash", "CherryBomb", "Gralic", "PumpkinHead"};
static int _WIDTH[] = { 73, 71, 73, 71, 75, 65, 83, 73, 112, 60, 97 };
static int _HIGH[] = { 74, 71, 71, 71, 55, 73, 119, 85, 81, 59, 67 };
int _COST[] = { 50, 100, 200, 175, 25, 50, 125, 50, 150, 50, 125 }; // 植物花费
#ifdef DEBUG
int _WAIT[] = { 25, 25, 25, 30, 100, 100, 150, 150, 250, 50, 150 }; // 商店冷却
#else
int _WAIT[] = { 250, 250, 250, 300, 1000, 1000, 1500, 1500, 2500, 500, 1500 }; // 商店冷却
#endif

Plant::Plant(PLANT pid, int r, int c) :
	PLANT_ID(pid), pos(r, c), status_count(0), valid(1), QWidget(UI_Game::bg), status(0)
{
	FULL_HP = _HP[(int)pid];
	ATK = _ATK[(int)pid];
	AS = _AS[(int)pid];
	COLOR = _PLANT_COLOR[(int)pid];
	current_hp = FULL_HP;
	color_count = 0;

	int x = LEFT_WIDTH + (c + 1) * (COL_WIDTH + 1) - _WIDTH[(int)pid];
	int y = TOP_HIGH + (r + 1) * (ROW_HIGH + 1) - _HIGH[(int)pid];
	setGeometry(x, y, _WIDTH[(int)pid], _HIGH[(int)pid]);
	show();
	setStyleSheet("background-image:url();");
	char movie_path[100] = "";
	sprintf(movie_path, "Resource/images/Plants/%s/%s.gif", _PLANT_PATH[(int)pid], _PLANT_PATH[(int)pid]);
	movie = new QMovie(movie_path);
	processLabel = new QLabel(this);
	processLabel->setMovie(movie);
	processLabel->setGeometry(0, 0, _WIDTH[(int)pid], _HIGH[(int)pid]);
	processLabel->setAttribute(Qt::WA_TranslucentBackground, true);
	processLabel->show();
	movie->start();

	setAttribute(Qt::WA_TransparentForMouseEvents, true);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
}

Plant::~Plant()
{
	qDebug() << "Plant" << _PLANT_NAME[(int)PLANT_ID] << "Dead";
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

void Plant::changeMovie(const char* path, int width, int high)
{
	hide();
	delete movie;
	movie = new QMovie(path);
	movie->setScaledSize(QSize(width, high));
	processLabel->setMovie(movie);
	movie->start();
	show();
}

void PlantList::reinit()
{
	qDebug() << "PlantList reinited!";
	for (auto i = plant_list.begin(); i != plant_list.end();)
	{
		delete i->second;
		plant_list.erase(i++);
	}
	for (auto i = pumpkin_list.begin(); i != pumpkin_list.end();)
	{
		delete i->second;
		pumpkin_list.erase(i++);
	}
}

PlantList::PlantList() {}

PlantList::~PlantList()
{
	reinit();
}

bool PlantList::addPlant(Plant* plant, bool sure)
{
	if (plant->getID() == PLANT::PUMPKIN)
	{
		std::map<Pos, Plant*>::iterator ip = pumpkin_list.find(plant->getPos());
		if (ip != pumpkin_list.end())
		{
			if (sure)
			{
				//fixPlant(*pumpkin_list[plant->getPos()]);
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
				//fixPlant(*plant_list[plant->getPos()]);
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
			//showPlant(*(i->second));
			i++;
		}
		else
		{
			//fixPlant(*(i->second));
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
			//showPlant(*(i->second));
			i++;
		}
		else
		{
			//fixPlant(*(i->second));
			delete i->second;
			pumpkin_list.erase(i++);
		}
	}
}

Plant* PlantList::getPlant(int r, int c)
{
	Plant* p = getPumkin(r, c);
	if (p)
		return p;
	return getNormalPlant(r, c);
}

Plant* PlantList::getNormalPlant(int r, int c)
{
	Pos p(r, c);
	auto j = plant_list.find(p);
	if (j != plant_list.end())
		return j->second;
	return NULL;
}

Plant* PlantList::getPumkin(int r, int c)
{
	Pos p(r, c);
	auto i = pumpkin_list.find(p);
	if (i != pumpkin_list.end())
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
		 UI_Game::addSunlight(ATK);
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
		auto zombies = UI_Game::zlist.getZombie(pos.row);
		for (auto z : zombies)
		{
			if (z->getPos().col >= x)
			{
				// 发出子弹
				Bullet* blt = new Bullet(x, y, 1, ATK, COLOR, BULLET::NORMAL);
				UI_Game::blist.addBullet(blt);
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
		auto zombies = UI_Game::zlist.getZombie(pos.row);
		for (auto z : zombies)
		{
			if (z->getPos().col >= x || hit_count == 1)
			{
				// 发出子弹
				Bullet* blt = new Bullet(x, y, 1, ATK, COLOR, BULLET::NORMAL);
				UI_Game::blist.addBullet(blt);
				if (hit_count == 1)
				{
					status_count = 8;
					hit_count = 0;
				}
				else
				{
					status_count = AS - 8;
					hit_count++;
				}
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

Nut::Nut(int r, int c, PLANT id) :Plant(id, r, c) {}

void Nut::hit() 
{
	if (current_hp < FULL_HP * 2 / 3 && status == 0)
	{
		status = 1;
		changeMovie("Resource/images/Plants/WallNut/Wallnut_cracked1.gif", _WIDTH[(int)PLANT_ID], _HIGH[(int)PLANT_ID]);
	}
	else if (current_hp < FULL_HP / 3 && status == 1)
	{
		status = 2;
		changeMovie("Resource/images/Plants/WallNut/Wallnut_cracked2.gif", _WIDTH[(int)PLANT_ID], _HIGH[(int)PLANT_ID]);
	}
}

Potato::Potato(int r, int c) : Plant(PLANT::POTATO, r, c), is_ready(0), ready_count(0) {}

void Potato::hit()
{
	if (is_ready)
	{
		int x = (pos.col + 1) * (COL_WIDTH + 1) - 1;
		int y = pos.row * (ROW_HIGH + 1) + TOP_HIGH;
		Zombie* z = UI_Game::zlist.getZombie(x, y);
		if (z != NULL)
		{
			if (is_ready < 50)
			{
				//showBoom(pos.row, pos.col, 0, RED);
				if (is_ready == 1)
				{
					QMediaPlayer* music = new QMediaPlayer(UI_Game::bg);
					music->setMedia(QUrl::fromLocalFile("Resource/sounds/boom.mp3"));
					music->setVolume(40);
					music->play();
					changeMovie("Resource/images/Plants/PotatoMine/PotatoMine_mashed.gif", _WIDTH[(int)PLANT_ID], _HIGH[(int)PLANT_ID]);
					z->beHit(ATK);
				}
				is_ready++;
			}
			else
			{
				//fixBoom(pos.row, pos.col, 0);
				valid = 0;
			}
		}
		else if (is_ready >= 2)
		{
			if (is_ready > 50)
				valid = 0;
			is_ready++;
		}
	}
	else if (ready_count == 1000)
	{
		is_ready++;
		current_hp = 20000;
		COLOR = RED;
		changeMovie("Resource/images/Plants/PotatoMine/PotatoMineReady.gif", _WIDTH[(int)PLANT_ID], _HIGH[(int)PLANT_ID]);
	}
	else
	{
		ready_count++;
	}
}

IceShooter::IceShooter(int r, int c) : Plant(PLANT::ICE_SHOOTER, r, c), ice_time(AS * 3) {}

void IceShooter::hit()
{
	if (status_count >= AS && UI_Game::zlist.getZombie(pos.row).size() > 0)
	{
		int x = (pos.col + 1) * (COL_WIDTH + 1) - 1;
		int y = pos.row * (ROW_HIGH + 1) + TOP_HIGH + ROW_HIGH / 2;
		auto zombies = UI_Game::zlist.getZombie(pos.row);
		for (auto z : zombies)
		{
			if (z->getPos().col >= x)
			{
				// 发出子弹
				Bullet* blt = new IceBullet(x, y, 1, ATK, COLOR, BULLET::ICE_BULLET, ice_time);
				UI_Game::blist.addBullet(blt);
				status_count = 0;
				color_count = 0;
				COLOR = DARK_CYAN;
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

HighNut::HighNut(int r, int c) :Nut(r, c, PLANT::HIGH_NUT) {}

void HighNut::hit()
{
	if (current_hp < FULL_HP * 2 / 3 && status == 0)
	{
		status = 1;
		changeMovie("Resource/images/Plants/TallNut/TallnutCracked1.gif", _WIDTH[(int)PLANT_ID], _HIGH[(int)PLANT_ID]);
	}
	else if (current_hp < FULL_HP / 3 && status == 1)
	{
		status = 2;
		changeMovie("Resource/images/Plants/TallNut/TallnutCracked2.gif", _WIDTH[(int)PLANT_ID], _HIGH[(int)PLANT_ID]);
	}
}

Squash::Squash(int r, int c) : Plant(PLANT::SQUASH, r, c), attack(0) {}

void Squash::hit()
{
	int x = (pos.col + 1) * (COL_WIDTH + 1) - 1;
	int y = pos.row * (ROW_HIGH + 1) + TOP_HIGH;
	if (attack == 1)
	{
		current_hp = 100000;
		int x = LEFT_WIDTH + (pos.col + 1) * (COL_WIDTH + 1) - 100;
		int y = TOP_HIGH + (pos.row + 1) * (ROW_HIGH + 1) - 226;
		setGeometry(x, y, 100, 226);
		processLabel->setGeometry(0, 0, 100, 226);
		processLabel->repaint();
		changeMovie("Resource/images/Plants/Squash/SquashAttack.gif", 100, 226);
		//showBoom(pos.row, pos.col, 0, COLOR);
	}
	if (attack >= 5)
	{
		auto zombies = UI_Game::zlist.getZombie(pos.row);
		for (auto i = zombies.begin(); i != zombies.end(); i++)
		{
			if ((*i)->getPos().col >= x - (COL_WIDTH + 1) && (*i)->getPos().col <= x)
				(*i)->beHit(ATK);
		}
		//fixBoom(pos.row, pos.col, 0);
		this->valid = 0;
	}
	else if (status_count >= AS)
	{
		//int j = COL_WIDTH + 1;
		//Zombie* zombie = zlist.getZombie(x, y);
		//while (zombie == NULL && j > -COL_WIDTH - 1)
		//	zombie = zlist.getZombie(x + (j--), y);
		auto zombies = UI_Game::zlist.getZombie(pos.row);
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
					//fixPlant(*this);
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
					//fixPlant(*this);
					this->pos.col++;
				}
				this->COLOR = RED;
				color_count = 0;
				attack++;
				break;
			}
			else if (attack == 1)
			{
				attack++;
				break;
			}
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
	//showBoom(pos.row, pos.col, 1, COLOR);
	int x = (pos.col + 1) * (COL_WIDTH + 1) - 1;
	int y = pos.row * (ROW_HIGH + 1) + TOP_HIGH;
	if (attack == 2)
	{
		if (status == 0)
		{
			status = 1;
			int x = LEFT_WIDTH + (pos.col + 1) * (COL_WIDTH + 1) - 178;
			int y = TOP_HIGH + (pos.row + 1) * (ROW_HIGH + 1) - 120;
			setGeometry(x, y, 213, 160);
			processLabel->setGeometry(0, 0, 213, 160);
			processLabel->repaint();
			changeMovie("Resource/images/Plants/CherryBomb/Boom.gif", 213, 160);
			QMediaPlayer* music = new QMediaPlayer(UI_Game::bg);
			music->setMedia(QUrl::fromLocalFile("Resource/sounds/boom.mp3"));
			music->setVolume(40);
			music->play();
		}
		auto zombies = UI_Game::zlist.getZombie(pos.row);
		for (auto i = zombies.begin(); i != zombies.end(); i++)
		{
			if ((*i)->getPos().col >= x - 2 * (COL_WIDTH - 1) && (*i)->getPos().col < x + COL_WIDTH + 1)
				(*i)->beHit(ATK);
		}
		zombies = UI_Game::zlist.getZombie(pos.row - 1);
		for (auto i = zombies.begin(); i != zombies.end(); i++)
		{
			if ((*i)->getPos().col >= x - 2 * (COL_WIDTH - 1) && (*i)->getPos().col < x + COL_WIDTH + 1)
				(*i)->beHit(ATK);
		}
		zombies = UI_Game::zlist.getZombie(pos.row + 1);
		for (auto i = zombies.begin(); i != zombies.end(); i++)
		{
			if ((*i)->getPos().col >= x - 2 * (COL_WIDTH - 1) && (*i)->getPos().col < x + COL_WIDTH + 1)
				(*i)->beHit(ATK);
		}
		//fixBoom(pos.row, pos.col, 1);
	}
	else if (attack == 4)
	{
		this->valid = 0;
	}
	if (status_count >= AS)
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

void Garlic::hit()
{
	if (current_hp < FULL_HP * 2 / 3 && status == 0)
	{
		status = 1;
		changeMovie("Resource/images/Plants/Garlic/Garlic_body2.gif", _WIDTH[(int)PLANT_ID], _HIGH[(int)PLANT_ID]);
	}
	else if (current_hp < FULL_HP / 3 && status == 1)
	{
		status = 2;
		changeMovie("Resource/images/Plants/Garlic/Garlic_body3.gif", _WIDTH[(int)PLANT_ID], _HIGH[(int)PLANT_ID]);
	}
}

Pumpkin::Pumpkin(int r, int c) : Plant(PLANT::PUMPKIN, r, c)
{
	back_movie = new QMovie("Resource/images/Plants/PumpkinHead/Pumpkin_back.gif");
	backLabel = new QLabel(UI_Game::bg);
	backLabel->setMovie(back_movie);
	int x = LEFT_WIDTH + (c + 1) * (COL_WIDTH + 1) - _WIDTH[(int)PLANT_ID];
	int y = TOP_HIGH + (r + 1) * (ROW_HIGH + 1) - _HIGH[(int)PLANT_ID];
	backLabel->setGeometry(x, y, _WIDTH[(int)PLANT_ID], _HIGH[(int)PLANT_ID]);
	backLabel->setAttribute(Qt::WA_TranslucentBackground, true);
	backLabel->show();
	back_movie->start();
	backLabel->stackUnder(this);
}

Pumpkin::~Pumpkin()
{
	delete backLabel;
}

void Pumpkin::hit()
{
	if (current_hp < FULL_HP * 2 / 3 && status == 0)
	{
		status = 1;
		changeMovie("Resource/images/Plants/PumpkinHead/Pumpkin_damage1.gif", _WIDTH[(int)PLANT_ID], _HIGH[(int)PLANT_ID]);
	}
	else if (current_hp < FULL_HP / 3 && status == 1)
	{
		status = 2;
		changeMovie("Resource/images/Plants/PumpkinHead/Pumpkin_damage2.gif", _WIDTH[(int)PLANT_ID], _HIGH[(int)PLANT_ID]);
	}
	Plant* p = UI_Game::plist.getNormalPlant(pos.row, pos.col);
	if (p != NULL)
	{
		p->raise();
		raise();
	}
}
