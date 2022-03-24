#ifndef SELECTEDBLOCKSMODEL_H
#define SELECTEDBLOCKSMODEL_H

#include <QSortFilterProxyModel>

class SelectedBlocksModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit SelectedBlocksModel(QObject *parent = nullptr);

protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // SELECTEDBLOCKSMODEL_H
