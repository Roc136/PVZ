#include "include.h"
#include <math.h>

extern int _COST[]; // 植物花费
extern const char* _PLANT_NAME[]; //植物名字

PlantSelector::PlantSelector()
{
	pid = 0;
}

PlantSelector::~PlantSelector()
{
	reinit();
}

void PlantSelector::reinit()
{
	pid = 0;
}

void PlantSelector::move(int direction)
{
	switch (direction)
	{
	case UP:
		pid = (pid + (PLANT_KIND_NUM / 4 + 1) * 4 - 4) % ((PLANT_KIND_NUM / 4 + 1) * 4);
		while (pid < 0) pid++;
		break;
	case LEFT:
		pid = (pid + PLANT_KIND_NUM - 1) % PLANT_KIND_NUM;
		break;
	case RIGHT:
		pid = (pid + 1) % PLANT_KIND_NUM;
		break;
	case DOWN:
		pid = (pid + 4) % ((PLANT_KIND_NUM / 4 + 1) * 4);
		while (pid >= PLANT_KIND_NUM) pid--;
		break;
	}
}

void PlantSelector::setPant(int pid)
{
	if(pid >= 0 && pid < PLANT_KIND_NUM)
		this->pid = pid;
	else
	{
		//showMessage("植物ID错误！");
		exit(-1);
	}
}

int PlantSelector::getPlant() const
{
	return pid;
}

MapSelector::MapSelector() :pos(0, 0) {}

MapSelector::~MapSelector()
{
	reinit();
}

void MapSelector::reinit()
{
	pos.row = 0;
	pos.col = 0;
}

void MapSelector::move(int direction)
{
	//fixShop();
	switch (direction)
	{
	case UP:
		pos.row = (pos.row + ROW - 1) % ROW;
		break;
	case LEFT:
		pos.col = (pos.col + COL - 1) % COL;
		break;
	case RIGHT:
		pos.col = (pos.col + 1) % COL;
		break;
	case DOWN:
		pos.row = (pos.row + 1) % ROW;
		break;
	}
}

Pos MapSelector::getPos() const
{
	return pos;
}

int Shop::buyPlant(int sure)
{
	int success = 0;
	int pid = ps.getPlant();
	int need_sun = _COST[pid];
	if (wait_time[pid] > 0)
		return -1;
	if (UI_Game::getSunlight() >= need_sun)
	{
		Pos pos = ms.getPos();
		success = 1;
		UI_Game::useSunlight(need_sun);
		switch (pid)
		{
		case 0:
		{
			Sunflower* p = new Sunflower(pos.row, pos.col);
			if (!UI_Game::plist.addPlant(p, sure))
			{
				success = 0;
				status = 2;
			}
			break;
		}
		case 1:
		{
			PeaShooter* p = new PeaShooter(pos.row, pos.col);
			if (!UI_Game::plist.addPlant(p, sure))
			{
				success = 0;
				status = 2;
			}
			break;
		}
		case 2:
		{
			DoubleShooter* p = new DoubleShooter(pos.row, pos.col);
			if (!UI_Game::plist.addPlant(p, sure))
			{
				success = 0;
				status = 2;
			}
			break;
		}
		case 3:
		{
			IceShooter* p = new IceShooter(pos.row, pos.col);
			if (!UI_Game::plist.addPlant(p, sure))
			{
				success = 0;
				status = 2;
			}
			break;
		}
		case 5:
		{
			Nut* p = new Nut(pos.row, pos.col);
			if (!UI_Game::plist.addPlant(p, sure))
			{
				success = 0;
				status = 2;
			}
			break;
		}
		case 6:
		{
			HighNut* p = new HighNut(pos.row, pos.col);
			if (!UI_Game::plist.addPlant(p, sure))
			{
				success = 0;
				status = 2;
			}
			break;
		}
		case 10:
		{
			Pumpkin* p = new Pumpkin(pos.row, pos.col);
			if (!UI_Game::plist.addPlant(p, sure))
			{
				success = 0;
				status = 2;
			}
			break;
		}
		case 9:
		{
			Garlic* p = new Garlic(pos.row, pos.col);
			if (!UI_Game::plist.addPlant(p, sure))
			{
				success = 0;
				status = 2;
			}
			break;
		}
		case 4:
		{
			Potato* p = new Potato(pos.row, pos.col);
			if (!UI_Game::plist.addPlant(p, sure))
			{
				success = 0;
				status = 2;
			}
			break;
		}
		case 7:
		{
			Squash* p = new Squash(pos.row, pos.col);
			if (!UI_Game::plist.addPlant(p, sure))
			{
				success = 0;
				status = 2;
			}
			break;
		}
		case 8:
		{
			Cherry* p = new Cherry(pos.row, pos.col);
			if (!UI_Game::plist.addPlant(p, sure))
			{
				success = 0;
				status = 2;
			}
			break;
		}
		default:
			success = -2;	
		}
		if(success == 1)
			wait_time[pid] = _WAIT[pid];
	}
	return success;
}

void Shop::reinit(int regame)
{
	status = 0;
	delete[] wait_time;
	ps.reinit();
	ms.reinit();
	if(regame)
		wait_time = new int[PLANT_KIND_NUM]();
}

Shop::Shop() :status(0) 
{
	wait_time = new int[PLANT_KIND_NUM]();
}

Shop::~Shop()
{
	reinit(0);
}

void Shop::choosePlant()
{
	const char* name = _PLANT_NAME[ps.getPlant()];
	char msg[64] = "选中植物";
	int i = 0;
	for (i = 0; name[i] != 0; i++)
		msg[8 + i] = name[i];
	//showMessage(msg);
	status = 1;
}

void Shop::unchoosePlant()
{
	status = 0;
	//fixShop();
}

void Shop::shopOperate(int key)
{
	if (status == 0)
	{
		switch (key)
		{
		case UP:case DOWN:case LEFT:case RIGHT:
			ps.move(key);
			break;
		case ENTER:
			choosePlant();
			break;
		case NUM1:case NUM2:case NUM3:case NUM4:case NUM5:case NUM6:case NUM7:case NUM8:case NUM9:
			ps.setPant(key - NUM0 - 1);
			choosePlant();
			break;
		case KB_A:case KB_B:
			ps.setPant(key - KB_A + 9);
			choosePlant();
			break;
		case KB_a:case KB_b:
			ps.setPant(key - KB_a + 9);
			choosePlant();
			break;
		default:;
		}
	}
	else if(status == 1)
	{
		switch (key)
		{
		case UP:case DOWN:case LEFT:case RIGHT:
			ms.move(key);
			break;
		case ENTER:
		{
			int success = buyPlant(0);
			if (success == 0)
			{
				if (status == 2)
				{
					UI_Game::addSunlight(_COST[ps.getPlant()]);
					//showMessage("当前位置已有植物！");
				}
				else
				{
					status = 0;
					//showMessage("阳光不足！");
					//fixShop();
				}
			}
			else if (success == 1)
			{
				const char* name = _PLANT_NAME[ps.getPlant()];
				char msg[64] = "成功种植";
				int i = 0;
				for (i = 0; name[i] != 0; i++)
					msg[8 + i] = name[i];
				msg[8 + i] = '!';
				//showMessage(msg);
				unchoosePlant();
			}
			else if (success == -1)
			{
				status = 0;
				//showMessage("植物还在冷却！");
				//fixShop();
			}
			else if (success == -2)
			{
				status = 0;
				//showMessage("没有这种植物！");s
				//fixShop();
			}
			break;
		}
		case ESC:
			//showMessage("取消选择");
			unchoosePlant();
			break;
		default:;
		}
	}
	else if (status == 2)
	{
		switch (key)
		{
		case ENTER:
		{
			int success = buyPlant(1);
			if (success == 0)
			{
				if (status == 2)
				{
					UI_Game::addSunlight(_COST[ps.getPlant()]);
					//showMessage("当前位置已有植物！");
				}
				else
				{
					status = 0;
					//showMessage("阳光不足！");
					//fixShop();
				}
			}
			else if (success == 1)
			{
				const char* name = _PLANT_NAME[ps.getPlant()];
				char msg[64] = "成功种植";
				int i = 0;
				for (i = 0; name[i] != 0; i++)
					msg[8 + i] = name[i];
				msg[8 + i] = '!';
				//showMessage(msg);
				unchoosePlant();
			}
			else if (success == -1)
			{
				status = 0;
				//showMessage("植物还在冷却！");
				//fixShop();
			}
			else if (success == -2)
			{
				status = 0;
				//showMessage("没有这种植物！");
				//fixShop();
			}
			break;
		}
		case UP: case DOWN: case LEFT: case RIGHT:
			//fixShop();
			choosePlant();
			ms.move(key);
			break;
		case ESC:
			//showMessage("取消选择");
			unchoosePlant();
			break;
		}
	}
}

void Shop::wait()
{
	for (int i = 0; i < PLANT_KIND_NUM; i++)
		if (wait_time[i] > 0)
			wait_time[i]--;
}
