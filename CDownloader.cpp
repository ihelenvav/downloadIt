#include "CDownloader.h"
#include <QNetworkRequest>
#include <QNetworkReply>


CDownloader::CDownloader(QObject * parent):
    QObject(parent)
{

}

CDownloader::~CDownloader(){

}

void CDownloader:: download(const QString& link)
{
    qDebug() << __FUNCTION__ << " link=" << link;

    QString urlStr = QString("http://www.youtube-mp3.org/api/pushItem/?item=%1&xy=yx&bf=false&r=#{Time.now.to_i}").arg(link);

    qDebug() << "----" << " urlStr=" << urlStr;
    startRequest(urlStr);
}

void CDownloader::startRequest(const QUrl &requestedUrl)
{
    if(!requestedUrl.isValid()){
        qDebug() << "Url is not valid.Buy" << requestedUrl;
        return;
    }
    QNetworkRequest request;
    request.setUrl(requestedUrl);
    request.setRawHeader("Accept-Location", " *");

    reply = networkAccessMngr.get(request);
    connect(reply, &QNetworkReply::finished, this, &CDownloader::onFinished);
    connect(reply, &QIODevice::readyRead, this, &CDownloader::onReadyRead);

}


void CDownloader::cancelDownload()
{

}

void CDownloader::onFinished()
{
    reply->deleteLater();
    reply = Q_NULLPTR;
}

void CDownloader::onReadyRead()
{
    QByteArray out = reply->readAll();
    qDebug() << "----" << __FUNCTION__ << out;

}

void CDownloader::slotAuthenticationRequired(QNetworkReply*,QAuthenticator *)
{

}
