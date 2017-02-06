#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "broker.h"
#include <QThread>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Broker::declareQML();
    Constants::QmlDec();
//     QThread workerThread;
//    Broker::getInstance()->moveToThread(&workerThread);
//    workerThread.start();

    engine.rootContext()->setContextProperty("myBroker",Broker::getInstance());
    engine.rootContext()->setContextProperty("myConst",Constants::getInstance());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));



    return app.exec();
}
