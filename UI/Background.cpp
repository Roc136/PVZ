#include "Background.h"

Background::Background(QWidget* parent) : QWidget(parent)
{
    setGeometry(300, 300, 1, 1);
    setFixedSize(800, 600);
    setAutoFillBackground(true);
    setStyleSheet("background-image:url(Resource/images/interface/background0.png);margin-left:-220px; margin-top:-0px;");
    show();

    playlist = new QMediaPlaylist();
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music = new QMediaPlayer();
    music->setPlaylist(playlist);

    playlist->addMedia(QUrl::fromLocalFile("Resource/sounds/menu.mp3"));
    music->setVolume(30);
    music->play();
}

void Background::setBackground(const char* path)
{
    char style[300];
    sprintf(style, "background-image:url(%s);margin-left:-220px; margin-top:-0px;", path);
    setStyleSheet(style);
}

void Background::changeMusic(const char* path)
{
    playlist->removeMedia(0);
    playlist->addMedia(QUrl::fromLocalFile(path));
    music->play();
}
