#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>

#include "CDownloader.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/DownloadIt.qml")));
    QQmlContext * context = engine.rootContext();
    CDownloader * downloader = new CDownloader(Q_NULLPTR);
    context->setContextProperty("downloader", downloader);

    app.setWindowIcon(QIcon("./icon.png"));

    return app.exec();
}
