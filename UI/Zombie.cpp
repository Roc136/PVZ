#include "Zombie.h"
#include "Plant.h"
#include "include.h"

static int _HP[] = { 120, 240, 360, 360, 240, 240, 500 }; // 僵尸血量
static int _ATK[] = { 8, 8, 8, 10, 10, 10, 10000 }; // 僵尸攻击力
static int _AS[] = { 30, 30, 30, 30, 30, 30, 42 }; // 僵尸攻击速度，用等待值显示，ms
static int _MS[] = { 3, 3, 3, 3, 1, 3, 5 }; // 僵尸移动速度，用等待值显示，ms
static int _ZOMBIE_SCORE[] = { 10, 15, 25, 35, 35, 40, 50 };
static int _ZOMBIE_COLOR[] = { WHITE, DARK_YELLOW, GREY, DARK_WHITE, BLUE, RED, WHITE }; // 僵尸颜色
//const char* _ZOMBIE_NAME[] = { "普通僵尸", "路障僵尸", "铁桶僵尸", "读报僵尸", "撑杆僵尸", "小丑僵尸", "投石僵尸" }; // 僵尸名字
const char* _ZOMBIE_NAME[] = { "Zombie", "ConeheadZombie", "BucketheadZombie", "NewspaperZombie", "PoleVaultingZombie", "ClownZombie", "BasketballZombie"};
const char* _ZOMBIE_PATH[] = { "Zombie", "ConeheadZombie", "BucketheadZombie", "NewspaperZombie", "PoleVaultingZombie", "ClownZombie", "BasketballZombie" };
static int _WIDTH[] = { 166, 166, 166, 166, 348, 166, 166 };
static int _HIGH[] = { 144, 144, 144, 144, 218, 144, 144 };
static int _LEFT[] = { 5, 5, 18, 5, 40, 5, 20 };
static int _ZID[] = {
	UI_Game::level - 7,
	UI_Game::level - 6,
	UI_Game::level - 6,
	UI_Game::level - 5,
	UI_Game::level - 5,
	UI_Game::level - 5,
	UI_Game::level - 4,
	UI_Game::level - 4,
	UI_Game::level - 4,
	UI_Game::level - 4,
	UI_Game::level - 3,
	UI_Game::level - 3,
	UI_Game::level - 3,
	UI_Game::level - 3,
	UI_Game::level - 3,
	UI_Game::level - 2,
	UI_Game::level - 2,
	UI_Game::level - 2,
	UI_Game::level - 2,
	UI_Game::level - 2,
	UI_Game::level - 2,
	UI_Game::level - 1,
	UI_Game::level - 1,
	UI_Game::level - 1,
	UI_Game::level - 1,
	UI_Game::level - 1,
	UI_Game::level - 1,
	UI_Game::level - 1,
}; // 随机产生僵尸种类，等级越高产生的僵尸种类难度越高

void Zombie::changeMovie(const char* path)
{
	hide();
	delete movie;
	movie = new QMovie(path);
	movie->setScaledSize(QSize(_WIDTH[(int)ZOMBIE_ID], _HIGH[(int)ZOMBIE_ID]));
	processLabel->setMovie(movie);
	movie->start();
	show();
}

Zombie::Zombie(ZOMBIE zid, int x, int y) :
	ZOMBIE_ID(zid), pos(y, x), eat_count(0), move_count(0), color_count(0),  status(0), slowed(0), garlic(0), valid(1), QWidget(UI_Game::bg)
{
	FULL_HP = _HP[(int)zid];
	ATK = _ATK[(int)zid];
	AS = _AS[(int)zid];
	MS = _MS[(int)zid];
	COLOR = _ZOMBIE_COLOR[(int)zid];
	ZOMBIE_SCORE = _ZOMBIE_SCORE[(int)zid];
	current_hp = FULL_HP;
	old_ms = MS;
	old_as = AS;

	int x_ = LEFT_WIDTH + pos.col + COL_WIDTH - _WIDTH[(int)zid] + _LEFT[(int)zid];
	int y_ = TOP_HIGH + pos.row + ROW_HIGH - _HIGH[(int)zid] - 35;
	setGeometry(x_, y_, _WIDTH[(int)zid], _HIGH[(int)zid]);
	setStyleSheet("background-image:url();");
	char movie_path[100] = "";
	sprintf(movie_path, "Resource/images/Zombies/%s/%s.gif", _ZOMBIE_PATH[(int)zid], _ZOMBIE_PATH[(int)zid]);
	movie = new QMovie(movie_path);
	processLabel = new QLabel(this);
	movie->setScaledSize(QSize(_WIDTH[(int)zid], _HIGH[(int)zid]));
	processLabel->setMovie(movie);
	processLabel->setGeometry(0, 0, _WIDTH[(int)zid], _HIGH[(int)zid]);
	processLabel->setAttribute(Qt::WA_TranslucentBackground, true);
	processLabel->show();
	movie->start();

	setAttribute(Qt::WA_TransparentForMouseEvents, true);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	raise();
	show();
}

Zombie::~Zombie()
{
	qDebug() << "Zombie" << _ZOMBIE_NAME[(int)ZOMBIE_ID] << "Dead";
}

bool Zombie::beHit(int atk)
{
	current_hp -= atk;
	color_count = 0;
	COLOR = RED;
	valid = (current_hp > 0);
	if (valid == 0)
	{
		//fixZombie(*this);
		UI_Game::addScore(ZOMBIE_SCORE);
	}
	return valid;
}

void Zombie::beSlowed(int ice_time)
{
	slowed = ice_time;
	MS = old_ms * 2;
	AS = old_as * 2;
}

Pos Zombie::getPos() const
{
	return pos;
}

bool Zombie::isValid() const
{
	return valid;
}

void Zombie::move()
{
	if (slowed) slowed--; else
	{
		MS = old_ms;
		AS = old_as;
	}
	if (garlic > 0)
	{
		//fixZombie(*this);
		garlic--;
		pos.row++;
		Plant* tmp = NULL;
		special(1, 0, tmp);
		fix();
	}
	else if (garlic < 0)
	{
		//fixZombie(*this);
		garlic++;
		pos.row--;
		Plant* tmp = NULL;
		special(1, 0, tmp);
		fix();
	}
	if (move_count >= MS && !garlic)
	{
		int r = (pos.row - TOP_HIGH) / (ROW_HIGH + 1);
		int c = pos.col / (COL_WIDTH + 1);
		Plant* plant = UI_Game::plist.getPlant(r, c);
		if (plant == NULL)
		{
			// 移动
			if (!special(1, 0, plant))
			{
				pos.col--;
				fix();
				if (pos.col == -1)
					UI_Game::alive = 0;
			}
#ifdef DEBUG
			//setCursorPos(30, 30);
			//printf("%d, %d", pos.row, pos.col);
#endif
		}
		move_count = 0;
		eat_count++;
	}
	else if (eat_count >= AS && !garlic)
	{
		int r = (pos.row - TOP_HIGH) / (ROW_HIGH + 1);
		int c = pos.col / (COL_WIDTH + 1);
		Plant* plant = UI_Game::plist.getPlant(r, c);
		if (!special(0, 1, plant))
		{
			// 吃
			if (plant != NULL)
			{
				plant->beEaten(ATK);
				if (plant->getID() == PLANT::GARLIC && ZOMBIE_ID != ZOMBIE::THROW)
				{
					pos.col--;
					if (pos.row == TOP_HIGH)
						garlic += (ROW_HIGH + 1);
					else if (pos.row == ((ROW - 1) * (ROW_HIGH + 1) + TOP_HIGH))
						garlic += -(ROW_HIGH + 1);
					else
						garlic += ((rand() % 2) ? (ROW_HIGH + 1) : -(ROW_HIGH + 1));
				}
				QMediaPlayer* music = new QMediaPlayer(UI_Game::bg);
				music->setMedia(QUrl::fromLocalFile("Resource/sounds/eat.mp3"));
				music->setVolume(40);
				music->play();
			}
		}
		color_count = 0;
		eat_count = 0;
		move_count++;
	}
	else
	{
		// 等待
		move_count++;
		eat_count++;
		color_count++;
		Plant* tmp = NULL;
		special(0, 0, tmp);
	}
	return;
}

int Zombie::special(int move_flag, int eat_flag, Plant*& plant)
{
	if (move_count >= MS)
	{
		if (move_flag)
			if (status != 0)
			{
				status = 0;
				char movie_path[100] = "";
				sprintf(movie_path, "Resource/images/Zombies/%s/%s.gif", _ZOMBIE_PATH[(int)ZOMBIE_ID], _ZOMBIE_PATH[(int)ZOMBIE_ID]);
				changeMovie(movie_path);
			}
	}
	else if (eat_count >= AS)
	{
		if (eat_flag && plant)
		{
			if (status != 1)
			{
				status = 1;
				char movie_path[100] = "";
				sprintf(movie_path, "Resource/images/Zombies/%s/%sAttack.gif", _ZOMBIE_PATH[(int)ZOMBIE_ID], _ZOMBIE_PATH[(int)ZOMBIE_ID]);
				changeMovie(movie_path);
			}
			COLOR = GREY;
		}
	}
	else
	{
		if (color_count == COLOR_TIME)
			COLOR = slowed ? CYAN : _ZOMBIE_COLOR[(int)ZOMBIE_ID];
	}
	return 0;
}

void Zombie::fix()
{
	//qDebug() << "Zmobie" << _ZOMBIE_NAME[(int)ZOMBIE_ID] << "move to" << pos.col;
	int x = LEFT_WIDTH + pos.col + COL_WIDTH - _WIDTH[(int)ZOMBIE_ID] + _LEFT[(int)ZOMBIE_ID];
	int y = TOP_HIGH + pos.row + ROW_HIGH - _HIGH[(int)ZOMBIE_ID] - 35;
	setGeometry(x, y, _WIDTH[(int)ZOMBIE_ID], _HIGH[(int)ZOMBIE_ID]);
	hide();
	repaint();
	show();
}

void Zombie::show()
{
	QWidget::show();
	processLabel->show();
}

void Zombie::hide()
{
	QWidget::hide();
	processLabel->hide();
}

void ZombieList::reinit()
{
	printf("ZombieList reinited!\n");
	for (auto i = zombie_list.begin(); i != zombie_list.end();)
	{
		delete (*i);
		i = zombie_list.erase(i);
	}
	create_count = 0;
	create_time = FIRST_ZOMBIE_TIME;
}

ZombieList::ZombieList()
{
	create_count = 0;
	create_time = FIRST_ZOMBIE_TIME;
}

ZombieList::~ZombieList()
{
	reinit();
}

void ZombieList::addZombie()
{
	int zid_idx = rand() % (sizeof(_ZID) / sizeof(int));
	int zid = _ZID[zid_idx] >= 0 ? _ZID[zid_idx] : 0;
	int r = rand() % ROW;
#ifdef DEBUG
	//r = 0;
	static int zid_tmp = 0;
	zid = zid_tmp;
	zid_tmp++;
	//zid_tmp %= 5;
	zid_tmp %= ZOMBIE_KIND_NUM;
	//zid = 6;
#endif
	int y = r * (ROW_HIGH + 1) + TOP_HIGH;
	if (UI_Game::zlist.getZombie(NEW_ZOMBIE_X, y) || UI_Game::zlist.getZombie(NEW_ZOMBIE_X - 1, y) || UI_Game::zlist.getZombie(NEW_ZOMBIE_X - 2, y) || UI_Game::zlist.getZombie(r).size() > UI_Game::level * 1.3)
	{
		zid = -1; // 不产生僵尸
	}
	switch (zid)
	{
	case -1:
		return;
	case 0:
	{
		Zombie* z = new Zombie(ZOMBIE::ORDINARY, NEW_ZOMBIE_X, y);
		zombie_list.push_back(z);
		break;
	}
	case 1:
	{
		Barricede* z = new Barricede(NEW_ZOMBIE_X, y);
		zombie_list.push_back(z);
		break;
	}
	case 2:
	{
		Buckethead* z = new Buckethead(NEW_ZOMBIE_X, y);
		zombie_list.push_back(z);
		break;
	}
	case 3:
	{
		Newspaper* z = new Newspaper(NEW_ZOMBIE_X, y);
		zombie_list.push_back(z);
		break;
	}
	case 4:
	{
		PoleVaulting* z = new PoleVaulting(NEW_ZOMBIE_X, y);
		zombie_list.push_back(z);
		break;
	}
	case 5:
	{
		Clown* z = new Clown(NEW_ZOMBIE_X, y);
		zombie_list.push_back(z);
		break;
	}
	case 6:
	{
		Throw* z = new Throw(NEW_ZOMBIE_X, y);
		zombie_list.push_back(z);
		break;
	}
	default:
	{
		zid = 0;
		Zombie* z = new Zombie(ZOMBIE::ORDINARY, NEW_ZOMBIE_X, y);
		zombie_list.push_back(z);
	}
	}
	if (zid != -1 && flag)
	{
		QMediaPlayer* music = new QMediaPlayer(UI_Game::bg);
		music->setMedia(QUrl::fromLocalFile("Resource/sounds/coming.mp3"));
		music->setVolume(40);
		music->play();
		flag = 0;
	}
	qDebug() << "Create zombie" << _ZOMBIE_NAME[zid];
}

void ZombieList::zombieOperate()
{
	for (std::vector<Zombie*>::iterator i = zombie_list.begin();
		i != zombie_list.end();)
	{
		if ((*i)->isValid())
		{
			(*i)->move();
			//showZombie(*(*i));
			i++;
		}
		else
		{
			//fixZombie(**i);
			delete (*i);
			i = zombie_list.erase(i);
		}
	}
	if (create_count >= create_time)
	{
		create_count = 0;
		if (create_time == FIRST_ZOMBIE_TIME)
#ifdef DEBUG
			create_time = 100;
#else
			create_time = 800;
#endif
		else if (create_time > 100)
			create_time = create_time - rand() % (3 * UI_Game::level);
		addZombie();
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
	int y = r * (ROW_HIGH + 1) + TOP_HIGH;
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

int Barricede::special(int move_flag, int eat_flag, Plant*& plant)
{
	if (move_count >= MS)
	{
		if (move_flag)
			if (status != 0)
			{
				status = 0;
				char movie_path[100] = "";
				sprintf(movie_path, "Resource/images/Zombies/%s/%s.gif", _ZOMBIE_PATH[(int)ZOMBIE_ID], _ZOMBIE_PATH[(int)ZOMBIE_ID]);
				changeMovie(movie_path);
			}
	}
	else if (eat_count >= AS)
	{
		if (eat_flag && plant)
		{
			if (status != 1)
			{
				status = 1;
				char movie_path[100] = "";
				sprintf(movie_path, "Resource/images/Zombies/%s/%sAttack.gif", _ZOMBIE_PATH[(int)ZOMBIE_ID], _ZOMBIE_PATH[(int)ZOMBIE_ID]);
				changeMovie(movie_path);
			}
			COLOR = YELLOW;
		}
	}
	else
	{
		if (color_count == COLOR_TIME)
		{
			if (current_hp < FULL_HP / 2)
				COLOR = slowed ? CYAN : _ZOMBIE_COLOR[0];
			else
				COLOR = slowed ? CYAN : _ZOMBIE_COLOR[(int)ZOMBIE_ID];
		}
	}
	return 0;
}

Buckethead::Buckethead(int x, int y) :Zombie(ZOMBIE::BUCKETHEAD, x, y) {}

int Buckethead::special(int move_flag, int eat_flag, Plant*& plant)
{
	if (move_count >= MS)
	{
		if (move_flag)
			if (status != 0)
			{
				status = 0;
				char movie_path[100] = "";
				sprintf(movie_path, "Resource/images/Zombies/%s/%s.gif", _ZOMBIE_PATH[(int)ZOMBIE_ID], _ZOMBIE_PATH[(int)ZOMBIE_ID]);
				changeMovie(movie_path);
			}
	}
	else if (eat_count >= AS)
	{
		if (eat_flag && plant)
		{
			if (status != 1)
			{
				status = 1;
				char movie_path[100] = "";
				sprintf(movie_path, "Resource/images/Zombies/%s/%sAttack.gif", _ZOMBIE_PATH[(int)ZOMBIE_ID], _ZOMBIE_PATH[(int)ZOMBIE_ID]);
				changeMovie(movie_path);
			}
			COLOR = YELLOW;
		}
	}
	else
	{
		if (color_count == COLOR_TIME)
		{
			if (current_hp < FULL_HP / 3)
				COLOR = slowed ? CYAN : WHITE;
			else if (current_hp < FULL_HP * 2 / 3)
				COLOR = slowed ? CYAN : DARK_WHITE;
			else
				COLOR = slowed ? CYAN : _ZOMBIE_COLOR[(int)ZOMBIE_ID];
		}
	}
	return 0;
}

Newspaper::Newspaper(int x, int y) :Zombie(ZOMBIE::NEWSPAPER, x, y) {}

int Newspaper::special(int move_flag, int eat_flag, Plant*& plant)
{
	if (move_count >= MS)
	{
		if (move_flag)
		{
			if (current_hp < FULL_HP * 2 / 3)
			{
				MS = _MS[(int)ZOMBIE_ID] / 2;
				old_ms = MS;
				if (status != 0)
				{
					status = 0;
					char movie_path[100] = "";
					sprintf(movie_path, "Resource/images/Zombies/%s/%s.gif", _ZOMBIE_PATH[(int)ZOMBIE_ID], _ZOMBIE_PATH[(int)ZOMBIE_ID]);
					changeMovie(movie_path);
				}
			}
			else
			{
				if (status != 0)
				{
					status = 0;
					char movie_path[100] = "";
					sprintf(movie_path, "Resource/images/Zombies/%s/%s.gif", _ZOMBIE_PATH[(int)ZOMBIE_ID], _ZOMBIE_PATH[(int)ZOMBIE_ID]);
					changeMovie(movie_path);
				}
			}
		}
	}
	else if (eat_count >= AS)
	{
		if (eat_flag && plant)
		{
			if (status != 1)
			{
				status = 1;
				char movie_path[100] = "";
				if (current_hp < FULL_HP * 2 / 3)
					sprintf(movie_path, "Resource/images/Zombies/%s/%sAttack.gif", _ZOMBIE_PATH[(int)ZOMBIE_ID], _ZOMBIE_PATH[(int)ZOMBIE_ID]);
				else
					sprintf(movie_path, "Resource/images/Zombies/%s/%sAttack.gif", _ZOMBIE_PATH[(int)ZOMBIE_ID], _ZOMBIE_PATH[(int)ZOMBIE_ID]);
				changeMovie(movie_path);
			}
			COLOR = GREY;
		}
	}
	else
	{
		if (color_count == COLOR_TIME)
		{
			if (current_hp < FULL_HP * 2 / 3)
				COLOR = slowed ? CYAN : WHITE;
			else
				COLOR = slowed ? CYAN : _ZOMBIE_COLOR[(int)ZOMBIE_ID];
		}
	}
	return 0;
}

PoleVaulting::PoleVaulting(int x, int y) :Zombie(ZOMBIE::POLE_VAULTING, x, y), rod(1), jump(0) {}

int PoleVaulting::special(int move_flag, int eat_flag, Plant*& plant)
{
	if (move_count >= MS)
	{
		if (move_flag)
		{
			if (status != 0)
			{
				status = 0;
				char movie_path[100] = "";
				if(rod)
					sprintf(movie_path, "Resource/images/Zombies/%s/%s.gif", _ZOMBIE_PATH[(int)ZOMBIE_ID], _ZOMBIE_PATH[(int)ZOMBIE_ID]);
				else
					sprintf(movie_path, "Resource/images/Zombies/%s/%sWalk.gif", _ZOMBIE_PATH[(int)ZOMBIE_ID], _ZOMBIE_PATH[(int)ZOMBIE_ID]);
				changeMovie(movie_path);
			}
		}
	}
	else if (eat_count >= AS)
	{
		if (eat_flag && plant)
		{
			if (rod)
			{
				COLOR = RED;
				if (plant->getID() == PLANT::PUMPKIN)
				{
					int r = (pos.row - TOP_HIGH) / (ROW_HIGH + 1);
					int c = pos.col / (COL_WIDTH + 1);
					Plant* p = UI_Game::plist.getNormalPlant(r, c);
					if (p && p->getID() == PLANT::HIGH_NUT)
						jump = 0;
					else if(p)
						jump = COL_WIDTH;
				}
				else
				{
					if (plant->getID() == PLANT::HIGH_NUT)
						jump = 0;
					else
						jump = COL_WIDTH ;
				}
				changeMovie("Resource/images/Zombies/PoleVaultingZombie/PoleVaultingZombieJump.gif");
				rod--;
				MS = MS * 2;
				old_ms = MS;
				return 1;
			}
			else
			{
				COLOR = DARK_BLUE;
				if (status != 1)
				{
					status = 1;
					char movie_path[100] = "";
					sprintf(movie_path, "Resource/images/Zombies/%s/%sAttack.gif", _ZOMBIE_PATH[(int)ZOMBIE_ID], _ZOMBIE_PATH[(int)ZOMBIE_ID]);
					changeMovie(movie_path);
				}
			}
		}
	}
	else
	{
		if (color_count >= COLOR_TIME)
		{
			if (current_hp < FULL_HP * 2 / 3)
				COLOR = slowed ? CYAN : WHITE;
			else
				COLOR = slowed ? CYAN : _ZOMBIE_COLOR[(int)ZOMBIE_ID];
		}
		if (jump > 0)
		{
			pos.col-=8;
			fix();
			jump-=8;
			//if(jump <= 5)
			//	changeMovie("Resource/images/Zombies/PoleVaultingZombie/PoleVaultingZombieJump2.gif");
			//showZombie(*this);
			if (pos.col <= 0)
				UI_Game::alive = 0;
			return 1;
		}
	}
	return 0;
}

Clown::Clown(int x, int y) :Zombie(ZOMBIE::CLOWN, x, y)
{
	if (rand() % 100 < 95)
	{
		boom_time = rand() % 500 + 750;
	}
	else
	{
		boom_time = rand() % 400 + 150;
	}
	boom_color = RED;
	boom_atk = 20000;
}

int Clown::special(int move_flag, int eat_flag, Plant*& plant)
{
	if (boom_time <= 30)
	{
		if (status != 2)
		{
			status = 2;
			changeMovie("Resource/images/Plants/CherryBomb/Boom.gif");
		}
		int r = (pos.row - TOP_HIGH) / (ROW_HIGH + 1);
		int c = pos.col / (COL_WIDTH + 1);
		if (boom_time == 0)
		{
			QMediaPlayer* music = new QMediaPlayer(UI_Game::bg);
			music->setMedia(QUrl::fromLocalFile("Resource/sounds/boom.mp3"));
			music->setVolume(40);
			music->play();
			for (int i = -1; i <= 1; i++)
				for (int j = -1; j <= 1; j++)
				{
					Plant* plant = UI_Game::plist.getPlant(r + i, c + j);
					if (plant != NULL)
						plant->beEaten(boom_atk);
				}
			valid = 0;
			UI_Game::addScore(ZOMBIE_SCORE);
			//fixBoom(r, c, 1);
		}
		else if (boom_time % 5 == 0)
		{
			//showBoom(r, c, 1, boom_color);
			boom_color = 0x10 - boom_color;
		}
		boom_time--;
		return 1;
	}
	if (move_count >= MS)
	{
		if (move_flag)
		{
			if (status != 0)
			{
				status = 0;
				char movie_path[100] = "";
				sprintf(movie_path, "Resource/images/Zombies/%s/%s.gif", _ZOMBIE_PATH[(int)ZOMBIE_ID], _ZOMBIE_PATH[(int)ZOMBIE_ID]);
				changeMovie(movie_path);
			}
			boom_time--;
		}
	}
	else if (eat_count >= AS)
	{
		if (eat_flag && plant)
		{
			if (status != 1)
			{
				status = 1;
				char movie_path[100] = "";
				sprintf(movie_path, "Resource/images/Zombies/%s/%sAttack.gif", _ZOMBIE_PATH[(int)ZOMBIE_ID], _ZOMBIE_PATH[(int)ZOMBIE_ID]);
				changeMovie(movie_path);
			}
			COLOR = DARK_RED;
			boom_time--;
		}
	}
	else
	{
		if (color_count >= COLOR_TIME)
		{
			COLOR = slowed ? CYAN : _ZOMBIE_COLOR[(int)ZOMBIE_ID];
		}
		boom_time--;
	}
	return 0;
}

Throw::Throw(int x, int y) :Zombie(ZOMBIE::THROW, x, y), basketball(20), basketball_atk(15), basketball_as(2), throw_count(0) 
{
	QMediaPlayer* music = new QMediaPlayer(UI_Game::bg);
	music->setMedia(QUrl::fromLocalFile("Resource/sounds/jntm.mp3"));
	music->setVolume(40);
	music->play();
}

int Throw::special(int move_flag, int eat_flag, Plant*& plant)
{
	if (move_count >= MS)
	{
		if (move_flag)
		{
			int r = (pos.row - TOP_HIGH) / (ROW_HIGH + 1);
			int max_c = pos.col / (COL_WIDTH + 1);
			int c = 0;
			Plant* p = UI_Game::plist.getPlant(r, c);
			for (c = 1; c < max_c && !p; c++)
				p = UI_Game::plist.getPlant(r, c);
			if (basketball > 0 && p != NULL)
				return 1;
			else
			{
				if (status != 0)
				{
					status = 0;
					char movie_path[100] = "";
					sprintf(movie_path, "Resource/images/Zombies/%s/%s.gif", _ZOMBIE_PATH[(int)ZOMBIE_ID], _ZOMBIE_PATH[(int)ZOMBIE_ID]);
					changeMovie(movie_path);
				}
				return 0;
			}
		}
	}
	else if (eat_count >= AS)
	{
		if (eat_flag)
		{
			int r = (pos.row - TOP_HIGH) / (ROW_HIGH + 1);
			int max_c = pos.col / (COL_WIDTH + 1);
			int c = 0;
			Plant* p = UI_Game::plist.getPlant(r, c);
			for (c = 1; c < max_c && !p; c++)
				p = UI_Game::plist.getPlant(r, c);
			if (basketball > 0 && p)
			{
				if (status != 2)
				{
					status = 2;
					changeMovie("Resource/images/Zombies/BasketballZombie/BasketballZombieThrow.gif");
				}
				else if (throw_count >= basketball_as)
				{
					throw_count = 0;
					COLOR = RED;
					basketball--;
					Basketball* blt = new Basketball(pos.col - 55, pos.row + 20, 1, basketball_atk, DARK_YELLOW, BULLET::BASKETBALL, c - 1);
					UI_Game::blist.addBullet(blt);
#ifdef DEBUG
					//setCursorPos(59, 30);
					//printf("%02d", basketball);
#endif
				}
				else
					throw_count++;
				return 1;
			}
			else if (plant)
			{
				if (status == 0)
				{
					status = 1;
					changeMovie("Resource/images/Zombies/BasketballZombie/BasketballZombieAttack.gif");
				}
				COLOR = GREY;
				return 0;
			}
			else
				return 1;
		}
	}
	else
	{
		if (color_count >= COLOR_TIME)
		{
			COLOR = slowed ? CYAN : _ZOMBIE_COLOR[(int)ZOMBIE_ID];
		}
	}
	return 0;
}
