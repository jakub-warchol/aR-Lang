#ifndef GUIENGINE_H
#define GUIENGINE_H

#include <QObject>

#include "models/blocks/blocksmodel.h"

class GuiEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BlocksModel* blocksModel READ blocksModel CONSTANT)
public:
    explicit GuiEngine(QObject *parent = nullptr);

    Q_INVOKABLE void aboutQt();

    BlocksModel* blocksModel() const;

signals:

private:
    BlocksModel* m_blocksModel;
};

#endif // GUIENGINE_H
