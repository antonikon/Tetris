#pragma once
#include <QImage>
#include <QVector>
#include <QPainter>
#include "figura.h"
#include <QPen>
#include <QFont>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <phonon/phonon>

class Map
{
public:
    Map();
    ~Map();
    void update();
    void render();
    void newFig();
    void figLeft();
    void figRight();
    void figRotate(bool a);
    void restart();
    void enter();
    void menu();
    QImage surface();
    qint32 speed();
private:
    void chekRecords();
    qint32 _points,_speed,_nextFigType, _curY, _mainMenu;
    Figura *_fig, *_nextFig;
    QVector < QVector <QImage> > _map;
    QImage _surface;
    QVector <QString> _records;
    Phonon::MediaObject *_media;
    Phonon::AudioOutput *_audio;
};
