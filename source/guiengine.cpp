#include "guiengine.h"
#include "source/calculations/calculationengine.h"
#include "source/expression/expressiongenerator.h"
#include "source/files/filesmanager.h"

#include <QApplication>
#include <QDebug>

/*!
 * \brief GuiEngine::GuiEngine
 * Constructor of GuiEngine
 * \param parent
 */
GuiEngine::GuiEngine(QObject *parent) : QObject(parent)
{
    m_blocksModel           = new BlocksModel(this);
    m_selectedBlocksModel   = new SelectedBlocksModel(this);
    m_errorsModel           = new ErrorModel(this);
    m_connectionLinesModel  = new ConnectionLinesModel(this);
    m_calculationEngine     = new CalculationEngine(this);
    m_expressionGenerator   = new ExpressionGenerator(m_blocksModel, this);
    m_filesManager          = new FilesManager(this);

    m_selectedBlocksModel->setSourceModel(m_blocksModel);

    connect(this, &GuiEngine::calculationStarted, m_errorsModel, &ErrorModel::clearErrors);
    connect(this, &GuiEngine::calculationError, m_errorsModel, &ErrorModel::addError);

    connect(m_calculationEngine, &CalculationEngine::parsingError, this, &GuiEngine::calculationError);
    connect(m_calculationEngine, &CalculationEngine::parsingSuccessful, this, &GuiEngine::calculationSucceeded);

    connect(m_filesManager, &FilesManager::error, m_errorsModel, &ErrorModel::addError);
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
 * \brief GuiEngine::selectedBlocksModel
 * Get selected blocks model
 * \return
 */
SelectedBlocksModel *GuiEngine::selectedBlocksModel() const
{
    return m_selectedBlocksModel;
}

/*!
 * \brief GuiEngine::connectionLinesModel
 * Get connection lines model
 * \return
 */
ConnectionLinesModel *GuiEngine::connectionLinesModel() const
{
    return m_connectionLinesModel;
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
    auto expressionGenerated = m_expressionGenerator->generateExpression(*resultIt);
    if(expressionGenerated) { // if there weren't any errors during expression generating, start parsing
        auto expression = m_expressionGenerator->generatedExpression();
        m_calculationEngine->parseCalculationExpression(expression);
    } else { // otherwise, notify about errors
        auto generatedError = m_expressionGenerator->errorString();
        emit calculationError(tr("Parsing failed"));
        emit calculationError(generatedError);
    }
}

/*!
 * \brief GuiEngine::loadFromFile
 * Load blocks from file with given <i>filePath</i>
 * \param filePath
 */
void GuiEngine::loadFromFile(const QString filePath)
{
    m_filesManager->readFromFile(filePath);
}

/*!
 * \brief GuiEngine::saveToFile
 * Save blocks to file with given <i>filePath</i>
 * \param filePath
 */
void GuiEngine::saveToFile(const QString filePath)
{
    m_filesManager->saveToFile(filePath);
}

/*!
 * \brief GuiEngine::deselectAll
 * Deselect all lines and blocks on the Scope
 */
void GuiEngine::deselectAll()
{
    qDebug() << "Deselect all blocks and lines";
    m_blocksModel->deselectAllBlocks();
    m_connectionLinesModel->deselectAllLines();
}
