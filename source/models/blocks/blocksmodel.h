#ifndef BLOCKSMODEL_H
#define BLOCKSMODEL_H

#include "blocksbasemodel.h"

class BlocksModel : public BlocksBaseModel
{
    Q_OBJECT
public:
    enum Roles {
        PosXRole = Qt::UserRole + 100,
        PosYRole,
        ModifiedRole,
    };

    explicit BlocksModel(QObject *parent = nullptr);

    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addBlock(const int type, qreal xPos, qreal yPos);
    Q_INVOKABLE void attachBlocks(const int sourceBlockIdx, const int targetBlockIdx, const int inputIdx);
    Q_INVOKABLE void detachBlocks(const int sourceBlockIdx, const int targetBlockIdx, const int inuptIdx);

protected:
    virtual bool canModifyValue(const CalculationBlock &block) const override;
};

#endif // BLOCKSMODEL_H
