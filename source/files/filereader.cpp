#include "filereader.h"
#include "savedfile.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QDebug>

/*!
 * \brief FileReader::FileReader
 * Constructor
 */
FileReader::FileReader()
{}

/*!
 * \brief FileReader::read
 * Read saved blocks from the file from the file
 * \param file
 * \return
 */
bool FileReader::read(const QString &file)
{
    QFile configFile{file};
    if(!configFile.open(QIODevice::ReadOnly)) {
        m_errorString = QObject::tr("Cannot open file %1: %2").arg(file, configFile.errorString());
        return false;
    }

    // load content
    QJsonParseError jsonParseError;
    auto jsonDocument = QJsonDocument::fromJson(configFile.readAll(), &jsonParseError);
    if(jsonParseError.error != QJsonParseError::NoError) {
        m_errorString = QObject::tr("Cannot load file %1: %2").arg(file, jsonParseError.errorString());
        return false;
    }

    if(!jsonDocument.isObject()) {
        m_errorString = QObject::tr("Cannot load file %1: File is not a correct aR-Lang's file").arg(file);
        return false;
    }

    auto json = jsonDocument.object();
    auto creator      = extractFromJson<QJsonObject, QString>(json, "creator");
    auto creationDate = extractFromJson<QJsonObject, QString>(json, "creationDate");
    auto blocksCount  = extractFromJson<QJsonObject, int>(json, "blocksCount");
    auto blocks       = extractFromJson<QJsonObject, QJsonArray>(json, "blocks");
    if(blocks.count() != blocksCount) {
        m_errorString = QObject::tr("Cannot load file %1: Inconsistent count of blocks").arg(file);
        return false;
    }

    ScriptFile scriptFile;
    scriptFile.creator      = creator;
    scriptFile.creationDate = creationDate;
    scriptFile.blocks.reserve(blocksCount);
    for(const auto &block : blocks) {
        ScriptFile::SingleBlock singleBlock;
        singleBlock.x                   = extractFromJson<QJsonObject, qreal>(block.toObject(), "x");
        singleBlock.y                   = extractFromJson<QJsonObject, qreal>(block.toObject(), "y");
        singleBlock.type                = extractFromJson<QJsonObject, int>(block.toObject(), "type");
        singleBlock.value               = extractFromJson<QJsonObject, QString>(block.toObject(), "value");
        singleBlock.inputCount          = extractFromJson<QJsonObject, int>(block.toObject(), "inputCount");
        singleBlock.targetBlockIdx      = extractFromJson<QJsonObject, int>(block.toObject(), "targetIdx");
        singleBlock.targetBlockInputIdx = extractFromJson<QJsonObject, int>(block.toObject(), "targetInputIdx");

        if(singleBlock.type > 0 && singleBlock.targetBlockInputIdx > singleBlock.inputCount) {
            m_errorString = QObject::tr("Cannot load file %1: Inconsistent count of inputs").arg(file);
            return false;
        }

        if(singleBlock.targetBlockIdx > blocksCount) {
            m_errorString = QObject::tr("Cannot load file %1: Block target exceeds blocks count").arg(file);
            return false;
        }

        scriptFile.blocks.push_back(singleBlock);
    }

    m_scriptFile = std::move(scriptFile);
    return true;
}

/*!
 * \brief FileReader::errorString
 * Get error string
 * \return
 */
QString FileReader::errorString() const
{
    return m_errorString;
}

/*!
 * \brief FileReader::scriptFile
 * Get last correct ScriptFile
 * \return
 */
ScriptFile FileReader::scriptFile() const
{
    return m_scriptFile;
}
