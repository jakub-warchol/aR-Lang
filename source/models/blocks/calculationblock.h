#ifndef CALCULATIONBLOCK_H
#define CALCULATIONBLOCK_H

#include <QString>

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

private:
    Type m_type;
    QString m_value;
    bool m_isDestination;
    bool m_isSource;
    int m_inputCount;
    qreal m_xPos;
    qreal m_yPos;
};

#endif // CALCULATIONBLOCK_H
