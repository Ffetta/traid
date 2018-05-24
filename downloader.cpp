#include "downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
}

void Downloader::getData()
{
    QUrl url("https://api.exmo.com/v1/ticker/");
    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);
}

void Downloader::onResult(QNetworkReply *reply)
{    
    if(reply->error()){
        qDebug() << "ERROR1";
    } else {
        QFile *file = new QFile("C:/file.txt");
        if(file->open(QFile::WriteOnly)){
            file->write(reply->readAll());
            file->close();
            qDebug() << "Downloading is completed";
            emit onReady();
        }
    }
}

