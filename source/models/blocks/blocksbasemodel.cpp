#include "blocksbasemodel.h"

BlocksBaseModel::BlocksBaseModel(QObject *parent) :
    QAbstractListModel(parent)
{}

int BlocksBaseModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_blocks.size();
}

QVariant BlocksBaseModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid()) {
        const auto idx    = index.row();
        const auto &block = m_blocks.at(idx);
        switch (role) {
            case TypeRole:
                return block.type();
            case ValueRole:
                return block.value();
            case IsDestinationRole:
                return block.isDestination();
            case IsSourceRole:
                return block.isSource();
            case InputCountRole:
                return block.inputCount();
        }
    }

    return {};
}

bool BlocksBaseModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid()) {
        const auto idx  = index.row();
        auto &block     = m_blocks[idx];
        if(canModifyValue(block)) {
            if(role == ValueRole) {
                block.setValue(value.toString());

                emit dataChanged(index, index, {ValueRole});
                return true;
            }
        }
    }

    return false;
}

QHash<int, QByteArray> BlocksBaseModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TypeRole]          = "type";
    roles[ValueRole]         = "value";
    roles[IsDestinationRole] = "isDestination";
    roles[IsSourceRole]      = "isSource";
    roles[InputCountRole]    = "inputCount";

    return roles;
}

QList<CalculationBlock>::const_iterator BlocksBaseModel::cbegin() const
{
    return m_blocks.cbegin();
}

QList<CalculationBlock>::const_iterator BlocksBaseModel::cend() const
{
    return m_blocks.cend();
}

void BlocksBaseModel::addBlock(const int type)
{
    CalculationBlock block{static_cast<CalculationBlock::Type>(type)};
    addBlock(block);
}

void BlocksBaseModel::addBlock(const CalculationBlock &block)
{
    beginInsertRows(QModelIndex{}, m_blocks.size(), m_blocks.size());
    m_blocks.push_back(block);
    endInsertRows();
}

CalculationBlock *BlocksBaseModel::blockAt(const int blockIdx)
{
    return &m_blocks[blockIdx];
}

bool BlocksBaseModel::canModifyValue(const CalculationBlock &block) const
{
    return false;
}
