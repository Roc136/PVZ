#include "include.h"
#include <math.h>
#include <qgraphicseffect.h>
#include "UI_Menu.h"

extern int _COST[]; // 植物花费
extern const char* _PLANT_NAME[]; //植物名字
extern const char* _PLANT_PATH[];
static int _WIDTH[] = { 73, 71, 73, 71, 75, 65, 83, 73, 112, 60, 97 };
static int _HIGH[] = { 74, 71, 71, 71, 55, 73, 119, 85, 81, 59, 67 };

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

void PlantSelector::setPlant(int pid)
{
	qDebug() << "Set PSelector" << pid;
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

MapSelector::MapSelector(QWidget* parent) :QWidget(parent), pos(0, 0)
{
	setGeometry(0, 0, 800, 600);
	setStyleSheet("background-image:url();");
	setMouseTracking(true);
}

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

void MapSelector::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		pos.col = (event->x() - LEFT_WIDTH) / COL_WIDTH;
		pos.row = (event->y() - 87) / ROW_HIGH;
		if (event->y() < 87)
		{
			emit unchoose();
		}
		else
		{
			if (pos.col < COL && pos.row < ROW)
				emit planted();
			else
				emit unchoose();
		}
		qDebug() << "Push LeftButton, x-" << event->x() << ", y-" << event->y() << ", ROW-" << pos.row << ", COL-" << pos.col;
	}
	else if (event->button() == Qt::RightButton)
	{
		qDebug() << "Push RightButton!";
		emit unchoose();
	}
}

void MapSelector::mouseMoveEvent(QMouseEvent* event)
{
	//qDebug() << "Mouse move to" << event->x() << event->y();
	emit changePlace(event->pos());
}

void MapSelector::mouseReleaseEvent(QMouseEvent* event)
{
}

void MapSelector::show()
{
	raise();
	QWidget::hide();
	setWindowFlags(Qt::WindowStaysOnTopHint);
	QWidget::show();
	QWidget::hide();
	setWindowFlags(Qt::Widget);
	QWidget::show();
}

void MapSelector::hide()
{
	QWidget::hide();
}

//void MapSelector::contextMenuEvent(QContextMenuEvent* event)
//{
//	printf("clicked right button\n");
//	emit unchoose();
//}

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
				delete p;
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
				delete p;
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
				delete p;
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
				delete p;
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
				delete p;
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
				delete p;
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
				delete p;
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
				delete p;
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
				delete p;
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
				delete p;
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
				delete p;
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
	qDebug() << "Shop reinit with regame valued" << regame;;
	status = 0;
	delete[] wait_time;
	ps.reinit();
	ms.reinit();
	if(regame)
		wait_time = new int[PLANT_KIND_NUM]();
}

Shop::Shop(QWidget* parent, UI_Menu* menu) :status(0), QWidget(parent), ms(UI_Game::bg), menu(menu)
{
	wait_time = new int[PLANT_KIND_NUM]();
	seedbank = new QWidget(parent);
	seedbank->setGeometry(10, 0, 650, 87);
	seedbank->setStyleSheet("background-image:url(Resource/images/interface/SeedBank.png);margin-left:0px; margin-top:0px;");
	char style[256] = "";
	char cost_c[5];
	for (int i = 0; i < 11; i++)
	{
		seedpackets[i] = new QPushButton(seedbank);
		seedpackets[i]->setGeometry(i * 51 + 78, 8, 51, 69);
		seedpackets[i]->setStyleSheet("background-image:url();border-image:url(Resource/images/interface/SeedPacket.png);border:none;");
		QLabel* pic = new QLabel(seedpackets[i]);
		pic->setGeometry(5, 9, 41, 41);
		sprintf(style, "background-image:url();border-image:url(Resource/images/Plants/Card/%s.png);", _PLANT_PATH[i]);
		pic->setStyleSheet(style);
		QLabel* cost = new QLabel(seedpackets[i]);
		cost->setStyleSheet("border-image:url();");
		cost->setGeometry(13, 55, 20, 10);
		cost->setAlignment(Qt::AlignRight);
		sprintf(cost_c, "%d", _COST[i]);
		cost->setText(cost_c);
		connect(seedpackets[i], &(QPushButton::clicked), this, [=](){ choosePlant(i); });

		waiting_shadows[i] = new QLabel(seedpackets[i]);
		waiting_shadows[i]->setGeometry(0, 0, 51, 0);
		waiting_shadows[i]->setStyleSheet("background-image:url();border-image:url();background-color:rgba(0,0,0,80);");
		valid_shawods[i] = new QLabel(seedpackets[i]);
		valid_shawods[i]->setGeometry(0, 0, 51, 69);
		valid_shawods[i]->setStyleSheet("background-image:url();border-image:url();background-color:rgba(0,0,0,100);");
		select_shawods[i] = new QLabel(seedpackets[i]);
		select_shawods[i]->setGeometry(0, 0, 51, 69);
		select_shawods[i]->setStyleSheet("background-image:url();border-image:url();background-color:rgba(0,0,0,150);");

	}
	sunlight = new QLabel(seedbank);
	sunlight->setGeometry(18, 63, 56, 18);
	sunlight->setStyleSheet("background-image:url();");
	for (int i = 0; i < 4; i++)
	{
		numbers[i] = new QLabel(sunlight);
		numbers[i]->setGeometry(i * 9, 0, 14, 18);
	}
	show_numbers(UI_Game::getSunlight());

	connect(&ms, SIGNAL(unchoose()), this, SLOT(unchoosePlant()));
	connect(&ms, SIGNAL(planted()), this, SLOT(buyPlant()));

	tmp_plant = new QLabel(&ms);
	QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect;
	tmp_plant->setGraphicsEffect(opacityEffect);
	opacityEffect->setOpacity(0.7);

	connect(&ms, SIGNAL(changePlace(QPoint)), this, SLOT(changePlace(QPoint)));
}

Shop::~Shop()
{
	reinit(0);
}

void Shop::choosePlant()
{
	qDebug() << "Choose plant " << _PLANT_NAME[ps.getPlant()];
	status = 1;
}

void Shop::unchoosePlant()
{
	if (status == 1 || status == 2)
	{
		qDebug() << "Unchoose Plant";
		status = 0;
		ms.hide();
		tmp_plant->setStyleSheet("background-image:url();");
		tmp_plant->repaint();
	}
}

void Shop::buyPlant()
{
	if (status == 1)
	{
		int success = buyPlant(0);
		if (success == 0)
		{
			if (status == 2)
			{
				UI_Game::addSunlight(_COST[ps.getPlant()]);
				qDebug() << "Already has plant!";
				ms.show();
			}
			else
			{
				status = 0;
				qDebug() << "Not enough sunlight!";
				//fixShop();
			}
		}
		else if (success == 1)
		{
			qDebug() << "Planted PID-" << ps.getPlant();
			unchoosePlant();
		}
		else if (success == -1)
		{
			status = 0;
			qDebug() << "Still waiting..";
		}
		else if (success == -2)
		{
			status = 0;
			qDebug() << "No such plant!";
		}
	}
	else if (status == 2)
	{
		int success = buyPlant(1);
		if (success == 0)
		{
			if (status == 2)
			{
				UI_Game::addSunlight(_COST[ps.getPlant()]);
				qDebug() << "Already has plant!";
			}
			else
			{
				status = 0;
				qDebug() << "Not enough sunlight!";
			}
		}
		else if (success == 1)
		{
			unchoosePlant();
		}
		else if (success == -1)
		{
			status = 0;
			qDebug() << "Still waiting..";
		}
		else if (success == -2)
		{
			status = 0;
			qDebug() << "No such plant!";
		}
	}
}

void Shop::changePlace(QPoint p)
{
	int c = (p.x() - LEFT_WIDTH) / COL_WIDTH;
	int r = (p.y() - 87) / ROW_HIGH;
	if (p.y() < 87)
	{
		tmp_plant->hide();
	}
	else
	{
		if (c < COL && r < ROW)
			tmp_plant->show();
		else
			tmp_plant->hide();
	}
	int pid = ps.getPlant();
	int x = LEFT_WIDTH + (c + 1) * (COL_WIDTH + 1) - _WIDTH[pid];
	int y = TOP_HIGH + (r + 1) * (ROW_HIGH + 1) - _HIGH[pid];
	tmp_plant->setGeometry(x, y, _WIDTH[pid], _HIGH[pid]);
}

//void Shop::shopOperate(int key)
//{
//	if (status == 0)
//	{
//		switch (key)
//		{
//		case UP:case DOWN:case LEFT:case RIGHT:
//			ps.move(key);
//			break;
//		case ENTER:
//			choosePlant();
//			break;
//		case NUM1:case NUM2:case NUM3:case NUM4:case NUM5:case NUM6:case NUM7:case NUM8:case NUM9:
//			ps.setPlant(key - NUM0 - 1);
//			choosePlant();
//			break;
//		case KB_A:case KB_B:
//			ps.setPlant(key - KB_A + 9);
//			choosePlant();
//			break;
//		case KB_a:case KB_b:
//			ps.setPlant(key - KB_a + 9);
//			choosePlant();
//			break;
//		default:;
//		}
//	}
//	else if(status == 1)
//	{
//		switch (key)
//		{
//		case UP:case DOWN:case LEFT:case RIGHT:
//			ms.move(key);
//			break;
//		case ENTER:
//		{
//			int success = buyPlant(0);
//			if (success == 0)
//			{
//				if (status == 2)
//				{
//					UI_Game::addSunlight(_COST[ps.getPlant()]);
//					//showMessage("当前位置已有植物！");
//				}
//				else
//				{
//					status = 0;
//					//showMessage("阳光不足！");
//					//fixShop();
//				}
//			}
//			else if (success == 1)
//			{
//				const char* name = _PLANT_NAME[ps.getPlant()];
//				char msg[64] = "成功种植";
//				int i = 0;
//				for (i = 0; name[i] != 0; i++)
//					msg[8 + i] = name[i];
//				msg[8 + i] = '!';
//				//showMessage(msg);
//				unchoosePlant();
//			}
//			else if (success == -1)
//			{
//				status = 0;
//				//showMessage("植物还在冷却！");
//				//fixShop();
//			}
//			else if (success == -2)
//			{
//				status = 0;
//				//showMessage("没有这种植物！");s
//				//fixShop();
//			}
//			break;
//		}
//		case ESC:
//			//showMessage("取消选择");
//			unchoosePlant();
//			break;
//		default:;
//		}
//	}
//	else if (status == 2)
//	{
//		switch (key)
//		{
//		case ENTER:
//		{
//			int success = buyPlant(1);
//			if (success == 0)
//			{
//				if (status == 2)
//				{
//					UI_Game::addSunlight(_COST[ps.getPlant()]);
//					//showMessage("当前位置已有植物！");
//				}
//				else
//				{
//					status = 0;
//					//showMessage("阳光不足！");
//					//fixShop();
//				}
//			}
//			else if (success == 1)
//			{
//				const char* name = _PLANT_NAME[ps.getPlant()];
//				char msg[64] = "成功种植";
//				int i = 0;
//				for (i = 0; name[i] != 0; i++)
//					msg[8 + i] = name[i];
//				msg[8 + i] = '!';
//				//showMessage(msg);
//				unchoosePlant();
//			}
//			else if (success == -1)
//			{
//				status = 0;
//				//showMessage("植物还在冷却！");
//				//fixShop();
//			}
//			else if (success == -2)
//			{
//				status = 0;
//				//showMessage("没有这种植物！");
//				//fixShop();
//			}
//			break;
//		}
//		case UP: case DOWN: case LEFT: case RIGHT:
//			//fixShop();
//			choosePlant();
//			ms.move(key);
//			break;
//		case ESC:
//			//showMessage("取消选择");
//			unchoosePlant();
//			break;
//		}
//	}
//}

void Shop::wait()
{
	for (int i = 0; i < PLANT_KIND_NUM; i++)
		if (wait_time[i] > 0)
			wait_time[i]--;
	for (int i = 0; i < 11; i++)
	{
		int y = 69 * wait_time[i] / _WAIT[i];
		waiting_shadows[i]->setGeometry(0, 69 - y, 51, y);
		waiting_shadows[i]->repaint();
		if (_COST[i] > UI_Game::getSunlight())
			valid_shawods[i]->show();
		else
			valid_shawods[i]->hide();
		if (status != 0 && ps.getPlant() == i)
			select_shawods[i]->show();
		else
			select_shawods[i]->hide();
	}
}

void Shop::show()
{
	seedbank->show();
	for (int i = 0; i < 11; i++)
		seedpackets[i]->show();
	sunlight->show();
	for (int i = 0; i < 4; i++)
		numbers[i]->show();
}

void Shop::hide()
{
	seedbank->hide();
	for (int i = 0; i < 11; i++)
		seedpackets[i]->hide();
	sunlight->hide();
	for (int i = 0; i < 4; i++)
		numbers[i]->hide();
}

void Shop::show_numbers(int number)
{
	if (number < 0)
		number = 0;
	if (number > 9999)
		number = 9999;
	char number_str[5] = "";
	sprintf(number_str, "%4d", number);
	char style[256];
	for (int i = 0; i < 4; i++)
	{
		sprintf(style, "background-image:url(Resource/images/interface/numbers_18.png);margin-left: -%dpx; margin-top:0px;", (number_str[i] - '0') * 14);
		numbers[i]->setStyleSheet(style);
		numbers[i]->repaint();
	}
}

void Shop::choosePlant(int pid)
{
	if (status == 0 && wait_time[pid] <= 0 && _COST[pid] <= UI_Game::getSunlight())
	{
		ps.setPlant(pid);
		choosePlant();
		ms.show();
		char style[256] = "";
		int pid = ps.getPlant();
		tmp_plant->setGeometry(0, 0, _WIDTH[pid], _HIGH[pid]);
		sprintf(style, "background-image:url(Resource/images/Plants/%s/%s.gif);margin-left: 0px; margin-top:0px;", _PLANT_PATH[pid], _PLANT_PATH[pid]);
		tmp_plant->setStyleSheet(style);
		tmp_plant->repaint();
	}
	else
	{
		if (wait_time[pid] > 0)
		{
			qDebug() << "Still waiting..";
			menu->showMessage("Resource/images/interface/waiting.png");
		}
		else if (_COST[pid] > UI_Game::getSunlight())
		{
			qDebug() << "Not enough sunlight!";
			menu->showMessage("Resource/images/interface/no_sunlight.png");
		}
	}
}
