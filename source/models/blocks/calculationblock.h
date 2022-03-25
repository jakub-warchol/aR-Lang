#ifndef CALCULATIONBLOCK_H
#define CALCULATIONBLOCK_H

#include <QString>
#include <QVector>

/*!
 * \brief The CalculationBlock class
 * Represents block of operation or number, which is used
 * on the Scope
 */
class CalculationBlock
{
public:
    /*!
     * \brief The Type enum
     * Type of block
     */
    enum Type {
        Number,         ///< Number
        Add,            ///< Add
        Substraction,   ///< Substraction
        Multiplication, ///< Multiplication
        Division,       ///< Division
        Exponentation,  ///< Exponentation
        Root,           ///< Root
        Result,         ///< Operation result
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
    Type m_type;                    ///< Type of block
    QString m_value;                ///< Value og block
    bool m_isDestination;           ///< Is block destination
    bool m_isSource;                ///< Is block source
    int m_inputCount;               ///< Input block count
    qreal m_xPos;                   ///< Block's position of x
    qreal m_yPos;                   ///< Block's position of y
    QVector<int> m_sourceBlocksIdx; ///< Indices of ssource blocks attached
    bool m_selected;                ///< Is block selected
};

#endif // CALCULATIONBLOCK_H
