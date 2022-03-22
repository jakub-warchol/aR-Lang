#ifndef EXPRESSIONGENERATOR_H
#define EXPRESSIONGENERATOR_H

#include <QObject>

class CalculationBlock;
class BlocksModel;
/*!
 * \brief The ExpressionGenerator class
 * Provide mechanism to generate expression from connected with Result blocks.
 * It also delivers simple errors' detector, which prevents from failures during a calculation process.
 */
class ExpressionGenerator : public QObject
{
    Q_OBJECT
public:
    explicit ExpressionGenerator(BlocksModel *blocksModel, QObject *parent = nullptr);

    bool generateExpression(const CalculationBlock &resultBlock);

    QString generatedExpression() const;
    QString errorString() const;

private:
    QString m_generatedExpression;  ///< Last generated expression
    QString m_errorString;          ///< Last detected error

    BlocksModel *m_blocksModel;     ///< Instance of BlocksModel
};

#endif // EXPRESSIONGENERATOR_H
