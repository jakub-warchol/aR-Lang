#include "addblocksmodel.h"

AddBlocksModel::AddBlocksModel(QObject *parent) : BlocksBaseModel(parent)
{
    addBlock(CalculationBlock::Number);
    addBlock(CalculationBlock::Result);
    addBlock(CalculationBlock::Add);
    addBlock(CalculationBlock::Substraction);
    addBlock(CalculationBlock::Multiplication);
    addBlock(CalculationBlock::Division);
    addBlock(CalculationBlock::Exponentation);
    addBlock(CalculationBlock::Root);
}
