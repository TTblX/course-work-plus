#ifndef ADDRESSWIDGET_H
#define ADDRESSWIDGET_H

#include "newaddresstab.h"
#include "tablemodel.h"
#include "finddialog.h"
#include"findtab.h"

#include <QItemSelection>
#include <QTabWidget>

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QItemSelectionModel;
QT_END_NAMESPACE

//! [0]
class AddressWidget : public QTabWidget
{
    Q_OBJECT

public:
    AddressWidget(QWidget *parent = nullptr);
    void readFromFile(const QString &fileName);
    void writeToFile(const QString &fileName);

public slots:
    void showAddEntryDialog();
    void addEntry(const QString &name, const QString &address, const QString &email, const  QString &picturePath);
    void editEntry();
    void findEntry();
    void removeEntry();

signals:
    void selectionChanged (const QItemSelection &selected);

private:
    void setupTabs();

    TableModel *table;
    NewAddressTab *newAddressTab;
    FindTab* findTab;
};
//! [0]

#endif // ADDRESSWIDGET_H
