#include "map.h"

Map::Map()
{
    QVector <QImage> t;
    for (int q=0;q<20;q++)
        t.push_back(QImage());
    for (int q=0;q<30;q++)
        _map.push_back(t);
    _points=0;
    _speed=1;
    _mainMenu=3;
    _curY=0;
    QFile file("C:\\koding\\tetris1\\Records.txt");
    file.open(QFile::ReadOnly);
    QTextStream out(&file);
    QString line;
    for (int q=0;q<5;q++)
    {
        line=out.readLine();
        _records.push_back(QString(line));
    }
    file.close();
    _media = new Phonon::MediaObject;
    _audio = new Phonon::AudioOutput;
    _media->setCurrentSource(QString("C:\\koding\\tetris1\\Songs\\Rose_theme.mp3"));
    Phonon::createPath(_media,_audio);
    _media->play();
}

void Map::newFig()
{
    delete _fig;
    _fig=new Figura(&_surface,_nextFigType);
    delete _nextFig;
    _nextFigType=rand()%7;
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
    if (!go)
    {
        if (_mainMenu!=2)
        {
            _media->setCurrentSource(QString("C:\\koding\\tetris1\\Songs\\Quest_Completed_Overlord.mp3"));
            _media->play();
        }
        _mainMenu=2;
    }
    if (go && _mainMenu==0)
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
    if (_mainMenu>2)
    {
        _surface=QImage("C:\\koding\\tetris1\\Images\\menu.png");
        QPainter painter(&_surface);
        if (_mainMenu==3)
        {
            painter.drawImage(0,0,QImage("C:\\koding\\tetris1\\Images\\Mmenu.png"));
            painter.drawImage(20,110+(36.5*_curY),QImage("C:\\koding\\tetris1\\Images\\menuC.png"));
        }
        else if (_mainMenu==4)
        {
            painter.drawImage(0,0,QImage("C:\\koding\\tetris1\\Images\\Control.png"));
            painter.drawImage(180,258,QImage("C:\\koding\\tetris1\\Images\\menuC.png"));
        }
        else if (_mainMenu==5)
        {
            painter.drawImage(0,0,QImage("C:\\koding\\tetris1\\Images\\R.png"));
            painter.drawImage(180,258,QImage("C:\\koding\\tetris1\\Images\\menuC.png"));
            QPen pen;
            pen.setColor(Qt::blue);
            painter.setPen(pen);
            painter.setFont(QFont("",24));
            for (int q=0;q<5;q++)
                painter.drawText(70,65+(36.5*q),300,50,0,_records[q]);
        }
    }
    else
    {
        _surface=QImage("C:\\koding\\tetris1\\Images\\BG1.png");
        _fig->paint();
        _nextFig->paint();
        QPainter painter(&_surface);
        for (int q=0;q<_map.size();q++)
            for (int i=0;i<_map[q].size();i++)
                if (!_map[q][i].isNull())
                    painter.drawImage(i*10+5,q*10+5,_map[q][i]);
        if (_mainMenu==2)
        {
            painter.drawImage(0,0,QImage("C:\\koding\\tetris1\\Images\\Z.png"));
            painter.drawImage(0,0,QImage("C:\\koding\\tetris1\\Images\\GM.png"));
            painter.drawImage(20,165+(20*_curY),QImage("C:\\koding\\tetris1\\Images\\gameC.png"));
        }
        else if (_mainMenu==1)
        {
            painter.drawImage(0,0,QImage("C:\\koding\\tetris1\\Images\\Z.png"));
            painter.drawImage(0,0,QImage("C:\\koding\\tetris1\\Images\\P.png"));
            painter.drawImage(35,165+(20*_curY),QImage("C:\\koding\\tetris1\\Images\\gameC.png"));
        }
        QPen pen;
        pen.setColor(Qt::red);
        painter.setPen(pen);
        painter.setFont(QFont("",40));
        painter.drawText(205,20,100,100,0,QString("%1").arg(_points));
        painter.drawText(205,105,100,100,0,QString("%1").arg(_speed));
    }
}

QImage Map::surface()
{
    return _surface;
}

void Map::figLeft()
{
    if (_mainMenu==0)
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
    if (_mainMenu==0)
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

void Map::figRotate(bool a)
{
    if (_mainMenu==0)
    {
        bool test=true;
        for (int q=0;q<_fig->sizeY();q++)
            for (int i=0;i<_fig->sizeX();i++)
                if (!_map[_fig->y()][_fig->x()+q].isNull())
                    test=false;
        if (_fig->x()+_fig->sizeY()<20 && test)
            _fig->rotate(a);
    }
    else if (_mainMenu==3 && !a && _curY<3)
        _curY++;
    else if (_mainMenu==3 && a && _curY>0)
        _curY--;
    else if ((_mainMenu==2 || _mainMenu==1) && !a && _curY<1)
        _curY++;
    else if ((_mainMenu==2 || _mainMenu==1) && a && _curY>0)
        _curY--;

}

void Map::restart()
{
    if (_mainMenu==2 || _mainMenu==3)
    {
        _fig=new Figura(&_surface,rand()%5);
        _nextFigType=rand()%7;
        _nextFig=new Figura(&_surface,_nextFigType);
        _nextFig->x(23);
        _nextFig->y(23);
        _points=0;
        _speed=1;
        _mainMenu=0;
        for (int q=0;q<_map.size();q++)
            for (int i=0;i<_map[0].size();i++)
                _map[q][i]=QImage();
        _media->setCurrentSource(QString("C:\\koding\\tetris1\\Songs\\Sanctuary_Beauty.mp3"));
        _media->play();
    }
}

qint32 Map::speed()
{
    return _speed;
}

void Map::enter()
{
    if (_mainMenu==3)
    {
        if (_curY==0)
        {
            restart();
            _mainMenu=0;
        }
        else if (_curY==1)
            _mainMenu=4;
        else if (_curY==2)
            _mainMenu=5;
        else if (_curY==3)
        {
            exit(0);
        }
    }
    else if(_mainMenu==4)
        _mainMenu=3;
    else if(_mainMenu==5)
        _mainMenu=3;
    else if (_mainMenu==2)
    {
        chekRecords();
        if (_curY==0)
            restart();
        else
        {
            restart();
            _mainMenu=3;
            _curY=0;
            _media->setCurrentSource(QString("C:\\koding\\tetris1\\Songs\\Rose_theme.mp3"));
            _media->play();
        }
    }
    else if (_mainMenu==1)
    {
        if (_curY==0)
        {
            chekRecords();
            restart();
            _mainMenu=3;
            _media->setCurrentSource(QString("C:\\koding\\tetris1\\Songs\\Rose_theme.mp3"));
            _media->play();
        }
        else
            _mainMenu=0;
    }

}

void Map::chekRecords()
{
    bool b=true;
    for (int q=0;q<5;q++)
    {
        QStringList l=_records[q].split(" - ");
        if (l.size()>1)
            if (QString("%1").arg(l[1]).toInt()>_points)
                b=false;
    }
    if (b)
        _records.push_front(QString("User - %2").arg(_points));
}

void Map::menu()
{
    if (_mainMenu==1)
    {
        _mainMenu=0;
    }
    else if (_mainMenu==0)
        _mainMenu=1;
}

Map::~Map()
{
    QFile file("C:\\koding\\tetris1\\Records.txt");
    file.open(QFile::WriteOnly);
    file.remove();
    file.close();
    file.setFileName("C:\\koding\\tetris1\\Records.txt");
    file.open(QFile::WriteOnly);
    QTextStream in(&file);
    for (int q=0;q<5;q++)
        in << _records[q] << "\n";
    file.close();
}
