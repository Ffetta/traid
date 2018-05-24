#include "widget.h"
#include "ui_widget.h"
#include <fstream>
QList <double> spisok;
QList<int> result;
QList<bool> score;
Widget::Widget(QList<double> *_list, QWidget *parent) :
    list(_list),
    QWidget(parent),
    //mainwindow(_mainwindow),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    downloader = new Downloader();
    connect(ui->pushButton, &QPushButton::clicked, downloader, &Downloader::getData);
    connect(downloader, &Downloader::onReady, this, &Widget::readFile);
   // connect(downloader, &Downloader::onReady, this, &Widget::readFileNumber);
  // connect(this,&Widget::onReady , graf, &Graf::on_pushButton_clicked );
  //  connect(this,&Widget::onReady,mainwindow,&MainWindow::);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::AddNumber(QByteArray num){
    num+=' ';
    QFile *file = new QFile("C:/number.txt");
    if(file->open(QFile::Append))
        file->write(num);
    file->close();
}


void Widget::AddNumberToList(double s){
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
   // QString Name;
    QByteArray BayPriseByte;
   // QByteArray SellPriseByte;
   // QByteArray LastTraid;
    bool flag=1;
    int control=0;
    for(int i=0;i<search;i++){
        if (str[i]=='}') break;
        if (flag==0 && str[i]!=34){
            switch (control) {
//            case 1:
//                Name+=str[i];
//                break;
            case 5:
                BayPriseByte+=str[i];
                break;
//            case 9:
//                SellPriseByte+=str[i];
//                break;
//            case 13:
//                LastTraid+=str[i];
//                break;
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
//    qDebug()<<BayPriseByte<<' '<<d1;
//    double d2 = atof(SellPriseByte);
//    double d3 = atof(LastTraid);
//    Widget c;
//    c.AddNumber(BayPriseByte);
//    double *now= new double(Name, d1, d2,d3,clock());
//    c.AddNumberToList(*now);
//    return now;

}

//задержка
void wait ( int seconds ) // доступно для int. Если сделать double seconds(будет работать, но есть варнинг)
{
    clock_t endwait;
    //qDebug()<<endwait<<'e';
    endwait = clock () + seconds * CLOCKS_PER_SEC ;
    while (clock() < endwait) {}
}


void Widget::Prognoz(){
    connect(this,&Widget::onReady,mainwindow,&MainWindow::BildGraf);
    if (list->size()>10){
        list->removeAt(0);
    }
    list->push_back(*ReadFile());
    result.push_back(Up_or_Down());
    score.push_back(Win_or_Loss());
//    if(score.back()){
//        ui->textEdit_2->setText("1");
//    }else{
//        ui->textEdit_2->setText(ui->textEdit_2->toPlainText()+"0");
//    }
// вдругом окне
   // double d=*ReadFile();
    //double First = d.bay_Praice;

    emit onReady();


    wait(3);
    downloader->getData();
}


void Widget::readFile()
{
   // QFile file("C:/file.txt");

    if (list->size()==0){
        for(int i=0;i<10;i++){
            list->push_back(*ReadFile());
        }
    }
    Prognoz();
    //if (!file.open(QIODevice::ReadOnly))
     //   return;
    //ui->textEdit->setText(file.readAll());
}

//ne nyhcno
void Widget::readFileNumber()
{
    QFile file("C:/number.txt");
    if (!file.open(QIODevice::ReadOnly))
        return;
    //ui->textEdit->setText(file.readAll());
}


//void Widget::on_delete_2_clicked()
//{
//    QFile *file = new QFile("C:/number.txt");
//    if(file->open(QFile::WriteOnly)){
//        file->write("");
//        file->close();
//    }
//}





int Up_or_Down(){

    double a =spisok.at(9);
    double b=spisok.at(10);
    if (a<b) {
        return 1;
    }
    if (a==b) {
        return 0;
    }
    if (a>b) {
        return -1;
    }
}

bool Win_or_Loss(){
    int a=result.size();
    int b=result.at(a-1);
    int c =result.at(a);

    if (c!=b) {
        return 0;
    }
    else return 1;

}
