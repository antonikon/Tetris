#pragma once
#include <QPainter>
#include <QImage>
#include <QtCore>

class Figura
{
public:
    Figura(QImage *surface, qint32 type);
    void paint();
    void x(qint32 x);
    void y(qint32 y);
    void rotate();
    qint32 sizeX();
    qint32 sizeY();
    qint32 x();
    qint32 y();
    bool testMap(qint32 x, qint32 y);
    QImage image();
private:
    qint32 _x,_y;
    QImage *_surface, _image;
    QVector < QVector <QImage> > _map;
};
