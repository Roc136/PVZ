#include <QtWidgets/QApplication>
#include <qwidget.h>
#include "include.h"
#include "config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("Plant VS. Zombies! | version = 3.0  | @Roc");
    UI_Menu* menu = new UI_Menu;
    return a.exec();
}

