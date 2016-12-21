#ifndef CDOWNLOADER_H
#define CDOWNLOADER_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>


class CDownloader : public QObject
{
    Q_OBJECT

public:
      CDownloader(QObject *parent = Q_NULLPTR);
      ~CDownloader();

      void startRequest(const QUrl &requestedUrl);
public slots:
      void download(const QString& link);
      void cancelDownload();

private slots:    
      void onFinished();
      void onReadyRead();

      void slotAuthenticationRequired(QNetworkReply*,QAuthenticator *);

private:
    QUrl url;
    QNetworkAccessManager networkAccessMngr;
    QNetworkReply *reply;

    bool httpRequestAborted;
};

#endif // CDOWNLOADER_H
