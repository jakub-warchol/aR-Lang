#include "filewriter.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

/*!
 * \brief FileWriter::FileWriter
 * Constructor
 */
FileWriter::FileWriter()
{}

/*!
 * \brief FileWriter::save
 * Save content to the configuration file and return success status
 * \param file
 * \param savedFile
 * \return
 */
bool FileWriter::save(const QString &file, const ScriptFile &savedFile)
{
    QJsonObject json;
    json.insert("creator", savedFile.creator);
    json.insert("creationDate", savedFile.creationDate);

    // add blocks
    QJsonArray blocks;
    for(const auto &singleBlock : qAsConst(savedFile.blocks)) {
        QJsonObject blockJson;
        blockJson.insert("x", singleBlock.x);
        blockJson.insert("y", singleBlock.y);
        blockJson.insert("type", singleBlock.type);
        blockJson.insert("value", singleBlock.value);
        blockJson.insert("inputCount", singleBlock.inputCount);
        blockJson.insert("targetIdx", singleBlock.targetBlockIdx);
        blockJson.insert("targetInputIdx", singleBlock.targetBlockInputIdx);

        blocks.push_back(blockJson);
    }

    json.insert("blocks", blocks);
    json.insert("blocksCount", blocks.count());

    // create file
    QJsonDocument jsonDocument{json};
    auto jsonBytes = jsonDocument.toJson(QJsonDocument::Indented);

    QFile configFile{file};
    if(!configFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Cannot open file" << file << configFile.errorString();
        return false;
    }

    // save to file
    QTextStream in{&configFile};
    in << jsonBytes;

    configFile.close();
    return true;
}
