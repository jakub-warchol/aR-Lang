#include "connectionlinesmodel.h"

#include <QQuickItem>

ConnectionLinesModel::ConnectionLinesModel(QObject *parent) : QObject(parent)
{}

int ConnectionLinesModel::linesCount() const
{
    return m_lines.size();
}

int ConnectionLinesModel::selectedLinesCount() const
{
    return m_selectedLines.size();
}

void ConnectionLinesModel::addLine(QQuickItem *line)
{
    m_lines.push_back(line);
    emit linesCountChanged(m_lines.size());
}

void ConnectionLinesModel::removeLine(QQuickItem *line)
{
    int lineIdx = -1;
    for(int i = 0; i < m_lines.size(); i++) {
        if(m_lines.at(i) == line) {
            lineIdx = i;
            break;
        }
    }

    if(lineIdx != -1) {
        m_lines.removeAt(lineIdx);
        if(auto selectedLineIdx = lineInSelectedModelIndex(line); selectedLineIdx > -1) {
            m_selectedLines.removeAt(selectedLineIdx);
            emit selectedLinesCountChanged(m_selectedLines.size());
        }

        emit linesCountChanged(m_lines.size());        
    }
}

void ConnectionLinesModel::removeSelectedLines()
{
    for(auto &line : m_selectedLines) {
        if(auto selectedLineIdx = lineInSelectedModelIndex(line); selectedLineIdx > -1) {
            m_selectedLines.removeAt(selectedLineIdx);
            QMetaObject::invokeMethod(line, "lineRemoved", Qt::DirectConnection);
        }
    }

    emit selectedLinesCountChanged(m_selectedLines.size());
}

void ConnectionLinesModel::toggleLineSelectionStatus(QQuickItem *line)
{
    if(auto selectedLineIdx = lineInSelectedModelIndex(line); selectedLineIdx > -1) {
        m_selectedLines.removeAt(selectedLineIdx);
    } else {
        m_selectedLines.push_back(line);
    }

    emit selectedLinesCountChanged(m_selectedLines.size());
}

int ConnectionLinesModel::lineInSelectedModelIndex(QQuickItem *line) const
{
    int idx = -1;
    for(int i = 0; i < m_selectedLines.size(); i++) {
        if(m_selectedLines.at(i) == line) {
            idx = i;
            break;
        }
    }

    return idx;
}
