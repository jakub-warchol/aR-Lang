#ifndef GUIENGINE_H
#define GUIENGINE_H

#include <QObject>

class GuiEngine : public QObject
{
    Q_OBJECT
public:
    explicit GuiEngine(QObject *parent = nullptr);

    Q_INVOKABLE void aboutQt();

signals:

};

#endif // GUIENGINE_H
