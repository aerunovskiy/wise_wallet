#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLocale>
#include <QTranslator>

#include "main_backend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MainBackend mainBackend;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("MainBackend", &mainBackend);
    engine.load(QUrl(QStringLiteral("qrc:main.qml")));

    if (engine.rootObjects().isEmpty())
        return EXIT_FAILURE;

    return app.exec();
}
