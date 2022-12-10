#include "finddialog.h"

#include <QtWidgets>

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent),
      nameText(new QLineEdit),
      addressText(new QLineEdit),
      emailText(new QLineEdit)
{
    auto nameLabel = new QLabel(tr("Name"));
    auto addressLabel = new QLabel(tr("Address"));
    auto emailLabel = new QLabel(tr("Email"));
    auto okButton = new QPushButton(tr("OK"));
    auto cancelButton = new QPushButton(tr("Cancel"));

    auto gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 2);
    gLayout->addWidget(nameLabel, 0, 0);
    gLayout->addWidget(nameText, 0, 1);

    gLayout->addWidget(addressLabel, 1, 0);
    gLayout->addWidget(addressText, 1, 1);

    gLayout->addWidget(emailLabel, 2, 0);
    gLayout->addWidget(emailText, 2, 1);

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Find a Contact"));
}

QString FindDialog::name() const
{
    return nameText->text();
}

QString FindDialog::address() const
{
    return addressText->text();
}

QString FindDialog::email() const
{
    return emailText->text();
}
