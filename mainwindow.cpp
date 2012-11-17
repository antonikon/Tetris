#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPen>
#include <QString>
#include <QFont>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("C:\\koding\\tetris1\\Images\\favicon.ico"));
    startTimer(20);
    _time=0;
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
    QPen pen;
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.setFont(QFont("",40));
    painter.drawText(205,20,100,100,0,QString("%1").arg(_map.points()));
    painter.drawText(205,105,100,100,0,QString("%1").arg(_map.speed()));
}

void MainWindow::timerEvent(QTimerEvent *)
{
    update();
    _time+=_map.speed();
    if (_time>=15)
    {
        _map.update();
        _time=0;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *key)
{
    if (key->key()==Qt::Key_Right)
        _map.figRight();
    else if (key->key()==Qt::Key_Left)
        _map.figLeft();
    else if (key->key()==Qt::Key_Down)
        _map.update();
    else if (key->key()==Qt::Key_Up)
        _map.figRotate();
    else if (key->key()==Qt::Key_P)
        _map.pause();
    else if (key->key()==Qt::Key_R)
        _map.restart();

}
