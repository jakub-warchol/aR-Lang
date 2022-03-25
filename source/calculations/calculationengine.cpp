#include "calculationengine.h"

#include <QtMath>

static int wagaOperatora(QChar input){
    int waga = 0;

    switch (input.toLatin1()){
    case '+':
        waga = 1;
        break;

    case '-':
        waga = 1;
        break;

    case '*':
        waga = 2;
        break;

    case '/':
        waga = 2;
        break;

    case '^':
        waga = 3;
        break;
    }

    return waga;
}

static double operation(double a, double b, QChar op){
    //Perform operation
    if(op == '+')
        return a + b;
    else if(op == '-')
        return a - b;
    else if(op == '*')
        return a * b;
    else if(op == '/')
        return a / b;
    else if(op == '^')
        return qPow(a,b); //find b^a
    else
        return INT_MIN; //return negative infinity
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

    QString stos;
    QString symbole;
    QChar lastSymbol;

    for (QChar symbol : input){
        if ((symbol.isDigit() || symbol == '.') || (symbol == '-' && !lastSymbol.isDigit())){
            stos.append(symbol);
        }else if(symbol == '('){
            symbole.append(symbol);
        }else if(symbol == ')'){
            while (symbole.back() != '('){
                stos.append(" ");
                stos.append(symbole.back());
                symbole.chop(1);
            }
            symbole.chop(1);
        }else{
            stos.append(" ");
            if (symbole.isEmpty()){
                symbole.append(symbol);
            }else{

                while (true){
                    if (symbol == '^'){ //prawostronna operacja
                        if (wagaOperatora(symbol) < wagaOperatora(symbole.back())){
                            stos.append(symbole.back());
                            symbole.chop(1);
                            stos.append(" ");
                        }else{
                            break;
                        }
                    }else{
                        if (wagaOperatora(symbol) <= wagaOperatora(symbole.back())){
                            stos.append(symbole.back()); //front i back
                            symbole.chop(1);
                            stos.append(" ");
                        }else{
                            break;
                        }
                    }

                    if (symbole.isEmpty()){
                        break;
                    }
                }

                symbole.append(symbol);
            }
        }
        lastSymbol = symbol;

    }

    std::reverse(symbole.begin(), symbole.end()); //odwrotna kolesnosc

    for (QChar symbol : symbole){
        stos += ' ' + symbol;
    }

    QString number;
    QList<double> stk;
    stos += ' ';

    for (QChar symbol : qAsConst(stos)) {
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
