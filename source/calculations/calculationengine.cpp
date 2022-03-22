#include "calculationengine.h"

int wagaOperatora(QChar input){
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

double operation(double a, double b, QChar op){
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
        return pow(a,b); //find b^a
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
    //QString input = "-42+-2*3.3^-2.1*52.89^2*-4-8^-3/-2+4+7.27--11*-1.2";
    QString input = expression;

    input.replace(",",".");

    //qDebug() << input;

    QString stos;
    QString symbole;
    QChar lastSymbol;

    for (QChar symbol : input){

        if ((symbol.isDigit() || symbol == '.') || (symbol == '-' && !lastSymbol.isDigit())){
            stos.append(symbol);
        }else{
            stos.append(" ");
            if (symbole.isEmpty()){
                symbole.append(symbol);
            }else{

                //if (wagaOperatora(symbol) wagaOperatora(stos))
                while (true){
                    //qDebug() << stos;
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

    //qDebug() << stos;

    QString number;
    QList<double> stk;
    stos += ' ';

    for (QChar symbol : stos) {
        if (symbol != ' '){
            number += symbol;
        }else{
            if (number.length()>1 || number[0].isDigit()){
                stk.append(number.toDouble());
                //qDebug() << number;
            }else{
                double a = stk.last();
                stk.removeLast();
                double b = stk.last();
                stk.removeLast();
                stk.append(operation(b,a,number[0]));
            }
            number = NULL;
        }
    }

    emit parsingSuccessful(stk.first());

    //qDebug() << stk;
}
