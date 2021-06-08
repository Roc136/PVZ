#include "MyBaseButton.h"

MyBaseButton::MyBaseButton(QWidget* parent, int x, int y, const char* name, int w, int h)
    :x(x), y(y), w(w), h(h), QPushButton("", parent)
{
    setGeometry(x, y, w, h);
    setFont(QFont("Times", 18));
    setAutoFillBackground(true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setStyleSheet("background-image:url(Resource/images/interface/Button.png);margin-left:-0px; margin-top:-0px;border:none;");
    connect(this, SIGNAL(pressed()), SLOT(pressdown()));
    connect(this, SIGNAL(released()), SLOT(release()));
    QLabel* label = new QLabel(this);
    label->setGeometry(0, 0, w, h);
    char style[100] = "";
    sprintf(style, "background-image:url(Resource/images/interface/button_%s.png);", name);
    label->setStyleSheet(style);
    label->show();
    show();
}

void MyBaseButton::pressdown()
{
    setGeometry(x + 1, y + 1, w, h);
    repaint();
}

void MyBaseButton::release()
{
    setGeometry(x, y, w, h);
    repaint();
}