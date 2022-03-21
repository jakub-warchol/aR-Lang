#include "guiengine.h"
#include "source/calculations/calculationengine.h"

#include <QApplication>

/*!
 * \brief GuiEngine::GuiEngine
 * Constructor of GuiEngine
 * \param parent
 */
GuiEngine::GuiEngine(QObject *parent) : QObject(parent)
{
    m_blocksModel = new BlocksModel(this);
    m_errorsModel = new ErrorModel(this);
    m_calculationEngine = new CalculationEngine(this);

    connect(this, &GuiEngine::calculationStarted, m_errorsModel, &ErrorModel::clearErrors);
    connect(this, &GuiEngine::calculationError, m_errorsModel, &ErrorModel::addError);

    connect(m_calculationEngine, &CalculationEngine::parsingError, this, &GuiEngine::calculationError);
    connect(m_calculationEngine, &CalculationEngine::parsingSuccessful, this, &GuiEngine::calculationSucceeded);
}

/*!
 * \brief GuiEngine::blocksModel
 * Get BlocksModel instance
 * \return
 */
BlocksModel *GuiEngine::blocksModel() const
{
    return m_blocksModel;
}

/*!
 * \brief GuiEngine::errorsModel
 * Get ErrorModel instance
 * \return
 */
ErrorModel *GuiEngine::errorsModel() const
{
    return m_errorsModel;
}

/*!
 * \brief GuiEngine::aboutQt
 * Show aboutQt dialog
 */
void GuiEngine::aboutQt()
{
    qApp->aboutQt();
}

/*!
 * \brief GuiEngine::startCalculation
 * Start calculation with blocks on the Scope
 */
void GuiEngine::startCalculation()
{
    emit calculationStarted();

    // find result block
    auto getResultBlock = [](const CalculationBlock &block) {
        return block.type() == CalculationBlock::Result;
    };

    auto resultBlocksCount = std::count_if(m_blocksModel->cbegin(), m_blocksModel->cend(), getResultBlock);
    if(resultBlocksCount == 0) {
        emit calculationError(tr("No Result block found"));
        return;
    } else if(resultBlocksCount > 1) {
        emit calculationError(tr("Multiple Result Block on the Scope"));
        return;
    }

    // start creating expression
    // there is no need to check if resultIt is valid (we've checked it previously)
    auto resultIt = std::find_if(m_blocksModel->cbegin(), m_blocksModel->cend(), getResultBlock);
    auto expression = prepareCalculationExpression(*resultIt);
    if(expression.isEmpty()) {
        emit calculationError(tr("Generated equation is empty"));
        return;
    }

    m_calculationEngine->parseCalculationExpression(expression);
}

/*!
 * \brief GuiEngine::loadFromFile
 * Load blocks from file with given <i>filePath</i>
 * \param filePath
 */
void GuiEngine::loadFromFile(const QString filePath)
{

}

/*!
 * \brief GuiEngine::saveToFile
 * Save blocks to file with given <i>filePath</i>
 * \param filePath
 */
void GuiEngine::saveToFile(const QString filePath)
{

}

/*!
 * \brief GuiEngine::prepareCalculationExpression
 * Prepare expression from blocks that joined in given <i>resultBlock</i>
 * \param resultBlock
 * \return
 */
QString GuiEngine::prepareCalculationExpression(const CalculationBlock &resultBlock)
{
    QString expr;

    return expr;
}
