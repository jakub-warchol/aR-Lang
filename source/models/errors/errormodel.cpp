#include "errormodel.h"

/*!
 * \brief ErrorModel::ErrorModel
 * Constructor of ErrorModel
 * \param parent
 */
ErrorModel::ErrorModel(QObject *parent) : QAbstractListModel(parent)
{}

/*!
 * \brief ErrorModel::rowCount
 * Get count of errors in the model
 * \param parent
 * \return
 */
int ErrorModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_errors.size();
}

/*!
 * \brief ErrorModel::data
 * Get data from model for given index
 * \param index
 * \param role
 * \return
 */
QVariant ErrorModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid()) {
        const int idx     = index.row();
        const auto &error = m_errors.at(idx);

        if(role == Qt::DisplayRole) {
            return error;
        }
    }

    return {};
}

/*!
 * \brief ErrorModel::roleNames
 * Get QML's names for accordings roles
 * \return
 */
QHash<int, QByteArray> ErrorModel::roleNames() const
{
    return {{Qt::DisplayRole, "error"}};
}

/*!
 * \brief ErrorModel::addError
 * Add given error to the model
 * \param error
 */
void ErrorModel::addError(const QString error)
{
    beginInsertRows(QModelIndex{}, m_errors.size(), m_errors.size());
    m_errors.append(error);
    endInsertRows();
}

/*!
 * \brief ErrorModel::clearErrors
 * Clear errors model
 */
void ErrorModel::clearErrors()
{
    beginResetModel();
    m_errors.clear();
    endResetModel();
}
