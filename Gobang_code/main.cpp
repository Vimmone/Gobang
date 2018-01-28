#include "my_mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    my_MainWindow w;                //创建Gobang
    w.show();

    return a.exec();
}
