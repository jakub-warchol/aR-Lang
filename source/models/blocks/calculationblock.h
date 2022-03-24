#ifndef CALCULATIONBLOCK_H
#define CALCULATIONBLOCK_H

#include <QString>
#include <QVector>

class CalculationBlock
{
public:
    enum Type {
        Number,
        Add,
        Substraction,
        Multiplication,
        Division,
        Exponentation,
        Root,
        Result,
    };

    explicit CalculationBlock(Type type, qreal x = 0., qreal y = 0.);
    explicit CalculationBlock(Type type, qreal x, qreal y, const QString &value);
    explicit CalculationBlock(const CalculationBlock &other);

    Type type() const;
    void setType(const Type &type);

    QString value() const;
    void setValue(const QString &value);

    bool isDestination() const;
    void setIsDestination(bool isDestination);

    bool isSource() const;
    void setIsSource(bool isSource);

    int inputCount() const;
    void setInputCount(int inputCount);

    qreal xPos() const;
    void setXPos(const qreal &xPos);

    qreal yPos() const;
    void setYPos(const qreal &yPos);

    int sourceBlockAt(const int inputIdx) const;
    void setSourceBlockAt(const int inputIdx, const int sourceBlockIdx);

    bool selected() const;
    void setSelected(bool selected);

    int inputOfSource(const int sourceBlockIdx) const;

private:
    Type m_type;
    QString m_value;
    bool m_isDestination;
    bool m_isSource;
    int m_inputCount;
    qreal m_xPos;
    qreal m_yPos;
    QVector<int> m_sourceBlocksIdx;
    bool m_selected;
};

#endif // CALCULATIONBLOCK_H
