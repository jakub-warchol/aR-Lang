#ifndef BLOCKSBASEMODEL_H
#define BLOCKSBASEMODEL_H

#include <QAbstractListModel>

#include "calculationblock.h"

/*!
 * \brief The BlocksBaseModel class
 * Represents base class of blocks model
 */
class BlocksBaseModel : public QAbstractListModel
{
    Q_OBJECT
public:
    /*!
     * \brief The Roles enum
     * Role of QML data field
     */
    enum Roles {
        TypeRole = Qt::UserRole + 1,
        ValueRole,
        IsDestinationRole,
        IsSourceRole,
        InputCountRole,
    };

    explicit BlocksBaseModel(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual QHash<int, QByteArray> roleNames() const override;

    QList<CalculationBlock>::const_iterator cbegin() const;
    QList<CalculationBlock>::const_iterator cend() const;

    void addBlock(const int type);
    void addBlock(const CalculationBlock &block);
    CalculationBlock* blockAt(const int blockIdx);

protected:
    virtual bool canModifyValue(const CalculationBlock &block) const;

protected:
    QList<CalculationBlock> m_blocks;   ///< List of blocks in a model

};

#endif // BLOCKSBASEMODEL_H
