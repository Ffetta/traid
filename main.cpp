#include "mainwindow.h"
//#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QList<double> *list = new QList<double>;
    MainWindow w(list);
    //Widget v(list);
  //  v.show();

    w.show();


    return a.exec();
}
