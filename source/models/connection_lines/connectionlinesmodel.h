#ifndef CONNECTIONLINESMODEL_H
#define CONNECTIONLINESMODEL_H

#include <QObject>

class QQuickItem;
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

signals:
    void linesCountChanged(int linesCount);
    void selectedLinesCountChanged(int selectedLinesCount);

private:
    int lineInSelectedModelIndex(QQuickItem *line) const;

private:
    QVector<QQuickItem*> m_lines;
    QVector<QQuickItem*> m_selectedLines;
};

#endif // CONNECTIONLINESMODEL_H
