#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "list.h"
#include "list.cpp"

#include <QAbstractTableModel>
#include <QPixMap>
#include <QString>
#include <QJsonObject>

struct Contact
{
    QString name;
    QString address;
    QString email;
    QString picturePath;

    bool operator==(const Contact &other) const
    {
        return name == other.name && address == other.address && email == other.email && picturePath == other.picturePath;
    }

    void toJson(QJsonObject &json) const
    {
        json["name"] = name;
        json["address"] = address;
        json["email"] = email;
        json["picture path"] = picturePath;
    }
};


class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = nullptr);
    TableModel(const List<Contact> &contacts, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;    
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;    
    const List<Contact> &getContacts() const;

private:
    List<Contact> contacts;
};

#endif // TABLEMODEL_H
