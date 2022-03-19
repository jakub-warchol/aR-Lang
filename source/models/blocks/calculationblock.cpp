#include "calculationblock.h"

#include <QMap>

static QMap<CalculationBlock::Type, QString> valueMapper = {
    {CalculationBlock::Number, QStringLiteral("0")},
    {CalculationBlock::Add, QStringLiteral("+")},
    {CalculationBlock::Substraction, QStringLiteral("-")},
    {CalculationBlock::Multiplication, QStringLiteral("*")},
    {CalculationBlock::Division, QStringLiteral("/")},
    {CalculationBlock::Exponentation, QStringLiteral("pow")},
    {CalculationBlock::Root, QStringLiteral("root")},
    {CalculationBlock::Result, QStringLiteral("Result")},
};

CalculationBlock::CalculationBlock(Type type, qreal x, qreal y) : CalculationBlock(type, x, y, valueMapper.value(type))
{}

CalculationBlock::CalculationBlock(CalculationBlock::Type type, qreal x, qreal y, const QString &value) :
    m_type(type),
    m_value(value),
    m_isDestination(type != Number),
    m_isSource(type != Result),
    m_xPos(x),
    m_yPos(y)
{
    if(type == Number) {
        m_inputCount = 0;
    } else if(type == Result) {
        m_inputCount = 1;
    } else {
        m_inputCount = 2;
    }
}

CalculationBlock::Type CalculationBlock::type() const
{
    return m_type;
}

void CalculationBlock::setType(const Type &type)
{
    m_type = type;
}

QString CalculationBlock::value() const
{
    return m_value;
}

void CalculationBlock::setValue(const QString &value)
{
    m_value = value;
}

bool CalculationBlock::isDestination() const
{
    return m_isDestination;
}

void CalculationBlock::setIsDestination(bool isDestination)
{
    m_isDestination = isDestination;
}

bool CalculationBlock::isSource() const
{
    return m_isSource;
}

void CalculationBlock::setIsSource(bool isSource)
{
    m_isSource = isSource;
}

int CalculationBlock::inputCount() const
{
    return m_inputCount;
}

void CalculationBlock::setInputCount(int inputCount)
{
    m_inputCount = inputCount;
}

qreal CalculationBlock::xPos() const
{
    return m_xPos;
}

void CalculationBlock::setXPos(const qreal &xPos)
{
    m_xPos = xPos;
}

qreal CalculationBlock::yPos() const
{
    return m_yPos;
}

void CalculationBlock::setYPos(const qreal &yPos)
{
    m_yPos = yPos;
}
