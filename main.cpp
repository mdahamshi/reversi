#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "broker.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Broker::declareQML();
    Constants::QmlDec();

    engine.rootContext()->setContextProperty("myBroker",Broker::getInstance());
    engine.rootContext()->setContextProperty("myConst",Constants::getInstance());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));



    return app.exec();
}
