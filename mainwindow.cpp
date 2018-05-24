#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QThread"

QList <double> spisok;
QList<char> result;
QList<QString> score;
MainWindow::MainWindow(QList<double> *_list, QWidget *parent) :
    list(_list),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    downloader = new Downloader();
    QPushButton *baton= new QPushButton;
    ui->gridLayout->addWidget(baton,0,0,1,2);
    ui->setupUi(this);
    customPlot = new QCustomPlot(); // Инициализируем графическое полотно
    ui->gridLayout->addWidget(customPlot,0,1,2,2);
    customPlot->setInteraction(QCP::iRangeZoom,true);
    customPlot->setInteraction(QCP::iRangeDrag, true);
    customPlot->axisRect()->setRangeDrag(Qt::Horizontal);
    customPlot->axisRect()->setRangeZoom(Qt::Horizontal);
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("hh:mm");
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->xAxis->setAutoTickStep(true);
    customPlot->yAxis->setAutoTickStep(true);
    customPlot->xAxis2->setVisible(true);
    customPlot->yAxis2->setVisible(true);
    customPlot->xAxis2->setTicks(false);
    customPlot->yAxis2->setTicks(false);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setTickLabels(false);
    customPlot->yAxis->setTickLabelColor(QColor(Qt::red));
    graphic = new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(graphic);
    graphic->setPen(QPen(QColor(Qt::red)));
    graphic->setAntialiased(false);
    graphic->setLineStyle(QCPGraph::lsImpulse);
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),
            this, SLOT(slotRangeChanged(QCPRange)));
    time = new QTimer;
    time->start(300);
    connect(ui->pushButton, &QPushButton::clicked, downloader, &Downloader::getData);
    connect(downloader, &Downloader::onReady, this, &MainWindow::readFile);
    connect(time,QTimer::timeout, downloader, &Downloader::getData);
    customPlot->replot();
    time->start(17000);
}
void MainWindow:: BildGraf(){
    ui->setupUi(this);
    ui->gridLayout->addWidget(customPlot,1,1,2,2);
    customPlot->setInteraction(QCP::iRangeZoom,true);
    customPlot->setInteraction(QCP::iRangeDrag, true);
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("hh:mm");
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->xAxis->setAutoTickStep(true);
    customPlot->yAxis->setAutoTickStep(true);
    customPlot->xAxis2->setVisible(true);
    customPlot->yAxis2->setVisible(true);
    customPlot->xAxis2->setTicks(false);
    customPlot->yAxis2->setTicks(false);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setTickLabels(false);
    customPlot->yAxis->setTickLabelColor(QColor(Qt::red));
    graphic = new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(graphic);
    graphic->setPen(QPen(QColor(Qt::red)));
    graphic->setAntialiased(false);
    graphic->setLineStyle(QCPGraph::lsImpulse);
    double now = QDateTime::currentDateTime().toTime_t();
    QVector <double> time(2) ,income(2);
    income= list->toVector();
    for (int i=1; i<2; ++i)
    {
        time[i-1] = now - 60*i;//60 кличество секунд
    }
    graphic->setData(time, income);
    customPlot->yAxis->setRange(list->front()-500,list->front()+500);
    customPlot->xAxis->setRange(time[0]-100,time[0]+100);
    customPlot->replot();
    if(score.size()>1){
        QString a=score.at(1);
        ui->label->setText(a);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotRangeChanged(const QCPRange &newRange)
{
    customPlot->xAxis->setDateTimeFormat((newRange.size() <= 86400)? "hh:mm" : "dd MMM yy");
}

void MainWindow::AddNumber(QByteArray num){
    num+=' ';
    QFile *file = new QFile("C:/number.txt");
    if(file->open(QFile::Append))
        file->write(num);
    file->close();
}


void MainWindow::AddNumberToList(double s){
    if(spisok.size()>10){
        spisok.pop_front();
    }
    spisok.push_back(s);
}

double  *ReadFile(){//расшифровка данных
    QFile file("C:/file.txt");
    if (!file.open(QIODevice::ReadOnly))
        return NULL;
    int search=100;
    QByteArray str= file.read(search);

    QByteArray BayPriseByte;
    bool flag=1;
    int control=0;
    for(int i=0;i<search;i++){
        if (str[i]=='}') break;
        if (flag==0 && str[i]!=34){
            switch (control) {
            case 5:
                BayPriseByte+=str[i];
                break;
            default:
                break;
            }
        }
        if (str[i]==34){
            flag=!flag;
            control++;
        }
    }
    double d1 = BayPriseByte.toDouble();
    double *d=&d1;
    return d;
}



void MainWindow::Prognoz(){

    if (list->size()>=1){
        list->removeAt(0);
    }
    list->push_back(*ReadFile());
    result.push_back(Up_or_Down());
    score.push_back(Win_or_Loss());
    BildGraf();
    emit onReady();
}


void MainWindow::readFile()
{
    if (list->size()==0){
        for(int i=0;i<1;i++){
            list->push_back(*ReadFile());
        }

        for(int i=0;i<10;i++){
            spisok.push_back(*ReadFile());
            result.push_back(*ReadFile());
        }
    }
    Prognoz();
}

char MainWindow::Up_or_Down(){
    int c=spisok.size();
    double a =spisok.at(c-2);
    double b=spisok.at(c-1);
    if (a<b) {
        return '1';
    }
    if (a==b) {
        return '0';
    }
    if (a>b) {
        return '-1';
    }
}

QString MainWindow::Win_or_Loss(){
    int a=result.size();
    char b=result.at(a-2);
    char c =result.at(a-1);
    if (c!=b) {
        return "Не оправдвлся";
    }
    else return "Оправдался";
}


