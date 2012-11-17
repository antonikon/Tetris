#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QString>
#include <QIcon>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("C:\\koding\\tetris1\\Images\\favicon.ico"));
    startTimer(20);
    _time=0;
    _keyTime=0;
    _keys.insert(Qt::Key_Space,false);
    _keys.insert(Qt::Key_Left,false);
    _keys.insert(Qt::Key_Right,false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *)
{
    _map.render();
    QPainter painter(this);
    painter.drawImage(0,0,_map.surface());
}

void MainWindow::timerEvent(QTimerEvent *)
{
    update();
    _keyTime++;
    _time+=_map.speed();
    if (_time>=15)
    {
        _map.update();
        _time=0;
    }
    if (_keyTime==3)
    {
        if (_keys[Qt::Key_Space])
            _map.update();
        if (_keys[Qt::Key_Right])
            _map.figRight();
        else if (_keys[Qt::Key_Left])
            _map.figLeft();
        _keyTime=0;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *key)
{
    if (key->key()==Qt::Key_Space)
        _keys[Qt::Key_Space]=true;
        //_map.update();
    if (key->key()==Qt::Key_Right)
        _keys[Qt::Key_Right]=true;
        //_map.figRight();
    else if (key->key()==Qt::Key_Left)
        _keys[Qt::Key_Left]=true;
        //_map.figLeft();
    if (key->key()==Qt::Key_Down)
        _map.figRotate(false);
    else if (key->key()==Qt::Key_Up)
        _map.figRotate(true);
    if (key->key()==Qt::Key_R)
        _map.restart();
    else if (key->key()==Qt::Key_Return)
        _map.enter();
    else if (key->key()==Qt::Key_Escape)
        _map.menu();

}

void MainWindow::keyReleaseEvent(QKeyEvent *key)
{
    if (key->key()==Qt::Key_Space)
        _keys[Qt::Key_Space]=false;
        //_map.update();
    if (key->key()==Qt::Key_Right)
        _keys[Qt::Key_Right]=false;
        //_map.figRight();
    else if (key->key()==Qt::Key_Left)
        _keys[Qt::Key_Left]=false;
        //_map.figLeft();
}
