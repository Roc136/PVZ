#include "include.h"
#include <stdio.h>
#include <string.h>
#include <math.h> 
using namespace std;

extern const char* _PLANT_NAME[]; // 植物名字
extern const char* _ZOMBIE_NAME[]; // 僵尸名字
extern int _COST[];

void showMap()
{
	setCursorPos(0, 0);
	printf("+");
	for (int i = 0; i < COL * (COL_WIDTH + 1) - 1; i++)
		printf("-");
	printf("+\n");
	for (int i = 0; i < TOP_HIGH - 1; i++)
	{
		printf("|");
		setCursorPos(WINDOWS_WIDTH - 2, i + 1);
		printf("|\n");
	}
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			printf("+");
			for (int k = 0; k < COL_WIDTH; k++)
				printf("-");
		}
		printf("+\n");
		int x = 0, y = i * (ROW_HIGH + 1) + TOP_HIGH + 1;
		for (int j = 0; j < ROW_HIGH; j++)
		{
			for (int k = 0; k <= COL; k++)
			{
				setCursorPos(x, y);
				printf("|");
				x += COL_WIDTH + 1;
			}
			printf(" ");
			y++;
			x = 0;
		}
	}
	for (int j = 0; j < COL; j++)
	{
		printf("+");
		for (int k = 0; k < COL_WIDTH; k++)
			printf("-");
	}
	printf("+");
	setCursorPos(0, TOP_HIGH + ROW * (ROW_HIGH + 1) + 1);
	for (int i = 0; i < BOTTOM_HIGH - 1; i++)
	{
		printf("|");
		setCursorPos(WINDOWS_WIDTH - 2, i + 1 + TOP_HIGH + ROW * (ROW_HIGH + 1));
		printf("|\n");
	}
	setCursorPos(0, TOP_HIGH + ROW * (ROW_HIGH + 1) + BOTTOM_HIGH);
	printf("+");
	for (int j = 0; j < COL_WIDTH; j++)
		printf("-");
	for (int j = 0; j < COL - 1; j++)
	{
		printf("+");
		for (int k = 0; k < COL_WIDTH; k++)
			printf("-");
	}
	printf("+");
}

void showInfo()
{
	setCursorPos(2, 1);
	printf("阳光：%05d", sunlight);
	setCursorPos(49, 1);
	printf("等级：%d", level);
	setCursorPos(92, 1);
	printf("得分：%05d", score);
}

void showMessage(const char* message)
{
	setCursorPos(1, MESSAGE_LINE);
	for (int i = 0; i < WINDOWS_WIDTH - 3; i++)
		printf(" ");
	if (strlen(message) > WINDOWS_WIDTH)
	{
		printf("Message too long");
		exit(-1);
	}
	int left = (WINDOWS_WIDTH - strlen(message)) / 2;
	setCursorPos(left, MESSAGE_LINE);
	setColor(RED);
	printf("%s", message);
	setColor();
}

void showPlant(const Plant& plant)
{
	int map_left = plant.pos.col * (COL_WIDTH + 1);
	int map_top = plant.pos.row * (ROW_HIGH + 1) + TOP_HIGH;

	const char* name = _PLANT_NAME[(int)plant.PLANT_ID];
	int name_left = (COL_WIDTH - strlen(name)) / 2 + 1;
	if (plant.getID() == PLANT::PUMPKIN)
		setCursorPos(map_left + name_left, map_top + ROW_HIGH - 1);
	else
		setCursorPos(map_left + name_left, map_top + ROW_HIGH - 2);
	setColor(WHITE, plant.COLOR);
	printf("%s", name);

	if (plant.getID() == PLANT::PUMPKIN)
	{
		setColor(WHITE, plant.COLOR);
		for (int i = 0; i < ROW_HIGH - 1; i++)
		{
			setCursorPos(map_left + 1, map_top + 1 + i);
			printf("#");
			setCursorPos(map_left + COL_WIDTH, map_top + 1 + i);
			printf("#");
		}
		setCursorPos(map_left + 1, map_top + ROW_HIGH);
		for (int i = 0; i < COL_WIDTH; i++)
			printf("#");
	}

	if (plant.getID() == PLANT::PUMPKIN)
		setCursorPos(map_left + 2, map_top + 1);
	else
		setCursorPos(map_left + 2, map_top + 2);
	float cur_hp_percentage = (float)plant.current_hp / (float)plant.FULL_HP;
	int cur_hp = (int)(cur_hp_percentage * 10);
	char hp_info[13] = "HP:   .  %";
	char buffer[64];
	int ret = snprintf(buffer, sizeof buffer, "%f", cur_hp_percentage);
	if (ret < 0) {
		exit(-1);
	}
	if (buffer[0] == '1')
		hp_info[3] = buffer[0];
	hp_info[4] = buffer[2]; hp_info[5] = buffer[3]; hp_info[7] = buffer[4]; hp_info[8] = buffer[5];
	int hp_color = (plant.getID() == PLANT::PUMPKIN) ? YELLOW : WHITE;
	if (cur_hp <= 3)
		hp_color = RED;
	setColor(BLACK, hp_color);
	for (int i = 0; i < 10; i++)
	{
		printf("%c", hp_info[i]);
		if (i == cur_hp)
			setColor(hp_color, BLACK);
	}
	setColor();
}

void fixPlant(const Plant& plant)
{
	int map_left = plant.pos.col * (COL_WIDTH + 1);
	int map_top = plant.pos.row * (ROW_HIGH + 1) + TOP_HIGH;

	for (int i = 0; i < ROW_HIGH; i++)
	{
		setCursorPos(map_left + 1, map_top + i + 1);
		for (int j = 0; j < COL_WIDTH; j++)
			printf(" ");
	}
}

void showBullet(const Bullet& blt)
{
	if (blt.getID() == BULLET::BASKETBALL)
	{
		setCursorPos(blt.pos_x + 2, blt.pos_y);
		if ((blt.pos_x + 2) % (COL_WIDTH + 1) == 0)
		{
			printf("|");
		}
		else
		{
			printf(" ");
		}
	}
	else
	{
		setCursorPos(blt.pos_x - 1, blt.pos_y);
		if (blt.pos_x % (COL_WIDTH + 1) == 1)
		{
			printf("|");
		}
		else
		{
			printf(" ");
		}
	}
	setCursorPos(blt.pos_x, blt.pos_y);
	setColor(blt.color);
	printf("●");
	setColor();

	//setCursorPos(20, 20);
	//cout << blt.pos_x << " " << blt.pos_y;
}

void fixBullet(const Bullet& blt)
{
	if (blt.getID() == BULLET::BASKETBALL)
	{
		setCursorPos(blt.pos_x, blt.pos_y);
		if (blt.pos_x % (COL_WIDTH + 1) == COL_WIDTH - 1)
		{
			printf("|  ");
		}
		else if (blt.pos_x % (COL_WIDTH + 1) == COL_WIDTH - 2)
		{
			printf(" | ");
		}
		else if (blt.pos_x % (COL_WIDTH + 1) == COL_WIDTH - 3)
		{
			printf("  |");
		}
		else
		{
			printf("   ");
		}
	}
	else
	{
		setCursorPos(blt.pos_x - 1, blt.pos_y);
		if (blt.pos_x % (COL_WIDTH + 1) == 0)
		{
			printf(" |");
		}
		else if (blt.pos_x % (COL_WIDTH + 1) == 1)
		{
			printf("| ");
		}
		else
		{
			printf("  ");
		}
	}
}

void showZombie(const Zombie& zombie)
{
	int map_left = zombie.pos.col;
	int map_top = zombie.pos.row;

	const char* name = _ZOMBIE_NAME[(int)zombie.ZOMBIE_ID];
	int name_len = strlen(name);
	int name_left = (10 - name_len) / 2 + 1;

	setCursorPos(map_left + 11, map_top + 2);
	if ((map_left + 11) % (COL_WIDTH + 1) == 0)
	{
		if ((map_top - TOP_HIGH + 2) % (ROW_HIGH + 1) == 0)
			printf("+");
		else
			printf("|");
	}
	else
	{
		if ((map_top - TOP_HIGH + 2) % (ROW_HIGH + 1) == 0)
			printf("-");
		else
			printf(" ");
	}
	setCursorPos(map_left + name_left + name_len, map_top + 3);
	if ((map_left + name_left + name_len) % (COL_WIDTH + 1) == 0)
	{
		if ((map_top - TOP_HIGH + 3) % (ROW_HIGH + 1) == 0)
			printf("+");
		else
			printf("|");
	}
	else
	{
		if ((map_top - TOP_HIGH + 3) % (ROW_HIGH + 1) == 0)
			printf("-");
		else
			printf(" ");
	}

	setCursorPos(map_left + name_left, map_top + 3);
	setColor(BLACK, zombie.COLOR);
	printf("%s", name);

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
		printf("%c", hp_info[i]);
		if (i == cur_hp)
			setColor(hp_color, BLACK);
	}
	setColor();
}

void fixZombie(const Zombie& zombie)
{
	int map_left = zombie.pos.col;
	int map_top = zombie.pos.row;
	for (int j = 2; j <= 3; j++)
	{
		setCursorPos(map_left + 1, map_top + j);
		for (int i = 0; i < 10; i++)
		{
			if ((map_top - TOP_HIGH + j) % (ROW_HIGH + 1) == 0)
			{
				if ((map_left + 1 + i) % (COL_WIDTH + 1) == 0)
					printf("+");
				else
					printf("-");
			}
			else
			{
				if ((map_left + 1 + i) % (COL_WIDTH + 1) == 0)
					printf("|");
				else
					printf(" ");
			}
		}
	}
}

void showShop()
{
	for (int i = 0; i < PLANT_KIND_NUM; i++)
	{
		const char* name = _PLANT_NAME[i];
		int color = shop.ps.getPlant() == i ? (shop.status == 0 ? YELLOW : RED) : WHITE;
		setCursorPos((i % 4) * (WINDOWS_WIDTH - 3) / 4 + 1, WINDOWS_HIGH - BOTTOM_HIGH + (i / 4) * 2);
		setColor(BLACK, color);
		char buffer[64];
		int ret = snprintf(buffer, sizeof buffer, "%c. %s $%03d", (char)(i >= 9 ? ('A' + i - 9) : '0' + i + 1), name, _COST[i]);
		if (ret < 0) {
			exit(-1);
		}
		float cur_wt_percentage = (float)shop.wait_time[i] / (float)_WAIT[i];
		int cur_wt = (int)ceil(cur_wt_percentage * 16);
		for (int i = 0; buffer[i] != 0; i++)
		{
			if (i == 16 - cur_wt)
				setColor(BLACK, GREY);
			printf("%c", buffer[i]);
		}
#ifdef DEBUG
		setColor();
		printf(" %03d", shop.wait_time[i]);
#endif
		setColor();
	}
	if (shop.status == 1)
	{
		Pos p = shop.ms.getPos();
		Plant* ps = plist.getPlant(p.row, p.col);
		if (ps)
		{
			if ((ps->getID() != PLANT::PUMPKIN && shop.ps.getPlant() == (int)PLANT::PUMPKIN))
				setColor(GREEN);
			else
				setColor(RED);
		}
		else
			setColor(GREEN);
		int block_left = p.col * (COL_WIDTH + 1);
		int block_top = p.row * (ROW_HIGH + 1) + TOP_HIGH;
		setCursorPos(block_left, block_top);
		printf("+");
		for (int i = 0; i < COL_WIDTH; i++)
			printf("-");
		printf("+");
		for (int i = 0; i < ROW_HIGH; i++)
		{
			setCursorPos(block_left, block_top + i + 1);
			printf("|");
			setCursorPos(block_left + COL_WIDTH + 1, block_top + i + 1);
			printf("|");
		}
		setCursorPos(block_left, block_top + ROW_HIGH + 1);
		printf("+");
		for (int i = 0; i < COL_WIDTH; i++)
			printf("-");
		printf("+");
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
	printf("+");
	for (int i = 0; i < COL_WIDTH; i++)
		printf("-");
	printf("+");
	for (int i = 0; i < ROW_HIGH; i++)
	{
		setCursorPos(block_left, block_top + i + 1);
		printf("|");
		setCursorPos(block_left + COL_WIDTH + 1, block_top + i + 1);
		printf("|");
	}
	setCursorPos(block_left, block_top + ROW_HIGH + 1);
	printf("+");
	for (int i = 0; i < COL_WIDTH; i++)
		printf("-");
	printf("+");
}

void showBoom(int r, int c, int size, int color)
{
	setColor(color);
	for (int i = r - size; i <= r + size; i++)
		if (i >= 0 && i < ROW)
			for (int j = c - size; j <= c + size; j++)
				if (j >= 0 && j < COL)
				{
					int map_left = j * (COL_WIDTH + 1);
					int map_top = i * (ROW_HIGH + 1) + TOP_HIGH;
					setCursorPos(map_left + 1, map_top + 1);
					for (int k = 0; k < COL_WIDTH; k++)
						printf("#");
					for (int k = 0; k < ROW_HIGH - 2; k++)
					{
						setCursorPos(map_left + 1, map_top + k + 2);
						printf("#");
						setCursorPos(map_left + COL_WIDTH, map_top + k + 2);
						printf("#");
					}
					setCursorPos(map_left + 1, map_top + ROW_HIGH);
					for (int k = 0; k < COL_WIDTH; k++)
						printf("#");
				}
	setColor();
}

void fixBoom(int r, int c, int size)
{
	for (int i = r - size; i <= r + size; i++)
		if (i >= 0 && i < ROW)
			for (int j = c - size; j <= c + size; j++)
				if (j >= 0 && j < COL)
				{
					int map_left = j * (COL_WIDTH + 1);
					int map_top = i * (ROW_HIGH + 1) + TOP_HIGH;
					setCursorPos(map_left + 1, map_top + 1);
					for (int k = 0; k < COL_WIDTH; k++)
						printf(" ");
					for (int k = 0; k < ROW_HIGH - 2; k++)
					{
						setCursorPos(map_left + 1, map_top + k + 2);
						printf(" ");
						setCursorPos(map_left + COL_WIDTH, map_top + k + 2);
						printf(" ");
					}
					setCursorPos(map_left + 1, map_top + ROW_HIGH);
					for (int k = 0; k < COL_WIDTH; k++)
						printf(" ");
				}
}
