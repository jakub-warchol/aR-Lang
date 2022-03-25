#ifndef PARSERSTACK_H
#define PARSERSTACK_H

#include <QStack>
#include <QHash>

class CalculationBlock;
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
    QHash<CalculationBlock*, int> m_parsedSourceBlock;
    QStack<CalculationBlock*> m_bracketsOpenBlocks;
    QStack<CalculationBlock*> m_parentBlocks;
    int m_bracketsDepth;
};

#endif // PARSERSTACK_H
