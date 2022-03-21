#ifndef CALCULATIONENGINE_H
#define CALCULATIONENGINE_H

#include <QObject>

/*!
 * \brief The CalculationEngine class
 * Engine used to parse the expression.
 */
class CalculationEngine : public QObject
{
    Q_OBJECT
public:
    explicit CalculationEngine(QObject *parent = nullptr);

    void parseCalculationExpression(const QString &expression);

signals:
    void parsingError(const QString reason); ///< detected parsing error
    void parsingSuccessful(qreal result);    ///< parsing successful with given result
};

#endif // CALCULATIONENGINE_H
