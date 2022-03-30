#ifndef SAVEDFILE_H
#define SAVEDFILE_H

#include <QVector>

#include <QString>
#include <QVector>

/*!
 * \brief The ScriptFile struct
 * Script file represents data which is loaded or saved into script file
 */
struct ScriptFile {
    /*!
     * \brief The SingleBlock struct
     * Represents data of single block on the scope
     */
    struct SingleBlock {
        qreal x;                        ///< position of x
        qreal y;                        ///< position of y
        int type;                       ///< type
        QString value;                  ///< value
        int inputCount;                 ///< count of input
        int targetBlockIdx      = -1;   ///< index of block which is a target
        int targetBlockInputIdx = -1;   ///< index connected input
    };

    QString creator;                    ///< name of file creator
    QString creationDate;               ///< date of file creation
    QVector<SingleBlock> blocks;        ///< vector of file's blocks
};

#endif // SAVEDFILE_H
