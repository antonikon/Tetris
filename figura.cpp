#include "figura.h"

Figura::Figura(QImage *surface, qint32 type):
    _x(8),
    _y(0),
    _surface(surface)
{
    QVector <QImage> t;
    if (type==0)
    {
        _image=QImage("C:\\koding\\tetris1\\Images\\1.png");
        t.push_back(_image);
        t.push_back(_image);
        _map.push_back(t);
        _map.push_back(t);
    }
    else if (type==3)
    {
        _image=QImage("C:\\koding\\tetris1\\Images\\2.png");
        t.push_back(QImage());
        t.push_back(QImage());
        _map.push_back(t);
        _map.push_back(t);
        _map.push_back(t);
        _map[0][0]=_image;
        _map[0][1]=_image;
        _map[1][0]=_image;
        _map[2][0]=_image;
    }
    else if (type==2)
    {
        _image=QImage("C:\\koding\\tetris1\\Images\\3.png");
        t.push_back(QImage());
        t.push_back(QImage());
        _map.push_back(t);
        _map.push_back(t);
        _map.push_back(t);
        _map[0][1]=_image;
        _map[1][1]=_image;
        _map[1][0]=_image;
        _map[2][0]=_image;
    }
    else if (type==1)
    {
        _image=QImage("C:\\koding\\tetris1\\Images\\4.png");
        t.push_back(QImage());
        _map.push_back(t);
        _map.push_back(t);
        _map.push_back(t);
        _map.push_back(t);
        _map[0][0]=_image;
        _map[1][0]=_image;
        _map[2][0]=_image;
        _map[3][0]=_image;
    }
    else if (type==4)
    {
        _image=QImage("C:\\koding\\tetris1\\Images\\5.png");
        t.push_back(QImage());
        t.push_back(QImage());
        _map.push_back(t);
        _map.push_back(t);
        _map.push_back(t);
        _map[0][0]=_image;
        _map[1][0]=_image;
        _map[2][0]=_image;
        _map[1][1]=_image;
    }
    else if (type==5)
    {
        _image=QImage("C:\\koding\\tetris1\\Images\\3.png");
        t.push_back(QImage());
        t.push_back(QImage());
        _map.push_back(t);
        _map.push_back(t);
        _map.push_back(t);
        _map[0][0]=_image;
        _map[1][0]=_image;
        _map[1][1]=_image;
        _map[2][1]=_image;
    }
    else if (type==6)
    {
        _image=QImage("C:\\koding\\tetris1\\Images\\2.png");
        t.push_back(QImage());
        t.push_back(QImage());
        _map.push_back(t);
        _map.push_back(t);
        _map.push_back(t);
        _map[0][1]=_image;
        _map[0][0]=_image;
        _map[1][1]=_image;
        _map[2][1]=_image;
    }
}

void Figura::paint()
{
    QPainter painter(_surface);
    for (int q=0;q<_map.size();q++)
        for (int i=0;i<_map[q].size();i++)
            painter.drawImage((_x+i)*10+5,(_y+q)*10+5,_map[q][i]);
    //painter.drawLine(0,0,200,200);
}

void Figura::x(qint32 x)
{
    _x=x;
}

void Figura::y(qint32 y)
{
    _y=y;
}

qint32 Figura::x()
{
    return _x;
}

qint32 Figura::y()
{
    return _y;
}

qint32 Figura::sizeX()
{
    return _map[0].size();

}

qint32 Figura::sizeY()
{
    return _map.size();
}

bool Figura::testMap(qint32 x, qint32 y)
{
     if (_map[y][x].isNull())
         return false;
     else
         return true;
}

QImage Figura::image()
{
    return _image;
}

void Figura::rotate(bool a)
{
    if (a)
    {
        QVector <QImage> t;
        QVector < QVector <QImage> > map;
        for (int q=0;q<sizeY();q++)
            t.push_back(QImage());
        for (int q=0;q<sizeX();q++)
            map.push_back(t);
        for (int q=0;q<sizeY();q++)
            for (int i=0;i<sizeX();i++)
                map[i][sizeY()-q-1]=_map[q][i];
        _map=map;
    }
    else
    {
        for (int r=0;r<3;r++)
        {
            QVector <QImage> t;
            QVector < QVector <QImage> > map;
            for (int q=0;q<sizeY();q++)
                t.push_back(QImage());
            for (int q=0;q<sizeX();q++)
                map.push_back(t);
            for (int q=0;q<sizeY();q++)
                for (int i=0;i<sizeX();i++)
                    map[i][sizeY()-q-1]=_map[q][i];
            _map=map;
        }
    }

}
