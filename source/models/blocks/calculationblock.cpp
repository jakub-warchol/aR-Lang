#include "calculationblock.h"

#include <QMap>
#include <QDebug>

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

/*!
 * \brief CalculationBlock::CalculationBlock
 * Constructor, which create block from given type and position coordinates
 * \param type
 * \param x
 * \param y
 */
CalculationBlock::CalculationBlock(Type type, qreal x, qreal y) : CalculationBlock(type, x, y, valueMapper.value(type))
{}

/*!
 * \brief CalculationBlock::CalculationBlock
 * Full constructor
 * \param type
 * \param x
 * \param y
 * \param value
 */
CalculationBlock::CalculationBlock(CalculationBlock::Type type, qreal x, qreal y, const QString &value) :
    m_type(type),
    m_value(value),
    m_isDestination(type != Number),
    m_isSource(type != Result),
    m_xPos(x),
    m_yPos(y),
    m_selected(false)
{
    if(type == Number) {
        m_inputCount = 0;
    } else if(type == Result) {
        m_inputCount = 1;
    } else {
        m_inputCount = 2;
    }

    m_sourceBlocksIdx.resize(m_inputCount);
    m_sourceBlocksIdx.fill(-1);
}

/*!
 * \brief CalculationBlock::CalculationBlock
 * Copy constructor
 * \param other
 */
CalculationBlock::CalculationBlock(const CalculationBlock &other) :
    m_type(other.type()),
    m_value(other.value()),
    m_isDestination(other.isDestination()),
    m_isSource(other.isSource()),
    m_inputCount(other.inputCount()),
    m_xPos(other.xPos()),
    m_yPos(other.yPos()),
    m_selected(false)
{
    m_sourceBlocksIdx.resize(m_inputCount);
    m_sourceBlocksIdx.fill(-1);
}

/*!
 * \brief CalculationBlock::type
 * Get block type
 * \return
 */
CalculationBlock::Type CalculationBlock::type() const
{
    return m_type;
}

/*!
 * \brief CalculationBlock::setType
 * Set block type
 * \param type
 */
void CalculationBlock::setType(const Type &type)
{
    m_type = type;
}

/*!
 * \brief CalculationBlock::value
 * Get block value
 * \return
 */
QString CalculationBlock::value() const
{
    return m_value;
}

/*!
 * \brief CalculationBlock::setValue
 * Set block value
 * \param value
 */
void CalculationBlock::setValue(const QString &value)
{
    m_value = value;
}

/*!
 * \brief CalculationBlock::isDestination
 * Get is block destination
 * \return
 */
bool CalculationBlock::isDestination() const
{
    return m_isDestination;
}

/*!
 * \brief CalculationBlock::setIsDestination
 * Set block is destination
 * \param isDestination
 */
void CalculationBlock::setIsDestination(bool isDestination)
{
    m_isDestination = isDestination;
}

/*!
 * \brief CalculationBlock::isSource
 * Get is block a source
 * \return
 */
bool CalculationBlock::isSource() const
{
    return m_isSource;
}

/*!
 * \brief CalculationBlock::setIsSource
 * Set block as sourcce
 * \param isSource
 */
void CalculationBlock::setIsSource(bool isSource)
{
    m_isSource = isSource;
}

/*!
 * \brief CalculationBlock::inputCount
 * Get block's input count
 * \return
 */
int CalculationBlock::inputCount() const
{
    return m_inputCount;
}

/*!
 * \brief CalculationBlock::setInputCount
 * Set block's input count
 * \param inputCount
 */
void CalculationBlock::setInputCount(int inputCount)
{
    m_inputCount = inputCount;
}

/*!
 * \brief CalculationBlock::xPos
 * Get position of x
 * \return
 */
qreal CalculationBlock::xPos() const
{
    return m_xPos;
}

/*!
 * \brief CalculationBlock::setXPos
 * Set position of x
 * \param xPos
 */
void CalculationBlock::setXPos(const qreal &xPos)
{
    m_xPos = xPos;
}

/*!
 * \brief CalculationBlock::yPos
 * Get position of y
 * \return
 */
qreal CalculationBlock::yPos() const
{
    return m_yPos;
}

/*!
 * \brief CalculationBlock::setYPos
 * Set position of y
 * \param yPos
 */
void CalculationBlock::setYPos(const qreal &yPos)
{
    m_yPos = yPos;
}

/*!
 * \brief CalculationBlock::sourceBlockAt
 * Get source block index on given input
 * \param inputIdx
 * \return
 */
int CalculationBlock::sourceBlockAt(const int inputIdx) const
{
    return m_sourceBlocksIdx.at(inputIdx);
}

/*!
 * \brief CalculationBlock::setSourceBlockAt
 * Set source block index on given input
 * \param inputIdx
 * \param sourceBlockIdx
 */
void CalculationBlock::setSourceBlockAt(const int inputIdx, const int sourceBlockIdx)
{
    m_sourceBlocksIdx[inputIdx] = sourceBlockIdx;
}

/*!
 * \brief CalculationBlock::inputOfSource
 * Get input index of given source block index (-1 if there is no connection)
 * \param sourceBlockIdx
 * \return
 */
int CalculationBlock::inputOfSource(const int sourceBlockIdx) const
{
    auto it = std::find(m_sourceBlocksIdx.cbegin(), m_sourceBlocksIdx.cend(), sourceBlockIdx);
    return it != m_sourceBlocksIdx.cend() ? std::distance(m_sourceBlocksIdx.cbegin(), it) : -1;
}

/*!
 * \brief CalculationBlock::selected
 * Get selection status
 * \return
 */
bool CalculationBlock::selected() const
{
    return m_selected;
}

/*!
 * \brief CalculationBlock::setSelected
 * Set selection status
 * \param selected
 */
void CalculationBlock::setSelected(bool selected)
{
    m_selected = selected;
}
