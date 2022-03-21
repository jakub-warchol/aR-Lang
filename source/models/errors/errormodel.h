#ifndef ERRORMODEL_H
#define ERRORMODEL_H

#include <QAbstractListModel>

/*!
 * \brief The ErrorModel class
 * Model of error messages, detected during parsing a calculation expression
 */
class ErrorModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ErrorModel(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    void addError(const QString error);
    void clearErrors();

private:
    QStringList m_errors;   ///< List of errors
};

#endif // ERRORMODEL_H
