#pragma once
#include <qpushbutton.h>
#include <qfont.h>
#include <QApplication>
#include <qlabel.h>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include "MyBaseButton.h"

class Background : public QWidget
{
	QMediaPlaylist* playlist;
	QMediaPlayer* music;
public:
	Background(QWidget* parent = 0);
	void setBackground(const char* path);
	void changeMusic(const char* path);
};