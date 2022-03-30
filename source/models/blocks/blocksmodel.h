#ifndef BLOCKSMODEL_H
#define BLOCKSMODEL_H

#include "blocksbasemodel.h"

/*!
 * \brief The BlocksModel class
 * Represents blocks on the Scope
 */
class BlocksModel : public BlocksBaseModel
{
    Q_OBJECT
public:
    /*!
     * \brief The Roles enum
     * Data's role
     */
    enum Roles {
        PosXRole = Qt::UserRole + 100,
        PosYRole,
        ModifiedRole,
        SelectedRole,
    };

    explicit BlocksModel(QObject *parent = nullptr);

    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addBlock(const int type, qreal xPos, qreal yPos);
    Q_INVOKABLE void duplicateSelectedBlocks();
    Q_INVOKABLE void removeSelectedBlocks();
    Q_INVOKABLE void attachBlocks(const int sourceBlockIdx, const int targetBlockIdx, const int inputIdx);
    Q_INVOKABLE void detachBlocks(const int sourceBlockIdx, const int targetBlockIdx);

    void deselectAllBlocks();
    void clearModel();
    void refreshModel();
    void setNumberBlockValue(const int index, const QString &value);

signals:
    void blocksFromFileAttached(int sourceBlock, int targetBlock, int targetInput); ///< Signal is emmited when attaching between blocks will be detected during loading file

protected:
    virtual bool canModifyValue(const CalculationBlock &block) const override;        
};

#endif // BLOCKSMODEL_H
