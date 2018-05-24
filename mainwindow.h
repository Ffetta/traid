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
    QString Win_or_Loss();
    char  Up_or_Down();
private:
    QTimer *time;
    Downloader *downloader;
    QList<double>* list;
    Ui::MainWindow *ui;
    QCustomPlot *customPlot;
    QCPGraph *graphic;

public slots:
    void slotRangeChanged (const QCPRange &newRange);
    void BildGraf();
    void AddNumber(QByteArray num);
    void AddNumberToList(double s);
    void Prognoz();

private slots:
    void readFile();

signals:
    void onReady();

};

#endif // MAINWINDOW_H
