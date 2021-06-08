#pragma once
#include <qpushbutton.h>
#include <qfont.h>
#include <qlabel.h>

class MyBaseButton : public QPushButton
{
	Q_OBJECT
private:
	int x;
	int y;
	int w;
	int h;
public:
	MyBaseButton(QWidget* parent = 0, int x = 0, int y = 0, const char* name = 0, int w = 113, int h = 41);
public slots:
	void pressdown();
	void release();
};