#ifndef FILESMANAGER_H
#define FILESMANAGER_H

#include <QObject>
#include <QList>

#include "filereader.h"
#include "filewriter.h"

class CalculationBlock;
class BlocksModel;
/*!
 * \brief The FilesManager class
 * Responsible for reading/writing blocks from/to JSON-like file
 */
class FilesManager : public QObject
{
    Q_OBJECT
public:
    explicit FilesManager(BlocksModel *blocksModel, QObject *parent = nullptr);

    void saveToFile(const QString &file);
    void readFromFile(const QString &file);

signals:
    void error(const QString file, const QString reason);                                   ///< Error occured during reading/writing
    void loadSuccess(const QString file,const QString creator, const QString creationDate); ///< Load file successful

private:
    FileReader m_reader;                ///< Instance of FileReader
    FileWriter m_writer;                ///< Instance of FileWriter
    BlocksModel *m_blocksModel;         ///< Instance of BlocksModel
};

#endif // FILESMANAGER_H
