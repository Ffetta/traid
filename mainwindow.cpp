#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QThread"

QList <double> spisok;
QList<char> result;
QList<int> score;
const int kolvoznach=10;
MainWindow::MainWindow(QList<double> *_list, QWidget *parent) :
    list(_list),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    downloader = new Downloader();
    //QPushButton *baton= new QPushButton;
   // ui->gridLayout->addWidget(baton,0,0,1,2);
    ui->setupUi(this);

    customPlot = new QCustomPlot(); // Инициализируем графическое полотно]

    ui->doubleSpinBox->setMaximum(balans);
  ui->label_3->setStyleSheet("QLabel {background-color : blak;font-size: 32px;  color : white; }");
  ui->label_3->setText("Скоро все начнется!");
//ui->gridLayout->addWidget();
   // ui->gridLayout->addWidget(customPlot,0,1,1,2);
//    customPlot->setInteraction(QCP::iRangeZoom,true);
//    customPlot->setInteraction(QCP::iRangeDrag, true);
//    customPlot->axisRect()->setRangeDrag(Qt::Horizontal);
//    customPlot->axisRect()->setRangeZoom(Qt::Horizontal);
//    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
//    customPlot->xAxis->setDateTimeFormat("hh:mm");
//    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
//    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
//    customPlot->xAxis->setAutoTickStep(true);
//    customPlot->yAxis->setAutoTickStep(true);
//    customPlot->xAxis2->setVisible(true);
//    customPlot->yAxis2->setVisible(true);
//    customPlot->xAxis2->setTicks(false);
//    customPlot->yAxis2->setTicks(false);
//    customPlot->xAxis2->setTickLabels(false);
//    customPlot->yAxis2->setTickLabels(false);
//    customPlot->yAxis->setTickLabelColor(QColor(Qt::red));
//    graphic = new QCPGraph(customPlot->xAxis, customPlot->yAxis);
//    customPlot->addPlottable(graphic);
//    graphic->setPen(QPen(QColor(Qt::red)));
//    graphic->setAntialiased(false);
//    graphic->setLineStyle(QCPGraph::lsImpulse);
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),
            this, SLOT(slotRangeChanged(QCPRange)));
    time = new QTimer;
    timeshow=new QTimer;
    time->start(timering*6000);

   connect(time,QTimer::timeout, downloader, &Downloader::getData);
    connect(timeshow,QTimer::timeout,this,&MainWindow::show1);
    connect(downloader, &Downloader::onReady, this, &MainWindow::readFile);
    //connect(ui->spinBox,QSpinBox::valueChanged,this,&MainWindow::changeStavka);
  //  customPlot->replot();
 //   connect(ui->spinBox,&QSpinBox::valueChanged,this,&MainWindow::on_spinBox_valueChanged);
    timeshow->start(1700000);//устанавливает размер
    ui->doubleSpinBox->setValue(0.86);
    ui->spinBox_2->setValue(30);

         ui->label->setStyleSheet("QLabel {font-size: 26px;  color : green; }");
          ui->label_6->setStyleSheet("QLabel {font-size: 26px;   }");
          ui->label_4->setStyleSheet("QLabel {font-size: 26px;  background-color : red; }");
          ui->label_5->setStyleSheet("QLabel {font-size: 26px; background-color : green;  }");
          ui->label_7->setStyleSheet("QLabel {font-size: 26px;   }");
          ui->label_8->setStyleSheet("QLabel {font-size: 26px;   }");
          ui->label_9->setStyleSheet("QLabel {font-size: 26px;   }");

         show1();
}
void MainWindow:: BildGraf(){

    ui->gridLayout_2->addWidget(customPlot,0,1,1,2);
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
    //customPlot->xAxis->setRange(time[0]-100,time[0]+100);
    customPlot->replot();
    if (result.size()>1){
        ui->label_2->setStyleSheet("QLabel {font-size: 26px; }");
        if(result.back()='1'){
            ui->label_2->setText("Вверх");
        }
        if(result.back()='-1'){
            ui->label_2->setText("Вниз");
        }
        if(result.back()='0'){
            ui->label_2->setText("Останется на месте");
        }
    }
    stavka=ui->spinBox->value();
    mnogitel=ui->doubleSpinBox->value();


    if(score.size()>1){
        int a=score.last();
      if(a==2){
       ui->label->setStyleSheet("QLabel {font-size: 26px;  color : red; }");
         ui->label->setText("Не оправдался");
         kolvoLosse++;
         balans=balans-stavka;
         QString s;
         s=QString::number(kolvoLosse);
         ui->label_5->setText("Количество проигранных: "+s);

 }else{
      //  ui->label->setStyleSheet("QLabel {font-size: 26px;  color : green; }");
         ui->label->setText("Оправдался");
         kolvoWin++;
         balans=balans+stavka*mnogitel;
         QString s;
         s=QString::number(kolvoWin);
         ui->label_5->setText("Количество выгранных: "+s);

 }
 }
    QString s;
    s=QString::number(balans);
    ui->label_6->setText("Баланc "+s);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotRangeChanged(const QCPRange &newRange)
{
    customPlot->xAxis->setDateTimeFormat((newRange.size() <= 86400)? "hh:mm" : "dd MMM yy");
}

void MainWindow::show1()
{
     double now = QDateTime::currentDateTime().toTime_t();
      customPlot->xAxis->setRange(now-100,now+100);
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
time->stop();
int a=ui->spinBox_2->value();
time->start(a*1000);
    if (list->size()>=1){
        list->removeAt(0);
    }
    list->push_back(*ReadFile());

    if(result.size()>kolvoznach){
        result.removeFirst();
    }
    if(score.size()>kolvoznach){
        score.removeFirst();
    }
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

int MainWindow::Win_or_Loss(){
    int a=result.size();
    char b=result.at(a-2);
    char c =result.at(a-1);
    if (c!=b) {
        return 2;//не оправдался

    }
    else return 1;//оправдался
}
void MainWindow::changeStavka(){



}



//    void MainWindow::on_spinBox_valueChanged(int arg1)
//{
//    timering=arg1;
//     time = new QTimer;
//     time->start(100);
//        connect(time,QTimer::timeout, downloader, &Downloader::getData);
//}
