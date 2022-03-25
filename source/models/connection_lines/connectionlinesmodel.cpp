#include "connectionlinesmodel.h"

#include <QQuickItem>

/*!
 * \brief ConnectionLinesModel::ConnectionLinesModel
 * Constructor
 * \param parent
 */
ConnectionLinesModel::ConnectionLinesModel(QObject *parent) : QObject(parent)
{}

/*!
 * \brief ConnectionLinesModel::linesCount
 * Get lines count
 * \return
 */
int ConnectionLinesModel::linesCount() const
{
    return m_lines.size();
}

/*!
 * \brief ConnectionLinesModel::selectedLinesCount
 * Get selected lines count
 * \return
 */
int ConnectionLinesModel::selectedLinesCount() const
{
    return m_selectedLines.size();
}

/*!
 * \brief ConnectionLinesModel::addLine
 * Add line to model
 * \param line
 */
void ConnectionLinesModel::addLine(QQuickItem *line)
{
    m_lines.push_back(line);
    emit linesCountChanged(m_lines.size());
}

/*!
 * \brief ConnectionLinesModel::removeLine
 * Remove line from model
 * \param line
 */
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

/*!
 * \brief ConnectionLinesModel::removeSelectedLines
 * Remove selected lines
 */
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

/*!
 * \brief ConnectionLinesModel::toggleLineSelectionStatus
 * Toggle selection status of line
 * \param line
 */
void ConnectionLinesModel::toggleLineSelectionStatus(QQuickItem *line)
{
    if(auto selectedLineIdx = lineInSelectedModelIndex(line); selectedLineIdx > -1) {
        m_selectedLines.removeAt(selectedLineIdx);
    } else {
        m_selectedLines.push_back(line);
    }

    emit selectedLinesCountChanged(m_selectedLines.size());
}

/*!
 * \brief ConnectionLinesModel::deselectAllLines
 * Deselect all ines on the Scope
 */
void ConnectionLinesModel::deselectAllLines()
{
    for(auto &line : m_selectedLines) {
        toggleLineSelectionStatus(line);
        line->setProperty("selected", false);
    }
}

/*!
 * \brief ConnectionLinesModel::lineInSelectedModelIndex
 * Get index of the line in the selected model
 * \param line
 * \return
 */
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
