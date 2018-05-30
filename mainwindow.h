#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QWidget>
#include <QFile>
#include<QString>
#include <downloader.h>
#include <fstream>
#include <list>
#include <QList>
#include <iterator>
#include <iostream>
#include <QTimer>
#include <string.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QList<double> *list = nullptr,QWidget *parent = 0);
    ~MainWindow();
    //void BildGraf();
    int Win_or_Loss();
    char  Up_or_Down();
     QTimer *time;
     int timering=1;
     int kolvoWin=0;
     int kolvoLosse=0;
     double balans=10000;
     int stavka=0;
     double mnogitel=0.8;
private:
   // QTimer *time;
    QTimer *timeshow;
    Downloader *downloader;
    QList<double>* list;
    Ui::MainWindow *ui;
    QCustomPlot *customPlot;
    QCPGraph *graphic;
    QPicture *picture;

public slots:
    void slotRangeChanged (const QCPRange &newRange);
    void BildGraf();
    void AddNumber(QByteArray num);
    void AddNumberToList(double s);
    void Prognoz();
    void show1();
    void changeStavka();
    //void on_spinBox_valueChanged(int arg1);
private slots:
    void readFile();


 //  void on_spinBox_valueChanged(int arg1);

signals:
    void onReady();

};

#endif // MAINWINDOW_H
