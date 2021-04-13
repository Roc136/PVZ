#include "include.h"
#include <math.h>

extern int _COST[]; // 植物花费
extern const char* _PLANT_NAME[]; //植物名字

PlantSelector::PlantSelector()
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
	default:;
	}
}

void PlantSelector::setPant(int pid)
{
	this->pid = pid;
}

int PlantSelector::getPlant() const
{
	return pid;
}

MapSelector::MapSelector() :pos(0, 0) {}

void MapSelector::move(int direction)
{
	fixShop();
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
	default:;
	}
}

Pos MapSelector::getPos() const
{
	return pos;
}

bool Shop::buyPlant(int sure)
{
	int success = 0;
	int pid = ps.getPlant();
	int need_sun = _COST[pid];
	if (sunlight >= need_sun)
	{
		Pos pos = ms.getPos();
		success = 1;
		sunlight -= need_sun;
		switch (pid)
		{
		case 0:
		{
			Sunflower* p = new Sunflower(pos.row, pos.col);
			if (!plist.addPlant(p, sure))
			{
				success = 0;
				status = 2;
			}
			break;
		}
		case 1:
		{
			PeaShooter* p = new PeaShooter(pos.row, pos.col);
			if (!plist.addPlant(p, sure))
			{
				success = 0;
				status = 2;
			}
			break;
		}
		case 2:
		{
			DoubleShooter* p = new DoubleShooter(pos.row, pos.col);
			if (!plist.addPlant(p, sure))
			{
				success = 0;
				status = 2;
			}
			break;
		}
		case 3:
		{
			Nut* p = new Nut(pos.row, pos.col);
			if (!plist.addPlant(p, sure))
			{
				success = 0;
				status = 2;
			}
			break;
		}
		case 4:
		{
			Potato* p = new Potato(pos.row, pos.col);
			if (!plist.addPlant(p, sure))
			{
				success = 0;
				status = 2;
			}
			break;
		}
		default:
			success = 0;
		}
	}
	return success;
}

void Shop::choosePlant()
{
	status = 1;
}

void Shop::unchoosePlant()
{
	status = 0;
	fixShop();
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
		case NUM1:case NUM2:case NUM3:case NUM4:case NUM5:
			ps.setPant(key - NUM0 - 1);
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
			if (!buyPlant(0))
			{
				if (status == 2)
				{
					sunlight += _COST[ps.getPlant()];
					showMessage("当前位置已有植物！");
				}
				else
				{
					status = 0;
					showMessage("阳光不足！");
					fixShop();
				}
			}
			else
			{
				const char* name = _PLANT_NAME[ps.getPlant()];
				char msg[64] = "成功种植";
				int i = 0;
				for (i = 0; name[i] != 0; i++)
					msg[8 + i] = name[i];
				msg[8 + i] = '!';
				showMessage(msg);
				unchoosePlant();
			}
			break;
		case ESC:
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
			buyPlant(1);
			const char* name = _PLANT_NAME[ps.getPlant()];
			char msg[64] = "成功种植";
			int i = 0;
			for (i = 0; name[i] != 0; i++)
				msg[8 + i] = name[i];
			msg[8 + i] = '!';
			showMessage(msg);
			unchoosePlant();
			break;
		}
		case UP: case DOWN: case LEFT: case RIGHT:
			fixShop();
			choosePlant();
			ms.move(key);
			break;
		case ESC:
			unchoosePlant();
			break;
		default:;
		}
	}
}
