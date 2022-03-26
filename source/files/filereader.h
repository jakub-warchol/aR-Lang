#ifndef FILEREADER_H
#define FILEREADER_H

#include <QString>

/*!
 * \brief The FileReader class
 * Read previously saved file and set saved blocks on the Scope
 */
class FileReader
{
public:
    explicit FileReader();

    bool read(const QString &file);
};

#endif // FILEREADER_H
