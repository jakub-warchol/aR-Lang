#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QString>

#include "savedfile.h"

/*!
 * \brief The FileWriter class
 * Write configuration from scope to the file
 */
class FileWriter
{
public:
    FileWriter();

    bool save(const QString &file, const ScriptFile &savedFile);
};

#endif // FILEWRITER_H
