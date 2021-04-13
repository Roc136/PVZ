#include "include.h"
#include <stdio.h>
#include <string.h>
using namespace std;

extern const char* _PLANT_NAME[]; // 植物名字
extern const char* _ZOMBIE_NAME[]; // 僵尸名字
extern int _COST[];

void showMap()
{
	setCursorPos(0, 0);
	cout << "+";
	for (int i = 0; i < COL * (COL_WIDTH + 1) - 1; i++)
		cout << "-";
	cout << "+" << endl;
	for (int i = 0; i < TOP_HIGH - 1; i++)
	{
		cout << "|";
		setCursorPos(WINDOWS_WIDTH - 2, i + 1);
		cout << "| ";
	}
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
			cout << "+----------";
		cout << "+" << endl;
		int x = 0, y = i * (ROW_HIGH + 1) + TOP_HIGH + 1;
		for (int j = 0; j < ROW_HIGH; j++)
		{
			for (int k = 0; k <= COL; k++)
			{
				setCursorPos(x, y);
				cout << "|";
				x += COL_WIDTH + 1;
			}
			cout << " ";
			y++;
			x = 0;
		}
	}
	for (int j = 0; j < COL; j++)
		cout << "+----------";
	cout << "+";
	setCursorPos(0, TOP_HIGH + ROW * (ROW_HIGH + 1) + 1);
	for (int i = 0; i < BOTTOM_HIGH - 1; i++)
	{
		cout << "|";
		setCursorPos(WINDOWS_WIDTH - 2, i + 1 + TOP_HIGH + ROW * (ROW_HIGH + 1));
		cout << "| ";
	}
	setCursorPos(0, TOP_HIGH + ROW * (ROW_HIGH + 1) + BOTTOM_HIGH);
	cout << "+----------";
	for (int j = 0; j < COL - 1; j++)
		cout << "-----------";
	cout << "+";
}

void showInfo()
{
	setCursorPos(2, 1);
	cout << "阳光：" << setw(5) << setfill('0') << sunlight;
	setCursorPos(41, 1);
	cout << "等级：" << level;
	setCursorPos(76, 1);
	cout << "得分：" << setw(5) << setfill('0') << score;
}

void showMessage(const char* message)
{
	setCursorPos(1, MESSAGE_LINE);
	for (int i = 0; i < WINDOWS_WIDTH - 3; i++)
		cout << " ";
	if (strlen(message) > WINDOWS_WIDTH)
	{
		cout << "message too long";
		exit(-1);
	}
	int left = (WINDOWS_WIDTH - strlen(message)) / 2;
	setCursorPos(left, MESSAGE_LINE);
	setColor(RED);
	cout << message;
	setColor();
}

void showPlant(const Plant& plant)
{
	int map_left = plant.pos.col * (COL_WIDTH + 1);
	int map_top = plant.pos.row * (ROW_HIGH + 1) + TOP_HIGH;

	const char* name = _PLANT_NAME[(int)plant.PLANT_ID];
	int name_left = (COL_WIDTH - strlen(name)) / 2 + 1;
	setCursorPos(map_left + name_left, map_top + 3);
	setColor(WHITE, plant.COLOR);
	cout << name;

	setCursorPos(map_left + 1, map_top + 2);
	float cur_hp_percentage = (float)plant.current_hp / (float)plant.FULL_HP;
	int cur_hp = (int)(cur_hp_percentage * 10);
	char hp_info[11] = "HP:   .  %";
	char buffer[64];
	int ret = snprintf(buffer, sizeof buffer, "%f", cur_hp_percentage);
	if (ret < 0) {
		exit(-1);
	}
	if (buffer[0] == '1')
		hp_info[3] = buffer[0];
	hp_info[4] = buffer[2]; hp_info[5] = buffer[3]; hp_info[7] = buffer[4]; hp_info[8] = buffer[5];
	int hp_color = WHITE;
	if (cur_hp <= 3)
		hp_color = RED;
	setColor(BLACK, hp_color);
	for (int i = 0; i < 10; i++)
	{
		cout << hp_info[i];
		if (i == cur_hp)
			setColor(hp_color, BLACK);
	}
	setColor();
}

void fixPlant(const Plant& plant)
{
	int map_left = plant.pos.col * (COL_WIDTH + 1);
	int map_top = plant.pos.row * (ROW_HIGH + 1) + TOP_HIGH;

	setCursorPos(map_left + 1, map_top + 3);
	cout << "          ";
	setCursorPos(map_left + 1, map_top + 2);
	cout << "          ";
}

void showBullet(const Bullet& blt)
{
	setCursorPos(blt.pos_x - 1, blt.pos_y);
	if (blt.pos_x % (COL_WIDTH + 1) == 1)
	{
		cout << "|";
	}
	else
	{
		cout << " ";
	}
	setCursorPos(blt.pos_x, blt.pos_y);
	setColor(blt.color);
	cout << "●";
	setColor();

	//setCursorPos(20, 20);
	//cout << blt.pos_x << " " << blt.pos_y;
}

void fixBullet(const Bullet& blt)
{
	setCursorPos(blt.pos_x - 1, blt.pos_y);
	if (blt.pos_x % (COL_WIDTH + 1) == 0)
	{
		cout << " |";
	}
	else if (blt.pos_x % (COL_WIDTH + 1) == 1)
	{
		cout << "| ";
	}
	else
	{
		cout << "  ";
	}
}

void showZombie(const Zombie& zombie)
{
	int map_left = zombie.pos.col;
	int map_top = zombie.pos.row;

	const char* name = _ZOMBIE_NAME[(int)zombie.ZOMBIE_ID];
	int name_len = strlen(name);
	int name_left = (COL_WIDTH - name_len) / 2 + 1;

	setCursorPos(map_left + COL_WIDTH + 1, map_top + 2);
	if (map_left % (COL_WIDTH + 1) == 0)
	{
		cout << "|";
	}
	else
	{
		cout << " ";
	}
	setCursorPos(map_left + name_left + name_len, map_top + 3);
	if ((map_left + name_left + name_len) % (COL_WIDTH + 1) == 0)
	{
		cout << "|";
	}
	else
	{
		cout << " ";
	}

	setCursorPos(map_left + name_left, map_top + 3);
	setColor(BLACK, zombie.COLOR);
	cout << name;

	setCursorPos(map_left + 1, map_top + 2);
	float cur_hp_percentage = (float)zombie.current_hp / (float)zombie.FULL_HP;
	int cur_hp = (int)(cur_hp_percentage * 10);
	char hp_info[11] = "HP:   .  %";
	char buffer[64];
	int ret = snprintf(buffer, sizeof buffer, "%f", cur_hp_percentage);
	if (ret < 0) {
		exit(-1);
	}
	if (buffer[0] == '1')
		hp_info[3] = buffer[0];
	hp_info[4] = buffer[2]; hp_info[5] = buffer[3]; hp_info[7] = buffer[4]; hp_info[8] = buffer[5];
	int hp_color = WHITE;
	if (cur_hp <= 3)
		hp_color = RED;
	setColor(BLACK, hp_color);
	for (int i = 0; i < 10; i++)
	{
		cout << hp_info[i];
		if (i == cur_hp)
			setColor(hp_color, BLACK);
	}
	setColor();
}

void fixZombie(const Zombie& zombie)
{
	int map_left = zombie.pos.col;
	int map_top = zombie.pos.row;
	setCursorPos(map_left + 1, map_top + 2);
	for (int i = 0; i < 10; i++)
	{
		if ((map_left + 1 + i) % (COL_WIDTH + 1) == 0)
			cout << "|";
		else
			cout << " ";
	}
	setCursorPos(map_left + 1, map_top + 3);
	for (int i = 0; i < 10; i++)
	{
		if ((map_left + 1 + i) % (COL_WIDTH + 1) == 0)
			cout << "|";
		else
			cout << " ";
	}
}

void showShop()
{
	for (int i = 0; i < PLANT_KIND_NUM; i++)
	{
		const char* name = _PLANT_NAME[i];
		int color = shop.ps.getPlant() == i && shop.status == 0 ? YELLOW : WHITE;
		setCursorPos((i % 4) * 22 + 1, WINDOWS_HIGH - BOTTOM_HIGH + (i / 4) * 2);
		setColor(BLACK, color);
		cout << (i >= 9 ? 'A' + i - 9 : i + 1) << ". " << name << " $" << _COST[i];
		setColor();
	}
	if (shop.status == 1)
	{
		Pos p = shop.ms.getPos();
		if (plist.getPlant(p.row, p.col))
			setColor(RED);
		else
			setColor(GREEN);
		int block_left = p.col * (COL_WIDTH + 1);
		int block_top = p.row * (ROW_HIGH + 1) + TOP_HIGH;
		setCursorPos(block_left, block_top);
		cout << "+";
		for (int i = 0; i < COL_WIDTH; i++)
			cout << "-";
		cout << "+";
		for (int i = 0; i < ROW_HIGH; i++)
		{
			setCursorPos(block_left, block_top + i + 1);
			cout << "|";
			setCursorPos(block_left + COL_WIDTH + 1, block_top + i + 1);
			cout << "|";
		}
		setCursorPos(block_left, block_top + ROW_HIGH + 1);
		cout << "+";
		for (int i = 0; i < COL_WIDTH; i++)
			cout << "-";
		cout << "+";
	}
	setCursorPos(1, WINDOWS_HIGH - 2);
	setColor(WHITE, GREY);
	cout << std::left;
	switch (shop.status)
	{
	case 0:
		cout << setw(WINDOWS_WIDTH - 3) << setfill(' ') << "Tips: 按上下左右或植物前编号选择植物";
		break;
	case 1:
		cout << setw(WINDOWS_WIDTH - 3) << setfill(' ') << "Tips: 按上下左右移动绿色框选择种植位置";
		break;
	case 2:
		cout << setw(WINDOWS_WIDTH - 3) << setfill(' ') << "Tips: 按回车确认覆盖,按 Esc 取消种植，按上下左右重新选择位置";
		break;
	default:;
	}
	cout << std::right;
	setColor();
	//setCursorPos(30, 30);
	//cout << shop.status;
	return;
}

void fixShop()
{
	setColor();
	Pos p = shop.ms.getPos();
	int block_left = p.col * (COL_WIDTH + 1);
	int block_top = p.row * (ROW_HIGH + 1) + TOP_HIGH;
	setCursorPos(block_left, block_top);
	cout << "+";
	for (int i = 0; i < COL_WIDTH; i++)
		cout << "-";
	cout << "+";
	for (int i = 0; i < ROW_HIGH; i++)
	{
		setCursorPos(block_left, block_top + i + 1);
		cout << "|";
		setCursorPos(block_left + COL_WIDTH + 1, block_top + i + 1);
		cout << "|";
	}
	setCursorPos(block_left, block_top + ROW_HIGH + 1);
	cout << "+";
	for (int i = 0; i < COL_WIDTH; i++)
		cout << "-";
	cout << "+";
}