#ifndef FILESMANAGER_H
#define FILESMANAGER_H

#include <QObject>

#include "filereader.h"
#include "filewriter.h"

/*!
 * \brief The FilesManager class
 * Responsible for reading/writing blocks from/to JSON-like file
 */
class FilesManager : public QObject
{
    Q_OBJECT
public:
    explicit FilesManager(QObject *parent = nullptr);

    void saveToFile(const QString &file);
    void readFromFile(const QString &file);

signals:
    void error(const QString reason);   ///< Error occured during reading/writing

private:
    FileReader m_reader;                ///< Instance of FileReader
    FileWriter m_writer;                ///< Instance of FileWriter
};

#endif // FILESMANAGER_H
