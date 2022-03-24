#include "blocksmodel.h"

#include <QDebug>

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
        case SelectedRole:
            return block.selected();
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
        } else if(role == SelectedRole) {
            block.setSelected(value.toBool());
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
    roles[SelectedRole] = "selected";

    return roles;
}

void BlocksModel::addBlock(const int type, qreal xPos, qreal yPos)
{
    CalculationBlock block{static_cast<CalculationBlock::Type>(type), xPos, yPos};
    BlocksBaseModel::addBlock(block);
}

void BlocksModel::duplicateSelectedBlocks()
{
    for(const auto &block : qAsConst(m_blocks)) {
        if(block.selected()) {
            auto yPos = block.yPos() + 0.02;
            if(yPos > 1.) {
                yPos = 1.;
            }

            CalculationBlock newBlock{block};
            newBlock.setYPos(yPos);
            BlocksBaseModel::addBlock(newBlock);
        }
    }

    //TODO: deselect all
}

void BlocksModel::removeSelectedBlocks()
{
    beginResetModel();
    for(int i = 0; i < m_blocks.size(); i++) {
        if(m_blocks.at(i).selected()) {
            m_blocks.removeAt(i);
            i--;
        }
    }
    endResetModel();
}

void BlocksModel::attachBlocks(const int sourceBlockIdx, const int targetBlockIdx, const int inputIdx)
{
    if(targetBlockIdx >= 0 && targetBlockIdx < m_blocks.size()) {
        auto& targetBlock = m_blocks[targetBlockIdx];
        if(inputIdx < targetBlock.inputCount()) {
            qDebug() << "Lead line from:" << sourceBlockIdx << "to:" << targetBlockIdx;
            targetBlock.setSourceBlockAt(inputIdx, sourceBlockIdx);
        }
    }
}

void BlocksModel::detachBlocks(const int sourceBlockIdx, const int targetBlockIdx)
{
    if(targetBlockIdx >= 0 && targetBlockIdx < m_blocks.size()) {
        auto& targetBlock = m_blocks[targetBlockIdx];
        if(auto inputIdx = targetBlock.inputOfSource(sourceBlockIdx); inputIdx > -1) {
            qDebug() << "Remove line from:" << sourceBlockIdx << "to:" << targetBlockIdx;
            targetBlock.setSourceBlockAt(inputIdx, -1);
        }
    }
}

bool BlocksModel::canModifyValue(const CalculationBlock &block) const
{
    return block.type() == CalculationBlock::Number;
}
