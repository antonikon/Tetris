#pragma once
#include <QImage>
#include <QVector>
#include <QPainter>
#include "figura.h"

class Map
{
public:
    Map();
    void update();
    void render();
    void newFig();
    void figLeft();
    void figRight();
    void figRotate();
    void pause();
    void restart();
    QImage surface();
    qint32 points();
    qint32 speed();
private:
    bool _gameOver, _pause;
    qint32 _points,_speed,_nextFigType;
    Figura *_fig, *_nextFig;
    QVector < QVector <QImage> > _map;
    QImage _surface;
};
