#include "parserstack.h"

ParserStack::ParserStack() :
    m_bracketsDepth(0)
{}

CalculationBlock *ParserStack::parentBlock() const
{
    return m_parentBlocks.top();
}

bool ParserStack::hasParentBlock() const
{
    return !m_parentBlocks.isEmpty();
}

void ParserStack::addParentBlock(CalculationBlock *parentBlock)
{
    m_parentBlocks.push(parentBlock);
}

CalculationBlock *ParserStack::removeParentBlock()
{
    return m_parentBlocks.pop();
}

int ParserStack::blockParsingCount(CalculationBlock *block) const
{
    return m_parsedSourceBlock.value(block);
}

void ParserStack::incrementBlockParsingCount(CalculationBlock *block)
{
    m_parsedSourceBlock[block]++;
}

int ParserStack::bracketsDepth() const
{
    return m_bracketsDepth;
}

CalculationBlock *ParserStack::currentBracketsOpenBlock() const
{
    return m_bracketsOpenBlocks.top();
}

void ParserStack::openBracket(CalculationBlock *block)
{
    m_bracketsOpenBlocks.push(block);
    m_bracketsDepth++;
}

void ParserStack::closeBracket()
{
    m_bracketsOpenBlocks.pop();
    m_bracketsDepth--;
}
