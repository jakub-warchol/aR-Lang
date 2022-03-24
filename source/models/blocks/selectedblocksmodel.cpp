#include "selectedblocksmodel.h"
#include "blocksmodel.h"

SelectedBlocksModel::SelectedBlocksModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    setFilterRole(BlocksModel::SelectedRole);
}

bool SelectedBlocksModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    bool accepted = false;
    if(sourceModel() != nullptr) {
        auto blockIdx = sourceModel()->index(source_row, 0, source_parent);
        if(blockIdx.isValid()) {
            if(blockIdx.data(BlocksModel::SelectedRole).toBool()) {
                accepted = true;
            }
        }
    }

    return accepted;
}
