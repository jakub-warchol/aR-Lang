#include "blocksmodel.h"

BlocksModel::BlocksModel(QObject *parent) : BlocksBaseModel(parent)
{
    addBlock(CalculationBlock::Number, 0.02, 0.03);
    addBlock(CalculationBlock::Number, 0.01, 0.31);
    addBlock(CalculationBlock::Number, 0.29, 0.67);
    addBlock(CalculationBlock::Add, 0.17, 0.14);
    addBlock(CalculationBlock::Multiplication, 0.4, 0.35);
    addBlock(CalculationBlock::Result, 0.66, 0.35);
    addBlock(CalculationBlock::Multiplication, 0.53, 0.35);
    addBlock(CalculationBlock::Number, 0.52, 0.25);
    addBlock(CalculationBlock::Number, 0.51, 0.28);
}

QVariant BlocksModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid()) {
        const auto idx    = index.row();
        const auto &block = m_blocks.at(idx);

        switch (role) {
            case PosXRole:
                return block.xPos();
            case PosYRole:
                return block.yPos();
            case ModifiedRole:
            return canModifyValue(block);
        }
    }

    return BlocksBaseModel::data(index, role);
}

bool BlocksModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid()) {
        const auto idx = index.row();
        auto &block    = m_blocks[idx];

        if(role == PosXRole) {
            block.setXPos(value.toReal());
        } else if(role == PosYRole) {
            block.setYPos(value.toReal());
        } else {
            return BlocksBaseModel::setData(index, value, role);
        }

        emit dataChanged(index, index, {role});
    }

    return false;
}

QHash<int, QByteArray> BlocksModel::roleNames() const
{
    auto roles = BlocksBaseModel::roleNames();
    roles[PosXRole]     = "x";
    roles[PosYRole]     = "y";
    roles[ModifiedRole] = "canModified";

    return roles;
}

void BlocksModel::addBlock(const int type, qreal xPos, qreal yPos)
{
    CalculationBlock block{static_cast<CalculationBlock::Type>(type), xPos, yPos};
    BlocksBaseModel::addBlock(block);
}

void BlocksModel::attachBlocks(const int sourceBlockIdx, const int targetBlockIdx, const int inputIdx)
{
    if(targetBlockIdx >= 0 && targetBlockIdx < m_blocks.size()) {
        auto& targetBlock = m_blocks[targetBlockIdx];
        if(inputIdx < targetBlock.inputCount()) {
            targetBlock.setSourceBlockAt(inputIdx, sourceBlockIdx);
        }
    }
}

void BlocksModel::detachBlocks(const int sourceBlockIdx, const int targetBlockIdx, const int inuptIdx)
{

}

bool BlocksModel::canModifyValue(const CalculationBlock &block) const
{
    return block.type() == CalculationBlock::Number;
}
