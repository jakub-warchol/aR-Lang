#ifndef GUIENGINE_H
#define GUIENGINE_H

#include <QObject>

#include "models/blocks/blocksmodel.h"
#include "models/blocks/selectedblocksmodel.h"
#include "models/errors/errormodel.h"
#include "models/connection_lines/connectionlinesmodel.h"

class CalculationEngine;
class ExpressionGenerator;
/*!
 * \brief The GuiEngine class
 * Provide a bridge to communication between C++ and QML.
 * The class instance is registered and allowed in QML as a <i>guiEngine</i>
 */
class GuiEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BlocksModel* blocksModel READ blocksModel CONSTANT)
    Q_PROPERTY(SelectedBlocksModel* selectedBlocksModel READ selectedBlocksModel CONSTANT)
    Q_PROPERTY(ErrorModel* errorsModel READ errorsModel CONSTANT)
    Q_PROPERTY(ConnectionLinesModel* connectionLinesModel READ connectionLinesModel CONSTANT)
public:
    explicit GuiEngine(QObject *parent = nullptr);

    BlocksModel* blocksModel() const;
    SelectedBlocksModel* selectedBlocksModel() const;
    ErrorModel* errorsModel() const;
    ConnectionLinesModel* connectionLinesModel() const;

    Q_INVOKABLE void aboutQt();
    Q_INVOKABLE void startCalculation();
    Q_INVOKABLE void loadFromFile(const QString filePath);
    Q_INVOKABLE void saveToFile(const QString filePath);
    Q_INVOKABLE void deselectAll();

signals:
    void calculationStarted();                      ///< notify that calclation was started
    void calculationSucceeded(qreal result);        ///< notify that calculation finished successful with given result
    void calculationError(const QString reason);    ///< notify that <i>error</i> occured during parsing

private:
    BlocksModel* m_blocksModel;                     ///< Instance of BlocksModel on the Scope
    SelectedBlocksModel* m_selectedBlocksModel;     ///< Instance of SelectedBlocksModel
    ErrorModel* m_errorsModel;                      ///< Intance of ErrorModel
    ConnectionLinesModel* m_connectionLinesModel;   ///< Instance of ConnectionLinesModel

    CalculationEngine* m_calculationEngine;         ///< Instance of CalculationEngine
    ExpressionGenerator* m_expressionGenerator;     ///< Instance of ExpressionGenerator
};

#endif // GUIENGINE_H
