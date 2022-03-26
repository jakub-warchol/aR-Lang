#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QString>

/*!
 * \brief The FileWriter class
 * Write configuration from scope to the file
 */
class FileWriter
{
public:
    FileWriter();

    bool save(const QString &file);
};

#endif // FILEWRITER_H
