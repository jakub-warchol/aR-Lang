#ifndef ADDBLOCKSMODEL_H
#define ADDBLOCKSMODEL_H

#include "blocksbasemodel.h"

class AddBlocksModel : public BlocksBaseModel
{
    Q_OBJECT
public:
    explicit AddBlocksModel(QObject *parent = nullptr);

protected:
    using BlocksBaseModel::addBlock;
};

#endif // ADDBLOCKSMODEL_H
