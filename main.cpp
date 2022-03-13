#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "source/guiengine.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    QScopedPointer<GuiEngine> guiEngine{new GuiEngine};

    QQmlApplicationEngine engine;
    qmlRegisterSingletonType(QUrl(QStringLiteral("qrc:/gui/GuiStyle.qml")), "GuiStyle", 1, 0, "GuiStyle");

    engine.rootContext()->setContextProperty(QLatin1String("guiEngine"), guiEngine.data());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);

    }, Qt::QueuedConnection);

    engine.load(url);
    return app.exec();
}
