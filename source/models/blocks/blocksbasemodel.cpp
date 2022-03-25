#include "blocksbasemodel.h"

/*!
 * \brief BlocksBaseModel::BlocksBaseModel
 * Constructor
 * \param parent
 */
BlocksBaseModel::BlocksBaseModel(QObject *parent) :
    QAbstractListModel(parent)
{}

/*!
 * \brief BlocksBaseModel::rowCount
 * count of row in the model
 * \param parent
 * \return
 */
int BlocksBaseModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_blocks.size();
}

/*!
 * \brief BlocksBaseModel::data
 * Get data's role for given index
 * \param index
 * \param role
 * \return
 */
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

/*!
 * \brief BlocksBaseModel::setData
 * Set data's role for given index
 * \param index
 * \param value
 * \param role
 * \return
 */
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

/*!
 * \brief BlocksBaseModel::roleNames
 * Get QML's role names
 * \return
 */
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

/*!
 * \brief BlocksBaseModel::cbegin
 * Get iterator to the begin of model list
 * \return
 */
QList<CalculationBlock>::const_iterator BlocksBaseModel::cbegin() const
{
    return m_blocks.cbegin();
}

/*!
 * \brief BlocksBaseModel::cend
 * Get iterator to the end of model list
 * \return
 */
QList<CalculationBlock>::const_iterator BlocksBaseModel::cend() const
{
    return m_blocks.cend();
}

/*!
 * \brief BlocksBaseModel::addBlock
 * Add block of given type
 * \param type
 */
void BlocksBaseModel::addBlock(const int type)
{
    CalculationBlock block{static_cast<CalculationBlock::Type>(type)};
    addBlock(block);
}

/*!
 * \brief BlocksBaseModel::addBlock
 * Add block
 * \param block
 */
void BlocksBaseModel::addBlock(const CalculationBlock &block)
{
    beginInsertRows(QModelIndex{}, m_blocks.size(), m_blocks.size());
    m_blocks.push_back(block);
    endInsertRows();
}

/*!
 * \brief BlocksBaseModel::blockAt
 * Get block of given idx
 * \param blockIdx
 * \return
 */
CalculationBlock *BlocksBaseModel::blockAt(const int blockIdx)
{
    return &m_blocks[blockIdx];
}

/*!
 * \brief BlocksBaseModel::canModifyValue
 * Specify if block can be modified
 * \param block
 * \return
 */
bool BlocksBaseModel::canModifyValue(const CalculationBlock &block) const
{
    return false;
}
