#include <QApplication>
#include <QSurfaceFormat>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>

#include "source/guiengine.h"
#include "source/models/blocks/addblocksmodel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    QScopedPointer<GuiEngine> guiEngine{new GuiEngine};

    app.setApplicationName("aR-Lang");
    app.setWindowIcon(QIcon(":/resources/icons/logo.png"));

    // set supersampling
    QSurfaceFormat supersamplingFormat;
    supersamplingFormat.setSamples(8);
    QSurfaceFormat::setDefaultFormat(supersamplingFormat);

    QQmlApplicationEngine engine;
    qmlRegisterSingletonType(QUrl(QStringLiteral("qrc:/gui/GuiStyle.qml")), "GuiStyle", 1, 0, "GuiStyle");
    qmlRegisterType<AddBlocksModel>("AddBlocks", 1, 0, "AddBlocksModel");

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
