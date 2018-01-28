#ifndef MY_MAINWINDOW_H
#define MY_MAINWINDOW_H

#include "computer.h"
#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QVector>
#include <QPair>
#include <QSet>
#include <QMessageBox>
#include <QString>
#include <QMenu>
#include <QDebug>
#include <QStack>
#include <QVector>
#include <QPalette>
#include <QPushButton>
#include <QTime>
namespace Ui {
class my_MainWindow;
}

class my_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit my_MainWindow(QWidget *parent = 0);
    ~my_MainWindow();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *mouseEvent);
    int x,y,count=0;
   QVector<QPair <int ,int> >a,b;                           //创建容器存放棋子



private:
    Ui::my_MainWindow *ui;
      computer w;                                           //创建computer对象
     void remake();
     QPushButton *a1,*a2,*a3,*a4;
     int flag=1;
};

#endif // MY_MAINWINDOW_H
