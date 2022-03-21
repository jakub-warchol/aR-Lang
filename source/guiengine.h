#ifndef GUIENGINE_H
#define GUIENGINE_H

#include <QObject>

#include "models/blocks/blocksmodel.h"
#include "models/errors/errormodel.h"

class CalculationEngine;
/*!
 * \brief The GuiEngine class
 * Provide a bridge to communication between C++ and QML.
 * The class instance is registered and allowed in QML as a <i>guiEngine</i>
 */
class GuiEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BlocksModel* blocksModel READ blocksModel CONSTANT)
    Q_PROPERTY(ErrorModel* errorsModel READ errorsModel CONSTANT)
public:
    explicit GuiEngine(QObject *parent = nullptr);

    BlocksModel* blocksModel() const;
    ErrorModel* errorsModel() const;

    Q_INVOKABLE void aboutQt();
    Q_INVOKABLE void startCalculation();
    Q_INVOKABLE void loadFromFile(const QString filePath);
    Q_INVOKABLE void saveToFile(const QString filePath);

signals:
    void calculationStarted();                      ///< notify that calclation was started
    void calculationSucceeded(qreal result);        ///< notify that calculation finished successful with given result
    void calculationError(const QString reason);    ///< notify that <i>error</i> occured during parsing

private:
    QString prepareCalculationExpression(const CalculationBlock &resultBlock);

private:
    BlocksModel* m_blocksModel;             ///< Instance of BlocksModel on the Scope
    ErrorModel* m_errorsModel;              ///< Intance of ErrorModel

    CalculationEngine* m_calculationEngine; ///< Instance of CalculationEngine
};

#endif // GUIENGINE_H
