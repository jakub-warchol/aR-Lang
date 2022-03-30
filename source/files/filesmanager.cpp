#include "filesmanager.h"
#include "savedfile.h"
#include "source/models/blocks/blocksmodel.h"
#include "source/models/blocks/calculationblock.h"

#include <QDateTime>
#include <QDebug>

constexpr auto fileExtension = ".arfile";

/*!
 * \brief FilesManager::FilesManager
 * Constructor
 * \param parent
 */
FilesManager::FilesManager(BlocksModel *blocksModel, QObject *parent) :
    QObject(parent),
    m_blocksModel(blocksModel)
{}

/*!
 * \brief FilesManager::saveToFile
 * Save current blocks to the file
 * \param file
 */
void FilesManager::saveToFile(const QString &file)
{
    QString fileName = file;
    if(!fileName.endsWith(fileExtension)) {
        fileName.append(fileExtension);
    }

    ScriptFile savedFile;
    savedFile.creator = qgetenv("USER");
    savedFile.creationDate = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    savedFile.blocks.resize(m_blocksModel->rowCount());

    // prepare blocks
    for(int i = 0; i < m_blocksModel->rowCount(); i++) {
        const auto block = m_blocksModel->blockAt(i);
        auto &savedBlock      = savedFile.blocks[i];
        savedBlock.x          = block->xPos();
        savedBlock.y          = block->yPos();
        savedBlock.type       = static_cast<int>(block->type());
        savedBlock.value      = block->value();
        savedBlock.inputCount = block->inputCount();

        for(int j = 0; j < block->inputCount(); j++) {
            auto sourceBlockIdx = block->sourceBlockAt(j);
            if(sourceBlockIdx == -1) {
                continue;
            }

            savedFile.blocks[sourceBlockIdx].targetBlockIdx = i;
            savedFile.blocks[sourceBlockIdx].targetBlockInputIdx = j;
        }
    }

    m_writer.save(fileName, savedFile);
}

/*!
 * \brief FilesManager::readFromFile
 * Read blocks from the file
 * \param file
 */
void FilesManager::readFromFile(const QString &file)
{
    QString fileName = file;
    if(!fileName.endsWith(fileExtension)) {
        fileName.append(fileExtension);
    }

    if(m_reader.read(fileName)) {
        auto loadFile = m_reader.scriptFile();

        m_blocksModel->clearModel();

        // create CalculationBlock
        for(int i = 0; i < loadFile.blocks.size(); i++) {
            const auto &singleBlock = loadFile.blocks.at(i);
            m_blocksModel->addBlock(static_cast<CalculationBlock::Type>(singleBlock.type), singleBlock.x, singleBlock.y);
            m_blocksModel->setNumberBlockValue(i, singleBlock.value);
        }

        // update source block
        for(int i = 0; i < loadFile.blocks.size(); i++) {
            const auto &singleBlock = loadFile.blocks.at(i);
            if(singleBlock.targetBlockIdx != -1) {
                if(singleBlock.targetBlockInputIdx > m_blocksModel->blockAt(singleBlock.targetBlockIdx)->inputCount()) {
                    emit error(fileName, tr("Cannot append block.\nYour scope has been cleared."));
                    m_blocksModel->clearModel();
                    return;
                }

                m_blocksModel->attachBlocks(i, singleBlock.targetBlockIdx, singleBlock.targetBlockInputIdx);
                emit m_blocksModel->blocksFromFileAttached(i, singleBlock.targetBlockIdx, singleBlock.targetBlockInputIdx);
            }
        }

        m_blocksModel->refreshModel();
        emit loadSuccess(fileName, loadFile.creator, loadFile.creationDate);
    } else {
        auto error = m_reader.errorString();
        emit this->error(fileName, error);
    }
}
