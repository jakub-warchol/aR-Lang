#ifndef FILEREADER_H
#define FILEREADER_H

#include <QString>
#include <QVariant>

#include "savedfile.h"

/*!
 * \brief The FileReader class
 * Read previously saved file and set saved blocks on the Scope
 */
class FileReader
{
public:
    explicit FileReader();

    bool read(const QString &file);

    QString errorString() const;
    ScriptFile scriptFile() const;

private:
    template<typename Json, typename ReturnType>
    /*!
     * \brief extractFromJson
     * Extract from JSON file value on key <i>name</i> and return converted value
     * \param json
     * \param name
     * \return
     */
    auto extractFromJson(const Json &json, const QString &name) -> ReturnType {
        ReturnType r;

        auto jsonValue = json[name];
        if constexpr(std::is_same<ReturnType, int>::value) {
            r = jsonValue.toInt();
        } else if constexpr(std::is_same<ReturnType, qreal>::value) {
            r = jsonValue.toDouble();
        } else if constexpr(std::is_same<ReturnType, QString>::value) {
            r = jsonValue.toString();
        } else if constexpr(std::is_same<ReturnType, QJsonArray>::value) {
            r = jsonValue.toArray();
        } else {
            static_assert (std::is_convertible_v<ReturnType, QVariant>, "ReturnType must be at least convertible to QVariant");
            r = jsonValue.toVariant();
        }

        return r;
    }

private:
    QString m_errorString;      ///< Last error string
    ScriptFile m_scriptFile;    ///< Last successfully loaded ScriptFile
};

#endif // FILEREADER_H
