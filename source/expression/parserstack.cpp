#include "parserstack.h"

/*!
 * \brief ParserStack::ParserStack
 * Constructor
 */
ParserStack::ParserStack() :
    m_bracketsDepth(0)
{}

/*!
 * \brief ParserStack::parentBlock
 * Get current parent block
 * \return
 */
CalculationBlock *ParserStack::parentBlock() const
{
    return m_parentBlocks.top();
}

/*!
 * \brief ParserStack::hasParentBlock
 * Check if there is any parent block
 * \return
 */
bool ParserStack::hasParentBlock() const
{
    return !m_parentBlocks.isEmpty();
}

/*!
 * \brief ParserStack::addParentBlock
 * Add new parent block
 * \param parentBlock
 */
void ParserStack::addParentBlock(CalculationBlock *parentBlock)
{
    m_parentBlocks.push(parentBlock);
}

/*!
 * \brief ParserStack::removeParentBlock
 * Remove parent block
 * \return
 */
CalculationBlock *ParserStack::removeParentBlock()
{
    return m_parentBlocks.pop();
}

/*!
 * \brief ParserStack::blockParsingCount
 * Get count of block parsing
 * \param block
 * \return
 */
int ParserStack::blockParsingCount(CalculationBlock *block) const
{
    return m_parsedSourceBlock.value(block);
}

/*!
 * \brief ParserStack::incrementBlockParsingCount
 * Increment block parsing count
 * \param block
 */
void ParserStack::incrementBlockParsingCount(CalculationBlock *block)
{
    m_parsedSourceBlock[block]++;
}

/*!
 * \brief ParserStack::bracketsDepth
 * Get brackets depth
 * \return
 */
int ParserStack::bracketsDepth() const
{
    return m_bracketsDepth;
}

/*!
 * \brief ParserStack::currentBracketsOpenBlock
 * Get last block ehich opens the brackets
 * \return
 */
CalculationBlock *ParserStack::currentBracketsOpenBlock() const
{
    return m_bracketsOpenBlocks.top();
}

/*!
 * \brief ParserStack::openBracket
 * Open brackets on the block
 * \param block
 */
void ParserStack::openBracket(CalculationBlock *block)
{
    m_bracketsOpenBlocks.push(block);
    m_bracketsDepth++;
}

/*!
 * \brief ParserStack::closeBracket
 * Close last brackets
 */
void ParserStack::closeBracket()
{
    m_bracketsOpenBlocks.pop();
    m_bracketsDepth--;
}
