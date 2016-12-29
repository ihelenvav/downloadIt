#ifndef CDOWNLOADER_H
#define CDOWNLOADER_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class CDownloader : public QObject
{
    Q_OBJECT

public:
      CDownloader(QObject *parent = Q_NULLPTR);
      ~CDownloader();

      void startRequest(const QUrl &requestedUrl);
public slots:
      void requestLink(const QString& link);
      void downloadFile(const QUrl& link);
      void cancelDownload();

private slots:    
      void onFinished();
      void onDownloadFinished();
      void onReadyRead();
      void onDownloaded();

      void onError(QNetworkReply::NetworkError);
      void onSslErrors(QList<QSslError> sslErrors);

      bool saveAs(const QString &filename, QIODevice *data);
      void slotAuthenticationRequired(QNetworkReply*,QAuthenticator *);

private:
    QUrl getLinkForDownload(const QString& out);

    QUrl url;
    QNetworkAccessManager networkAccessMngr;
    QNetworkReply *reply;
    QNetworkReply *replyDownload;
    QByteArray replyString;

    bool httpRequestAborted;
};

#endif // CDOWNLOADER_H
