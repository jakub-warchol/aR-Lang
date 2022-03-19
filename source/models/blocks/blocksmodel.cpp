#include "blocksmodel.h"

BlocksModel::BlocksModel(QObject *parent) : BlocksBaseModel(parent)
{
    addBlock(CalculationBlock::Number, 0.1, 0.1);
    addBlock(CalculationBlock::Number, 0.1, 0.2);
    addBlock(CalculationBlock::Add, 0.15, 0.15);
    addBlock(CalculationBlock::Result, 0.3, 0.15);
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

bool BlocksModel::canModifyValue(const CalculationBlock &block) const
{
    return block.type() == CalculationBlock::Number;
}
