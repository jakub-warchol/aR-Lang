#ifndef PARSERSTACK_H
#define PARSERSTACK_H

#include <QStack>
#include <QHash>

class CalculationBlock;
/*!
 * \brief The ParserStack class
 * Represents stack of the parsing blocks into the infix expression
 */
class ParserStack
{
public:
    explicit ParserStack();

    CalculationBlock* parentBlock() const;
    bool hasParentBlock() const;
    void addParentBlock(CalculationBlock *parentBlock);
    CalculationBlock* removeParentBlock();

    int blockParsingCount(CalculationBlock *block) const;
    void incrementBlockParsingCount(CalculationBlock *block);

    int bracketsDepth() const;
    CalculationBlock* currentBracketsOpenBlock() const;
    void openBracket(CalculationBlock *block);
    void closeBracket();

private:
    QHash<CalculationBlock*, int> m_parsedSourceBlock;  ///< Hash of blocks, ehich contains count of entering during parsing
    QStack<CalculationBlock*> m_bracketsOpenBlocks;     ///< Stack of blocks which open the brackets
    QStack<CalculationBlock*> m_parentBlocks;           ///< Stack of parent (operation) blocks which source block are currently parsing
    int m_bracketsDepth;                                ///< Count of brackets depth
};

#endif // PARSERSTACK_H
