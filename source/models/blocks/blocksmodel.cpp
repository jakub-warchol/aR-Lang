#include "blocksmodel.h"

#include <QDebug>

/*!
 * \brief BlocksModel::BlocksModel
 * Constructor
 * \param parent
 */
BlocksModel::BlocksModel(QObject *parent) : BlocksBaseModel(parent)
{
    addBlock(CalculationBlock::Number, 0.02, 0.03);
    addBlock(CalculationBlock::Number, 0.01, 0.31);
    addBlock(CalculationBlock::Number, 0.29, 0.67);
    addBlock(CalculationBlock::Add, 0.17, 0.14);
    addBlock(CalculationBlock::Multiplication, 0.4, 0.35);
    addBlock(CalculationBlock::Result, 0.66, 0.35);
    addBlock(CalculationBlock::Substraction, 0.53, 0.35);
    addBlock(CalculationBlock::Number, 0.52, 0.25);
    addBlock(CalculationBlock::Number, 0.51, 0.28);
    addBlock(CalculationBlock::Division, 0.53, 0.35);
    addBlock(CalculationBlock::Number, 0.52, 0.25);
}

/*!
 * \brief BlocksModel::data
 * Get data's role for given index
 * \param index
 * \param role
 * \return
 */
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

/*!
 * \brief BlocksModel::setData
 * Set data's role for given index
 * \param index
 * \param value
 * \param role
 * \return
 */
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

/*!
 * \brief BlocksModel::roleNames
 * Get QML's role names
 * \return
 */
QHash<int, QByteArray> BlocksModel::roleNames() const
{
    auto roles = BlocksBaseModel::roleNames();
    roles[PosXRole]     = "x";
    roles[PosYRole]     = "y";
    roles[ModifiedRole] = "canModified";
    roles[SelectedRole] = "selected";

    return roles;
}

/*!
 * \brief BlocksModel::addBlock
 * Add block with given type and ccordination
 * \param type
 * \param xPos
 * \param yPos
 */
void BlocksModel::addBlock(const int type, qreal xPos, qreal yPos)
{
    CalculationBlock block{static_cast<CalculationBlock::Type>(type), xPos, yPos};
    BlocksBaseModel::addBlock(block);
}

/*!
 * \brief BlocksModel::duplicateSelectedBlocks
 * Duplicate selected blocks
 */
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

    deselectAllBlocks();
}

/*!
 * \brief BlocksModel::removeSelectedBlocks
 * Remove selected blocks
 */
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

/*!
 * \brief BlocksModel::attachBlocks
 * Attack source block to teth taret block on given input
 * \param sourceBlockIdx
 * \param targetBlockIdx
 * \param inputIdx
 */
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

/*!
 * \brief BlocksModel::detachBlocks
 * Detach source block from target block
 * \param sourceBlockIdx
 * \param targetBlockIdx
 */
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

/*!
 * \brief BlocksModel::deselectAllBlocks
 * Deselect all blocks on the scope
 */
void BlocksModel::deselectAllBlocks()
{
    for(int i = 0; i < m_blocks.size(); i++) {
        if(m_blocks.at(i).selected()) {
            setData(index(i), false, SelectedRole);
        }
    }
}

/*!
 * \brief BlocksModel::canModifyValue
 * Reimplementation from BlocksBaseModel
 * \param block
 * \return
 */
bool BlocksModel::canModifyValue(const CalculationBlock &block) const
{
    return block.type() == CalculationBlock::Number;
}
