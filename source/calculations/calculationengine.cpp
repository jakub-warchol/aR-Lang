#include "calculationengine.h"

#include <QtMath>

static int operatorRank(QChar input){
    int rank = 0;

    switch (input.toLatin1()){
    case '+':
        rank = 1;
        break;
    case '-':
        rank = 1;
        break;
    case '*':
        rank = 2;
        break;
    case '/':
        rank = 2;
        break;
    case '^':
        rank = 3;
        break;
    }

    return rank;
}

static double operation(double a, double b, QChar op){

    switch (op.toLatin1()){
    case '+':
        return a + b;
        break;
    case '-':
        return a - b;
        break;
    case '*':
        return a * b;
        break;
    case '/':
        return a / b;
        break;
    case '^':
        return qPow(a,b);
        break;
    default:
        return INT_MIN;
        break;
    }

}

/*!
 * \brief CalculationEngine::CalculationEngine
 * Constructor of CalculationEngine
 * \param parent
 */
CalculationEngine::CalculationEngine(QObject *parent) : QObject(parent)
{}

/*!
 * \brief CalculationEngine::parseCalculationExpression
 * Start parsing given string with equation to achieve the result of that calculation expression
 * \param expression
 */
void CalculationEngine::parseCalculationExpression(const QString &expression)
{
    QString input = expression;
    input.replace(",",".");

    QString symbolsStack;
    QString symbols;
    QChar lastSymbol;

    for (QChar symbol : input){
        if ((symbol.isDigit() || symbol == '.') || (symbol == '-' && !lastSymbol.isDigit())){
            symbolsStack.append(symbol);
        }else if(symbol == '('){
            symbols.append(symbol);
        }else if(symbol == ')'){
            while (symbols.back() != '('){
                symbolsStack.append(" ");
                symbolsStack.append(symbols.back());
                symbols.chop(1);
            }
            symbols.chop(1);
        }else{
            symbolsStack.append(" ");
            if (symbols.isEmpty()){
                symbols.append(symbol);
            }else{

                while (true){
                    if (symbol == '^'){
                        if (operatorRank(symbol) < operatorRank(symbols.back())){
                            symbolsStack.append(symbols.back());
                            symbols.chop(1);
                            symbolsStack.append(" ");
                        }else{
                            break;
                        }
                    }else{
                        if (operatorRank(symbol) <= operatorRank(symbols.back())){
                            symbolsStack.append(symbols.back());
                            symbols.chop(1);
                            symbolsStack.append(" ");
                        }else{
                            break;
                        }
                    }

                    if (symbols.isEmpty()){
                        break;
                    }
                }

                symbols.append(symbol);
            }
        }
        lastSymbol = symbol;

    }

    std::reverse(symbols.begin(), symbols.end()); //odwrotna kolesnosc

    for (QChar symbol : symbols){
        symbolsStack += ' ' + symbol;
    }

    QString number;
    QList<double> stk;
    symbolsStack += ' ';

    for (QChar symbol : qAsConst(symbolsStack)) {
        if (symbol != ' '){
            number += symbol;
        }else{
            if (number.length()>1 || number[0].isDigit()){
                stk.append(number.toDouble());
            }else{
                double a = stk.last();
                stk.removeLast();
                double b = stk.last();
                stk.removeLast();
                stk.append(operation(b,a,number[0]));
            }
            number.clear();
        }
    }

    emit parsingSuccessful(stk.first());
}
