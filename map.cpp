#include "map.h"

Map::Map()
{
    _surface=QImage("Images/BG1.png");
    QVector <QImage> t;
    for (int q=0;q<20;q++)
        t.push_back(QImage());
    for (int q=0;q<30;q++)
        _map.push_back(t);
    _fig=new Figura(&_surface,rand()%5);
    _nextFigType=rand()%5;
    _nextFig=new Figura(&_surface,_nextFigType);
    _nextFig->x(23);
    _nextFig->y(23);
    _points=0;
    _speed=1;
    _gameOver=false;
    _pause=false;
}

void Map::newFig()
{
    delete _fig;
    _fig=new Figura(&_surface,_nextFigType);
    delete _nextFig;
    _nextFigType=rand()%5;
    _nextFig=new Figura(&_surface,_nextFigType);
    _nextFig->x(23);
    _nextFig->y(23);
}

void Map::update()
{
    bool go=true;
    for (int q=0;q<_map[0].size();q++)
        if (!_map[0][q].isNull())
            go=false;
    _gameOver=!go;
    if (go && !_pause)
    {
        bool isClear=true;
        for (int q=0;q<_fig->sizeY();q++)
            for (int i=0;i<_fig->sizeX();i++)
                if (_fig->testMap(i,q))
                    if (!_map[_fig->y()+q+1][_fig->x()+i].isNull() ||  _fig->y()+_fig->sizeY()>28)
                        isClear=false;
        if (isClear)
        {
            _fig->y(_fig->y()+1);
        }
        else
        {
            for (int q=0;q<_fig->sizeY();q++)
                for (int i=0;i<_fig->sizeX();i++)
                    if (_fig->testMap(i,q))
                        _map[_fig->y()+q][_fig->x()+i]=_fig->image();
            newFig();
        }
        for (int q=0;q<_map.size();q++)
        {
            bool a=true;
            for (int i=0;i<_map[0].size()-1;i++)
                if (_map[q][i].isNull())
                    a=false;
            if (a)
            {
                _map.remove(q);
                QVector <QImage> t;
                for (int q=0;q<20;q++)
                    t.push_back(QImage());
                _map.push_front(t);
                _points++;
                _speed=_points/10+1;
            }
        }
    }
}

void Map::render()
{
    if (_gameOver)
    {
        QPainter painter(&_surface);
        painter.drawImage(25,90,QImage("Images/GM.png"));
        painter.drawImage(25,120,QImage("Images/M1.png"));
    }
    else if (_pause)
    {
        QPainter painter(&_surface);
        painter.drawImage(25,90,QImage("Images/P.png"));
    }
    else
    {
        _surface=QImage("Images/BG1.png");
        _fig->paint();
        _nextFig->paint();
        QPainter painter(&_surface);
        for (int q=0;q<_map.size();q++)
            for (int i=0;i<_map[q].size();i++)
                if (!_map[q][i].isNull())
                    painter.drawImage(i*10+5,q*10+5,_map[q][i]);
    }
}

QImage Map::surface()
{
    return _surface;
}

void Map::figLeft()
{
    if (!_pause)
    {
        bool a=true;
        for (int q=0;q<_fig->sizeY();q++)
            for (int i=0;i<_fig->sizeX();i++)
                if (_fig->testMap(i,q))
                    if (_fig->x()<=0 || !_map[_fig->y()+q][_fig->x()+i-1].isNull())
                        a=false;
        if (a)
            _fig->x(_fig->x()-1);
    }
}

void Map::figRight()
{
   // qDebug() << _map[_fig->y()][_fig->x()+1].isNull();
    if (!_pause)
    {
        bool a=true;
        for (int q=0;q<_fig->sizeY();q++)
            for (int i=0;i<_fig->sizeX();i++)
                if (_fig->testMap(i,q))
                    if (!_map[_fig->y()+q][_fig->x()+i+1].isNull() ||  _fig->x()+_fig->sizeX()>18)
                        a=false;
        if (a)
            _fig->x(_fig->x()+1);
    }
}

void Map::figRotate()
{
    if (!_pause)
    {
        bool test=true;
        for (int q=0;q<_fig->sizeY();q++)
            for (int i=0;i<_fig->sizeX();i++)
                if (!_map[_fig->y()][_fig->x()+q].isNull())
                    test=false;
        if (_fig->x()+_fig->sizeY()<20 && test)
            _fig->rotate();
    }
}

qint32 Map::points()
{
    return _points;
}

qint32 Map::speed()
{
    return _speed;
}

void Map::pause()
{
    if (_pause)
        _pause=false;
    else
        _pause=true;
}

void Map::restart()
{
    _points=0;
    _speed=1;
    _gameOver=false;
    for (int q=0;q<_map.size();q++)
        for (int i=0;i<_map[0].size();i++)
            _map[q][i]=QImage();
    newFig();
}
