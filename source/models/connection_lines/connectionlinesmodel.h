#ifndef CONNECTIONLINESMODEL_H
#define CONNECTIONLINESMODEL_H

#include <QObject>

class QQuickItem;
/*!
 * \brief The ConnectionLinesModel class
 * Provides model of Lines, which connect blocks
 */
class ConnectionLinesModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int linesCount READ linesCount NOTIFY linesCountChanged)
    Q_PROPERTY(int selectedLinesCount READ selectedLinesCount NOTIFY selectedLinesCountChanged)
public:
    explicit ConnectionLinesModel(QObject *parent = nullptr);

    int linesCount() const;
    int selectedLinesCount() const;

    Q_INVOKABLE void addLine(QQuickItem *line);
    Q_INVOKABLE void removeLine(QQuickItem *line);
    Q_INVOKABLE void removeSelectedLines();
    Q_INVOKABLE void toggleLineSelectionStatus(QQuickItem *line);

    void deselectAllLines();

signals:
    void linesCountChanged(int linesCount);
    void selectedLinesCountChanged(int selectedLinesCount);

private:
    int lineInSelectedModelIndex(QQuickItem *line) const;

private:
    QVector<QQuickItem*> m_lines;           ///< Vector of all lines on the Scope
    QVector<QQuickItem*> m_selectedLines;   ///< Vector of selected lines on the Scope
};

#endif // CONNECTIONLINESMODEL_H
