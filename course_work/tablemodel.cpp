#include "tablemodel.h"

//! [0]
TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

TableModel::TableModel(const QList<Contact> &contacts, QObject *parent)
    : QAbstractTableModel(parent), contacts(contacts)
{
}
//! [0]

//! [1]
int TableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : contacts.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 4;
}
//! [1]

//! [2]
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= contacts.size() || index.row() < 0)
        return QVariant();

//    if (role == Qt::DisplayRole) {
//        const auto &contact = contacts.at(index.row());

//        switch (index.column()) {
//            case 0:
//                return contact.name;
//            case 1:
//                return contact.address;
//            case 2:
//                return contact.email;
//            case 3:
//                return contact.picturePath;
//            default:
//                break;
//        }
//    }

    const auto &contact = contacts.at(index.row());
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
//! [2]

//! [3]
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
//! [3]

//! [4]
bool TableModel:: insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        contacts.insert(position, { QString(), QString() , QString(), QString()});

    endInsertRows();
    return true;
}
//! [4]

//! [5]
bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        contacts.removeAt(position);

    endRemoveRows();
    return true;
}
//! [5]

//! [6]
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        const int row = index.row();
        auto contact = contacts.value(row);

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
        contacts.replace(row, contact);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole, Qt::EditRole, Qt::EditRole});

        return true;
    }

    return false;
}
//! [6]

//! [7]
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
//! [7]

//! [8]
const QList<Contact> &TableModel::getContacts() const
{
    return contacts;
}
//! [8]
