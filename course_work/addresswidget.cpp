#include "addresswidget.h"
#include "adddialog.h"

#include <QtWidgets>

//! [0]
AddressWidget::AddressWidget(QWidget *parent)
    : QTabWidget(parent),
      table(new TableModel(this)),
      newAddressTab(new NewAddressTab(this)),
      findTab(new FindTab(this))
{
    connect(newAddressTab, &NewAddressTab::sendDetails,
        this, &AddressWidget::addEntry);

    addTab(newAddressTab, tr("Address Book"));

    AddressWidget::setTabsClosable(true);

    setupTabs();
}
//! [0]

//! [2]
void AddressWidget::showAddEntryDialog()
{
    AddDialog aDialog;

    if (aDialog.exec())
        addEntry(aDialog.name(), aDialog.address(), aDialog.email(), aDialog.getPicturePath());
}
//! [2]

//! [3]
void AddressWidget::addEntry(const QString &name, const QString &address, const QString &email, const QString &picturePath)
{
    if (!table->getContacts().contains({ name, address, email })) {
        table->insertRows(0, 1, QModelIndex());

        QModelIndex index = table->index(0, 0, QModelIndex());
        table->setData(index, name, Qt::EditRole);

        index = table->index(0, 1, QModelIndex());
        table->setData(index, address, Qt::EditRole);

        index = table->index(0, 2, QModelIndex());
        table->setData(index, email, Qt::EditRole);

        index = table->index(0, 3, QModelIndex());
        table->setData(index, picturePath, Qt::EditRole);
        removeTab(indexOf(newAddressTab));
    } else {
        QMessageBox::information(this, tr("Duplicate Name"),
            tr("The name \"%1\" already exists.").arg(name));
    }
}
//! [3]

void AddressWidget::findEntry()
{

    FindDialog fDialog;

    if(fDialog.exec())
    {

//        auto proxyModel = new QSortFilterProxyModel(this);
//        proxyModel->setSourceModel(table);

//        if(fDialog.name() != "" && fDialog.name() != nullptr)
//        {
//            const auto regExp1 = QRegularExpression(QLatin1StringView("^[%1].*").arg(fDialog.name()),
//                                                            QRegularExpression::CaseInsensitiveOption);
//            proxyModel->setFilterRegularExpression(regExp1);
//            proxyModel->setFilterKeyColumn(0);
//        }

//        if(fDialog.address() != "" && fDialog.address() != nullptr)
//        {
//            const auto regExp2 = QRegularExpression(QLatin1StringView("^[%1].*").arg(fDialog.address()),
//                                                            QRegularExpression::CaseInsensitiveOption);
//            proxyModel->setFilterRegularExpression(regExp2);
//            proxyModel->setFilterKeyColumn(1);
//        }

//        if(fDialog.email() != "" && fDialog.email() != nullptr)
//        {
//            const auto regExp3 = QRegularExpression(QLatin1StringView("^[%1].*").arg(fDialog.email()),
//                                                            QRegularExpression::CaseInsensitiveOption);

//            proxyModel->setFilterRegularExpression(regExp3);
//            proxyModel->setFilterKeyColumn(2);
//        }

        auto nameProxyModel = new QSortFilterProxyModel(this);
        nameProxyModel->setSourceModel(table);
        auto addressProxyModel = new QSortFilterProxyModel(this);
        addressProxyModel->setSourceModel(table);
        auto emailProxyModel = new QSortFilterProxyModel(this);
        emailProxyModel->setSourceModel(table);

        if(fDialog.name() != "" && fDialog.name() != nullptr)
        {
            const auto regExp = QRegularExpression(QLatin1StringView("[%1]").arg(fDialog.name()),
                                                QRegularExpression::CaseInsensitiveOption);

            nameProxyModel->setFilterRegularExpression(regExp);
            nameProxyModel->setFilterKeyColumn(0);

            addressProxyModel->setSourceModel(nameProxyModel);
            emailProxyModel->setSourceModel(nameProxyModel);
        }

        if(fDialog.address() != "" && fDialog.address() != nullptr)
        {
            const auto regExp = QRegularExpression(QLatin1StringView("[%1]").arg(fDialog.address()),
                                                QRegularExpression::CaseInsensitiveOption);

            addressProxyModel->setFilterRegularExpression(regExp);
            addressProxyModel->setFilterKeyColumn(1);

            emailProxyModel->setSourceModel(addressProxyModel);
        }

        if(fDialog.email() != "" && fDialog.email() != nullptr)
        {
            const auto regExp = QRegularExpression(QLatin1StringView("[%1]").arg(fDialog.email()),
                                                QRegularExpression::CaseInsensitiveOption);

            emailProxyModel->setFilterRegularExpression(regExp);
            emailProxyModel->setFilterKeyColumn(2);
        }

        QTableView *tableView  = new QTableView;
        tableView->setModel(emailProxyModel);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->hide();
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSortingEnabled(true);

        connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
                 this, &AddressWidget::selectionChanged);

       connect(this, &QTabWidget::currentChanged, this, [this, tableView](int tabIndex) {
           if (widget(tabIndex) == tableView)
               emit selectionChanged(tableView->selectionModel()->selection());
       });


        addTab(tableView, tr("Search Result"));
        setCurrentWidget(tableView);

    }
}

//! [4a]
void AddressWidget::editEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    const QModelIndexList indexes = selectionModel->selectedRows();
    QString name;
    QString address;
    QString email;
    QString picturePath;
    int row = -1;

    for (const QModelIndex &index : indexes) {
        row = proxy->mapToSource(index).row();
        QModelIndex nameIndex = table->index(row, 0, QModelIndex());
        QVariant varName = table->data(nameIndex, Qt::DisplayRole);
        name = varName.toString();

        QModelIndex addressIndex = table->index(row, 1, QModelIndex());
        QVariant varAddr = table->data(addressIndex, Qt::DisplayRole);
        address = varAddr.toString();

        QModelIndex emailIndex = table->index(row, 2, QModelIndex());
        QVariant varEmail= table->data(emailIndex, Qt::DisplayRole);
        email = varEmail.toString();

        QModelIndex picturePathIndex = table->index(row, 3, QModelIndex());
        QVariant varPicturePath= table->data(picturePathIndex, Qt::DisplayRole);
        picturePath = varPicturePath.toString();
    }
//! [4a]

//! [4b]
    AddDialog aDialog;
    aDialog.setWindowTitle(tr("Edit a Contact"));
    aDialog.editAddress(name, address, email, picturePath);

    if (aDialog.exec()) {
        const QString newAddress = aDialog.address();
        if (newAddress != address) {
            const QModelIndex index = table->index(row, 1, QModelIndex());
            table->setData(index, newAddress, Qt::EditRole);
        }

        const QString newEmail= aDialog.email();
        if (newEmail != email) {
            const QModelIndex index = table->index(row, 2, QModelIndex());
            table->setData(index, newEmail, Qt::EditRole);
        }

        const QString newPicturePath= aDialog.getPicturePath();
        if (newPicturePath!= picturePath) {
            const QModelIndex index = table->index(row, 3, QModelIndex());
            table->setData(index, newPicturePath, Qt::EditRole);
        }
    }
}
//! [4b]

//! [5]
void AddressWidget::removeEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    const QModelIndexList indexes = selectionModel->selectedRows();

    for (QModelIndex index : indexes) {
        int row = proxy->mapToSource(index).row();
        table->removeRows(row, 1, QModelIndex());
    }

    if (table->rowCount(QModelIndex()) == 0)
        insertTab(0, newAddressTab, tr("Address Book"));
}
//! [5]

//! [1]
void AddressWidget::setupTabs()
{
    using namespace Qt::StringLiterals;
//    const auto groups = { "ABC"_L1, "DEF"_L1, "GHI"_L1, "JKL"_L1, "MNO"_L1, "PQR"_L1,
//                          "STU"_L1, "VW"_L1, "XYZ"_L1 };

//    for (QLatin1StringView str : groups) {
//        const auto regExp = QRegularExpression(QLatin1StringView("^[%1].*").arg(str),
//                                               QRegularExpression::CaseInsensitiveOption);

//        auto proxyModel = new QSortFilterProxyModel(this);
//        proxyModel->setSourceModel(table);
//        proxyModel->setFilterRegularExpression(regExp);
//        proxyModel->setFilterKeyColumn(0);

//        QTableView *tableView = new QTableView;
//        tableView->setModel(proxyModel);
//        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//        tableView->horizontalHeader()->setStretchLastSection(true);
//        tableView->verticalHeader()->hide();
//        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
//        tableView->setSortingEnabled(true);

//        connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
//                this, &AddressWidget::selectionChanged);

//        connect(this, &QTabWidget::currentChanged, this, [this, tableView](int tabIndex) {
//            if (widget(tabIndex) == tableView)
//                emit selectionChanged(tableView->selectionModel()->selection());
//        });

//        addTab(tableView, str);
//    }

    auto proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(table);
    proxyModel->setFilterKeyColumn(0);


    QTableView *tableView  = new QTableView;
    tableView->setModel(proxyModel);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->hide();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
             this, &AddressWidget::selectionChanged);

   connect(this, &QTabWidget::currentChanged, this, [this, tableView](int tabIndex) {
       if (widget(tabIndex) == tableView)
           emit selectionChanged(tableView->selectionModel()->selection());
   });

   addTab(tableView, "ALL");
}
//! [1]

//! [7]
void AddressWidget::readFromFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }

    QList<Contact> contacts;
    QDataStream in(&file);
    in >> contacts;

    if (contacts.isEmpty()) {
        QMessageBox::information(this, tr("No contacts in file"),
                                 tr("The file you are attempting to open contains no contacts."));
    } else {
        for (const auto &contact: qAsConst(contacts))
            addEntry(contact.name, contact.address, contact.email, contact.picturePath);
    }
}
//! [7]

//! [6]
void AddressWidget::writeToFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QDataStream out(&file);
    out << table->getContacts();
}
//! [6]
