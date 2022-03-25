#ifndef ADDBLOCKSMODEL_H
#define ADDBLOCKSMODEL_H

#include "blocksbasemodel.h"

/*!
 * \brief The AddBlocksModel class
 * Represents model of blocks in the Add Block dialogue
 */
class AddBlocksModel : public BlocksBaseModel
{
    Q_OBJECT
public:
    explicit AddBlocksModel(QObject *parent = nullptr);

protected:
    using BlocksBaseModel::addBlock;    ///< Hide addBlock methods
};

#endif // ADDBLOCKSMODEL_H
