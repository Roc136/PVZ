#include "UI_Menu.h"
#include <random>
#include <time.h>

UI_Menu::UI_Menu(QWidget* parent): QWidget(parent)
{
	srand(time(0));
	bg = new Background(parent);
	start = new MyBaseButton(bg, 350, 200, "start");
	help = new MyBaseButton(bg, 350, 250, "help");
	exit = new MyBaseButton(bg, 350, 300, "exit");
	help_ret = new MyBaseButton(bg, 342, 520, "back");
	game_ret = new MyBaseButton(bg, 685, -8, "menu");
	music = new QMediaPlayer(bg);
	game_back_ask_wid = new ensureWid(bg, this);
	gameover_wid = new overWid(bg, this);

	start->show();
	help->show();
	exit->show();
	help_ret->hide();
	game_ret->hide();

	connect(start, SIGNAL(clicked()), this, SLOT(start_game()));
	connect(help, SIGNAL(clicked()), this, SLOT(show_help()));
	connect(help_ret, SIGNAL(clicked()), this, SLOT(help_back()));
	connect(game_ret, SIGNAL(clicked()), this, SLOT(game_back_ask()));
	connect(exit, SIGNAL(clicked()), qApp, SLOT(quit()));

	UI_Game::bg = bg;
	UI_Game::shop = new Shop(bg, this);
	
	score = new QLabel(bg);
	score->setGeometry(30, 566, 120, 31);
	score->setStyleSheet("border-image:url(Resource/images/interface/ScoreBoard.png);margin-left:0px; margin-top:0px;");
	QLabel* brain = new QLabel(score);
	brain->setGeometry(0, 0, 32, 31);
	brain->setStyleSheet("border-image:url();background-image:url(Resource/images/interface/brain.png);");
	for (int i = 0; i < 4; i++)
	{
		numbers[i] = new QLabel(score);
		numbers[i]->setGeometry(i * 20 + 40, 1, 20, 29);
		numbers[i]->setStyleSheet("border-image:url();background-image:url();background-color:white;");
	}
	level = new QLabel(bg);
	level->setGeometry(630, 570, 120, 31);
	level->setStyleSheet("background-image:url(Resource/images/interface/levelboard.png);border-image:url();margin-left:0px; margin-top:0px;");
	level_number = new QLabel(level);
	level_number->setGeometry(100, 1, 20, 29);
	show_numbers(UI_Game::getScore());

	message = new QLabel(bg);
	message->setGeometry(150, 480, 500, 50);
	message->setStyleSheet("background-image:url();background-color:rgba(0,0,0,150);border-radius:10px;margin-left:0px; margin-top:0px;");
	message->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	message->setWindowFlags(Qt::FramelessWindowHint);
	message->raise();
	
	timer = new QTimer(this);
	timer->setInterval(2500);
	connect(timer, SIGNAL(timeout()), this, SLOT(hideMessage()));

}

void UI_Menu::show_numbers(int number)
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
		sprintf(style, "border-image:url();background-image:url(Resource/images/interface/numbers_29.png);margin-left: -%dpx; margin-top:0px;", (number_str[i] - '0') * 20);
		numbers[i]->setStyleSheet(style);
		numbers[i]->repaint();
	}
	sprintf(style, "border-image:url();background-image:url(Resource/images/interface/numbers_29.png);margin-left: -%dpx; margin-top:0px;", UI_Game::level * 20);
	level_number->setStyleSheet(style);
	level_number->repaint();
}

void UI_Menu::showMessage(const char* path)
{
	char style[256] = "";
	sprintf(style, "background-image:url(%s);background-color:rgba(0,0,0,150);border-radius:10px;margin-left:0px; margin-top:0px;", path);
	message->setStyleSheet(style);
	message->raise();
	message->show();
	timer->start();
}

void UI_Menu::start_game()
{
	start->hide();
	help->hide();
	exit->hide();
	bg->setBackground("Resource/images/interface/background1.jpg");
	bg->changeMusic("Resource/sounds/background.mp3");

	music->setMedia(QUrl::fromLocalFile("Resource/sounds/start.mp3"));
	music->setVolume(40);
	music->play();

	game_ret->show();
	score->show();
	level->show();
	UI_Game::Start();
}

void UI_Menu::show_help()
{
	start->hide();
	help->hide();
	exit->hide();
	help_ret->show();
	bg->setBackground("Resource/images/interface/background_help.png");
}

void UI_Menu::help_back()
{
	start->show();
	help->show();
	exit->show();
	help_ret->hide();
	bg->setBackground("Resource/images/interface/background0.png");
}

void UI_Menu::game_back_ask()
{
	UI_Game::Pause();
	game_back_ask_wid->show();
}

void UI_Menu::game_back()
{
	UI_Game::Quit();
	start->show();
	help->show();
	exit->show();
	game_ret->hide();
	score->hide();
	level->hide();
	game_back_ask_wid->hide();
	gameover_wid->hide();
	bg->setBackground("Resource/images/interface/background0.png");
	bg->changeMusic("Resource/sounds/menu.mp3");
}

void UI_Menu::game_noback()
{
	UI_Game::Continue();
	game_back_ask_wid->hide();
}

void UI_Menu::gameoverWid()
{
	music->setMedia(QUrl::fromLocalFile("Resource/sounds/gameover.mp3"));
	music->setVolume(40);
	music->play();
	gameover_wid->show();
}

void UI_Menu::hideMessage()
{
	message->hide();
	timer->stop();
}

AskWid::AskWid(QWidget* parent, UI_Menu* menu) :QWidget(parent), menu(menu)
{
	setGeometry(240, 175, 320, 248);
	setStyleSheet("background-image:url();margin-left:-0px; margin-top:-0px;border:none;");

	lable_topleft = new QLabel(this);
	lable_topleft->setGeometry(0, 0, 107, 97);
	lable_topleft->setStyleSheet("background-image:url(Resource/images/interface/dialog_topleft.png);");
	lable_topmiddle = new QLabel(this);
	lable_topmiddle->setGeometry(107, 0, 93, 97);
	lable_topmiddle->setStyleSheet("background-image:url(Resource/images/interface/dialog_topmiddle.png);");
	lable_topright = new QLabel(this);
	lable_topright->setGeometry(200, 0, 120, 97);
	lable_topright->setStyleSheet("background-image:url(Resource/images/interface/dialog_topright.png);");

	lable_centerleft = new QLabel(this);
	lable_centerleft->setGeometry(0, 97, 107, 54);
	lable_centerleft->setStyleSheet("background-image:url(Resource/images/interface/dialog_centerleft.png);");
	lable_centermiddle = new QLabel(this);
	lable_centermiddle->setGeometry(107, 97, 93, 54);
	lable_centermiddle->setStyleSheet("background-image:url(Resource/images/interface/dialog_centermiddle.png);");
	lable_centerright = new QLabel(this);
	lable_centerright->setGeometry(200, 97, 105, 54);
	lable_centerright->setStyleSheet("background-image:url(Resource/images/interface/dialog_centerright.png);");

	lable_bottomleft = new QLabel(this);
	lable_bottomleft->setGeometry(0, 151, 107, 97);
	lable_bottomleft->setStyleSheet("background-image:url(Resource/images/interface/dialog_bottomleft.png);");
	lable_bottommiddle = new QLabel(this);
	lable_bottommiddle->setGeometry(107, 151, 93, 97);
	lable_bottommiddle->setStyleSheet("background-image:url(Resource/images/interface/dialog_bottommiddle.png);");
	lable_bottomright = new QLabel(this);
	lable_bottomright->setGeometry(200, 151, 108, 97);
	lable_bottomright->setStyleSheet("background-image:url(Resource/images/interface/dialog_bottomright.png);");
}

void AskWid::show()
{
	raise();
	QWidget::show();
	lable_topleft->show();
	lable_topright->show();
	lable_topmiddle->show();
	lable_centerleft->show();
	lable_centermiddle->show();
	lable_centerright->show();
	lable_bottomleft->show();
	lable_bottommiddle->show();
	lable_bottomright->show();
	info->show();
}

void AskWid::hide()
{
	QWidget::hide();
	lable_topleft->hide();
	lable_topright->hide();
	lable_topmiddle->hide();
	lable_centerleft->hide();
	lable_centermiddle->hide();
	lable_centerright->hide();
	lable_bottomleft->hide();
	lable_bottommiddle->hide();
	lable_bottomright->hide();
	info->hide();
}

ensureWid::ensureWid(QWidget* parent, UI_Menu* menu) : AskWid(parent, menu) {
	setConfig();
}

void ensureWid::setConfig()
{
	back = new MyBaseButton(this, 165, 180, "exit");
	noback = new MyBaseButton(this, 25, 180, "back");
	connect(back, SIGNAL(clicked()), menu, SLOT(game_back()));
	connect(noback, SIGNAL(clicked()), menu, SLOT(game_noback()));
	info = new QLabel(this);
	info->setGeometry(0, 0, 320, 180);
	info->setStyleSheet("background-image:url(Resource/images/interface/ensure.png);");
}


overWid::overWid(QWidget* parent, UI_Menu* menu): AskWid(parent, menu){
	setConfig();
}

void overWid::setConfig()
{
	back = new MyBaseButton(this, 95, 180, "exit");
	connect(back, SIGNAL(clicked()), menu, SLOT(game_back()));
	info = new QLabel(this);
	info->setGeometry(0, 0, 320, 180);
	info->setStyleSheet("background-image:url(Resource/images/interface/gameover.png);");
}
