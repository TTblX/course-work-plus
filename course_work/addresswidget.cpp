#include"addresswidget.h"
#include "finddialog.h"
#include "adddialog.h"
#include "errordialog.h"

#include <QtWidgets>

AddressWidget::AddressWidget(QWidget *parent)
    : QTabWidget(parent),
      table(new TableModel(this)),
      newAddressTab(new NewAddressTab(this))
{
    connect(newAddressTab, &NewAddressTab::sendDetails,
        this, &AddressWidget::addEntry);

    connect(this->tabBar(), &QTabBar::tabCloseRequested, this->tabBar(), &QTabBar::removeTab);
    addTab(newAddressTab, tr("Address Book"));

    AddressWidget::setTabsClosable(true);

    setupTabs();
}

void AddressWidget::showAddEntryDialog()
{
    AddDialog aDialog;

    if (aDialog.exec())
        addEntry(aDialog.name(), aDialog.address(), aDialog.email(), aDialog.getPicturePath());
}

void AddressWidget::addEntry(const QString &name, const QString &address, const QString &email, const QString &picturePath)
{    
    try {
        if(name == QString() || address == QString() || email == QString() || picturePath == QString())
            throw ArgumentException("each value of contact must not be zero\n");

        if (!table->getContacts().Contains({name, address, email, picturePath})) {
            table->insertRows(0, 1, QModelIndex());

            QModelIndex index = table->index(0, 0, QModelIndex());
            table->setData(index, name, Qt::EditRole);

            index = table->index(0, 1, QModelIndex());
            table->setData(index, address, Qt::EditRole);

            index = table->index(0, 2, QModelIndex());
            table->setData(index, email, Qt::EditRole);

            index = table->index(0, 3, QModelIndex());
            table->setData(index, picturePath, Qt::EditRole);
            if(indexOf(newAddressTab) != -1)
            {
                removeTab(indexOf(newAddressTab));
            }

        } else {
            QMessageBox::information(this, tr("Duplicate Name"),
                tr("The name \"%1\" already exists.").arg(name));
        }
    } catch (ArgumentException ex) {
        qDebug() << "Error message: " << ex.what();
        qDebug() << "Error code: " << ex.GetErrorCode();

        ErrorDialog errorDialog(this, ex);
        errorDialog.exec();
    }

}

void AddressWidget::findEntry()
{

    FindDialog fDialog;

    if(fDialog.exec())
    {
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

void AddressWidget::setupTabs()
{
    using namespace Qt::StringLiterals;

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
   this->tabBar()->tabButton(1, QTabBar::RightSide)->resize(0,0);
}

void AddressWidget::readFromFile(const QString &fileName)
{
    QFile file( fileName );
    if( file.open( QIODevice::ReadOnly ) )
    {
        QByteArray bytes = file.readAll();
        file.close();

        QJsonParseError jsonError;
        QJsonDocument document = QJsonDocument::fromJson( bytes, &jsonError );
        if( jsonError.error != QJsonParseError::NoError )
        {            
            return ;
        }
        if( document.isObject() )
        {
            QJsonArray jsonContacts = document.object().value("contacts").toArray();
            for(int i = 0 ; i < jsonContacts.count() ; i++)
            {
                QJsonObject json = jsonContacts.at(i).toObject();
                if(json.count() == 4 && json.contains("name") && json.contains("address") && json.contains("email") && json.contains("picture path"))
                {
                    if(json.value("name").isString() && json.value("address").isString() && json.value("email").isString() && json.value("picture path").isString())
                    {
                        addEntry(json.value("name").toString(), json.value("address").toString(), json.value("email").toString(), json.value("picture path").toString());

                    }
                }
            }
        }
    }
}

void AddressWidget::writeToFile(const QString &fileName)
{
    QJsonArray contactsArray;
    for (int i = 0; i < table->getContacts().Count(); i++)
    {
        QJsonObject jsonContact;
        table->getContacts().GetElement(i).toJson(jsonContact);
        contactsArray.append(jsonContact);
    }

    QJsonObject jsonContacts;
    jsonContacts.insert("contacts", contactsArray);

    QJsonDocument document;
    document.setObject( jsonContacts);
    QByteArray bytes = document.toJson( QJsonDocument::Indented );
    QFile file( fileName );

    try {
        if( !file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
        {
            throw Exception("Failed to open file\n");
        }
        QTextStream iStream( &file );
        iStream << bytes;
        file.close();
    } catch (Exception ex) {
        qDebug() << "Error message: " << ex.what();
        qDebug() << "Error code: " << ex.GetErrorCode();

        ErrorDialog errorDialog(this, ex);
        errorDialog.exec();
    }
}

