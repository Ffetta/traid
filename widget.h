#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>

#include <downloader.h>
#include <fstream>
#include <list>
#include <QList>
#include <iterator>
#include <iostream>

#include<mainwindow.h>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QList<double> *list = nullptr, QWidget *parent = 0);
    ~Widget();
     //boost::signal<void()> OnPressed; //Сигнал
    signals:
      void onReady();
      bool Win_or_Loss();
      int Up_or_Down();


private slots:
    void readFile();
    void readFileNumber();
    //void on_delete_2_clicked();

public slots:
    void AddNumber(QByteArray num);
    void AddNumberToList(double s);
    void Prognoz();



 private:
    QList<double>* list;
    Ui::Widget *ui;
    Downloader *downloader; // Объявляем объект класса для скачивания данных по http
   // Graf *graf;
   //MainWindow *mainwindow;


   // Currebcy_Pair s();
};

#endif // WIDGET_H
