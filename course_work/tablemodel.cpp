#include "tablemodel.h"
#include "errordialog.h"

//! [0]
TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent),
      contacts(List<Contact>())
{
}

TableModel::TableModel(const List<Contact> &contacts, QObject *parent)
    : QAbstractTableModel(parent), contacts(contacts)
{
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : contacts.Count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 4;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    try {
        if (!index.isValid())
            throw IndexException("Invalid index while accesing data\n");

        if (index.row() >= contacts.Count() || index.row() < 0)
            throw IndexException("Invalid row in index\n");
    } catch (IndexException ex) {
        qDebug() << "Error message: " << ex.what();
        qDebug() << "Error code: " << ex.GetErrorCode();

        ErrorDialog errorDialog(nullptr, ex);
        errorDialog.exec();
        return QVariant();
    }

    const auto &contact = contacts.GetElement(index.row());
    QString filename = contact.picturePath;

    QPixmap pixmap ;
    pixmap.load(filename);

    switch (index.column()) {
        case 0:
            if (role == Qt::DisplayRole) return contact.name;
            break;
        case 1:
            if (role == Qt::DisplayRole) return contact.address;
            break;
        case 2:
            if (role == Qt::DisplayRole) return contact.email;
            break;
        case 3:
            if(role == Qt::DisplayRole )
            {
                return filename;
            }

            if (role == Qt::ToolTipRole)
            {
                // find path for specified index
                return QString("<img src='%1'>").arg(filename);
            }
            break;
        default:
            break;
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Name");
            case 1:
                return tr("Address");
            case 2:
                return tr("Email");
            case 3:
                return tr("Photo");
            default:
                break;
        }
    }
    return QVariant();
}

bool TableModel:: insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        contacts.Insert({ QString(), QString() , QString(), QString()}, position);

    endInsertRows();
    return true;
}

bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        contacts.Del(position);

    endRemoveRows();
    return true;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    try {
        if(!index.isValid())
            throw IndexException("Invalid index while accesing data\n");

        if(value.toString() == QString())
            throw ArgumentException("each value of contact must not be zero\n");

        if (role == Qt::EditRole) {
            const int row = index.row();
            auto contact = contacts.GetElement(row);

            switch (index.column()) {
                case 0:
                    contact.name = value.toString();
                    break;
                case 1:
                    contact.address = value.toString();
                    break;
                case 2:
                    contact.email = value.toString();
                    break;
                case 3:
                    contact.picturePath = value.toString();
                    break;
                default:
                    return false;
            }
            contacts.SetElement(contact, row);
            emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole, Qt::EditRole, Qt::EditRole});

            return true;
        }
    } catch (ArgumentException ex) {
        qDebug() << "Error message: " << ex.what();
        qDebug() << "Error code: " << ex.GetErrorCode();

        ErrorDialog errorDialog(nullptr, ex);
        errorDialog.exec();
    }
    catch (IndexException ex)
    {
        qDebug() << "Error message: " << ex.what();
        qDebug() << "Error code: " << ex.GetErrorCode();

        ErrorDialog errorDialog(nullptr, ex);
        errorDialog.exec();
    }

    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

const List<Contact> &TableModel::getContacts() const
{
    return contacts;
}
