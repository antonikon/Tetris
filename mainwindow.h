#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "map.h"
#include <QPaintEvent>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QtCore>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *key);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    Map _map;
    qint32 _time;
};

#endif // MAINWINDOW_H
