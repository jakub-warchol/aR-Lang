#include "guiengine.h"

#include <QApplication>

GuiEngine::GuiEngine(QObject *parent) : QObject(parent)
{

}

void GuiEngine::aboutQt()
{
    qApp->aboutQt();
}
