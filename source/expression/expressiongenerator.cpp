#include "expressiongenerator.h"
#include "source/models/blocks/blocksmodel.h"
#include "parserstack.h"

#include <QDebug>

static QMap<CalculationBlock::Type, QString> operationToStringMapper = {
    {CalculationBlock::Add, QStringLiteral("+")},
    {CalculationBlock::Substraction, QStringLiteral("-")},
    {CalculationBlock::Multiplication, QStringLiteral("*")},
    {CalculationBlock::Division, QStringLiteral("/")},
    {CalculationBlock::Exponentation, QStringLiteral("^")},
    {CalculationBlock::Root, QStringLiteral("^")},
};

static QString swapRoot2Power(QString root) {
    auto rootValue = root.toDouble();
    if(rootValue <= 0) {
        return QString{};
    } else {
        return QString::number(1. / rootValue);
    }
}

static bool canDivideBy(const QString &divider) {
    auto dividerValue = divider.toDouble();
    return dividerValue != 0.;
}

/*!
 * \brief ExpressionGenerator::ExpressionGenerator
 * Constructor
 * \param blocksModel
 * \param parent
 */
ExpressionGenerator::ExpressionGenerator(BlocksModel *blocksModel, QObject *parent) :
    QObject(parent),
    m_blocksModel(blocksModel)
{}

/*!
 * \brief ExpressionGenerator::generateExpression
 * Try to generate infix expression from blocks, which meet in given resultBlock
 * \param resultBlock
 * \return generating status
 */
bool ExpressionGenerator::generateExpression(const CalculationBlock &resultBlock)
{
    m_errorString.clear();
    m_generatedExpression.clear();

    auto currentBlockIdx = resultBlock.sourceBlockAt(0);
    if(currentBlockIdx == -1) {
       m_errorString = tr("No block attached to Result");
        return false;
    }

    ParserStack parserStack{};
    auto currentBlock = m_blocksModel->blockAt(currentBlockIdx);
    parserStack.addParentBlock(currentBlock);

    while(parserStack.hasParentBlock()) {
        if(currentBlock->type() == CalculationBlock::Number) {
            auto parentBlock = parserStack.parentBlock();
            if(parentBlock->type() == CalculationBlock::Root && parserStack.blockParsingCount(parentBlock) > 1) {
                if(auto powValue = swapRoot2Power(currentBlock->value()); powValue.isEmpty()) { // degree of root cannot be negative or zero
                    m_errorString = tr("The root's degree is equaled or less than 0!");
                    return false;
                } else {
                    m_generatedExpression += powValue;
                }
            } else if(parentBlock->type() == CalculationBlock::Division && parserStack.blockParsingCount(parentBlock) > 1){
                if(canDivideBy(currentBlock->value())) {
                    m_generatedExpression += currentBlock->value();
                } else {
                    m_errorString = tr("Cannot divide by 0!");
                    return false;
                }
            } else {
                m_generatedExpression += currentBlock->value();
            }

            if(currentBlock == parentBlock) { // handle case, when only one number block is attached to result
                break;
            }

            currentBlock = parentBlock;
        } else {
            if(auto inputIdx = parserStack.blockParsingCount(currentBlock); inputIdx == 0) {
                auto childBlockIdx = currentBlock->sourceBlockAt(0);
                if(childBlockIdx == -1) {
                    m_errorString = tr("One of the source not attached to block");
                    return false;
                }

                parserStack.addParentBlock(currentBlock);
                parserStack.incrementBlockParsingCount(currentBlock);
//                parserStack.openBracket(currentBlock);
                currentBlock = m_blocksModel->blockAt(childBlockIdx);
//                m_generatedExpression += QStringLiteral("(");
            } else if(inputIdx < currentBlock->inputCount()){
                auto childBlockIdx = currentBlock->sourceBlockAt(inputIdx);
                if(childBlockIdx == -1) {
                    m_errorString = tr("One of the source not attached to block");
                    return false;
                }

                m_generatedExpression += operationToStringMapper[currentBlock->type()];
                parserStack.incrementBlockParsingCount(currentBlock);
                currentBlock = m_blocksModel->blockAt(childBlockIdx);
            } else if(parserStack.hasParentBlock()) {
//                if(currentBlock == parserStack.currentBracketsOpenBlock()) {
//                    m_generatedExpression += QStringLiteral(")");
//                    parserStack.closeBracket();
//                }

                currentBlock = parserStack.removeParentBlock();
            } else {
                break;
            }
        }
    }

//    if(parserStack.bracketsDepth() > 0) {
//        m_generatedExpression += QStringLiteral(")");
//    }

    qDebug() << "Generated expression:" << m_generatedExpression;
    return true;
}

/*!
 * \brief ExpressionGenerator::generatedExpression
 * Get last generated expression
 * \return
 */
QString ExpressionGenerator::generatedExpression() const
{
    return m_generatedExpression;
}

/*!
 * \brief ExpressionGenerator::errorString
 * Get last occured string
 * \return
 */
QString ExpressionGenerator::errorString() const
{
    return m_errorString;
}
