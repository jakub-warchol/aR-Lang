#include "guiengine.h"

#include <QApplication>

GuiEngine::GuiEngine(QObject *parent) : QObject(parent)
{
    m_blocksModel = new BlocksModel(this);
}

void GuiEngine::aboutQt()
{
    qApp->aboutQt();
}

BlocksModel *GuiEngine::blocksModel() const
{
    return m_blocksModel;
}
