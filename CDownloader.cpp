#include "CDownloader.h"
#include <QNetworkRequest>
#include <QDateTime>
#include <QFile>

CDownloader::CDownloader(QObject * parent):
    QObject(parent)
{

}

CDownloader::~CDownloader(){

}

QUrl CDownloader::getLinkForDownload(const QString& out)
{
    auto list = out.split("Link: ");
    if(list.count() != 2)
        return QUrl();

    return QUrl(list.at(1));
}

void CDownloader::requestLink(const QString& link)
{
    QString urlStr = QString("http://www.youtubeinmp3.com/fetch/?format=text&video=https://www.youtube.com/watch?v=%1").arg(link);

    startRequest(urlStr);
}

void CDownloader::downloadFile(const QUrl& link)
{
    qDebug() << "----" << __FUNCTION__ << link;
    QNetworkRequest request;
    request.setUrl(link);

    replyDownload = networkAccessMngr.get(request);
    connect(replyDownload, &QNetworkReply::finished, this, &CDownloader::onDownloadFinished);
    connect(replyDownload, &QIODevice::readyRead, this, &CDownloader::onDownloaded);
}

void CDownloader::startRequest(const QUrl &requestedUrl)
{
    if(!requestedUrl.isValid()){
        qDebug() << "Url is not valid.Bye" << requestedUrl;
        return;
    }
    QNetworkRequest request;
    request.setUrl(requestedUrl);
    request.setRawHeader("Accept-Location", "*");

    reply = networkAccessMngr.get(request);
    connect(reply, &QNetworkReply::finished, this, &CDownloader::onFinished);
    connect(reply, &QIODevice::readyRead, this, &CDownloader::onReadyRead);
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
              this, SLOT(onError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
              this, SLOT(onSslErrors(QList<QSslError>)));
}

void CDownloader::cancelDownload()
{
}

void CDownloader::onFinished()
{
    qDebug() << "----" << __FUNCTION__;

    reply->deleteLater();
    reply = Q_NULLPTR;
}

void CDownloader::onDownloadFinished()
{
    qDebug() << "----" << __FUNCTION__;

    replyDownload->deleteLater();
    replyDownload = Q_NULLPTR;
}

void CDownloader::onReadyRead()
{
    QByteArray out = reply->readAll();

    QUrl url = getLinkForDownload(out);
    if(!url.isValid()){
        qDebug() << "Url for download is not valid. Bye.";
        return;
    }

    downloadFile(url);

    qDebug() << "----" << __FUNCTION__ << out;
}

void CDownloader::onDownloaded()
{
    qDebug() << "----" << __FUNCTION__;

    QString fileName = "30_m.mp3"; //getFileName();

    saveAs(fileName, replyDownload);

}

void CDownloader::onError(QNetworkReply::NetworkError error)
{

}

void CDownloader::onSslErrors(QList<QSslError> sslErrors)
{

}

bool CDownloader::saveAs(const QString &filename, QIODevice *data)
{
    qDebug() << "----" << __FUNCTION__;

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
      fprintf(stderr, "Could not open %s for writing: %s\n",
              qPrintable(filename),
              qPrintable(file.errorString()));
      return false;
    }

    file.write(data->readAll());
    file.close();

    return true;
}

void CDownloader::slotAuthenticationRequired(QNetworkReply*,QAuthenticator *)
{
    qDebug() << "----" << __FUNCTION__;
}
