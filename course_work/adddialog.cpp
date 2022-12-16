#include "adddialog.h"

#include <QtWidgets>

AddDialog::AddDialog(QWidget *parent)
    : QDialog(parent),
      nameText(new QLineEdit),
      addressText(new QLineEdit),
      emailText(new QLineEdit)
{
    auto nameLabel = new QLabel(tr("Name"));
    auto addressLabel = new QLabel(tr("Address"));
    auto emailLabel = new QLabel(tr("Email"));
    auto pictureButton = new QPushButton(tr("Choose Picture"));
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

    gLayout->addWidget(pictureButton, 3, 0);

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);
    connect(pictureButton ,&QAbstractButton::clicked, this, &AddDialog::addPicture);

    setWindowTitle(tr("Add a Contact"));
}

QString AddDialog::name() const
{
    return nameText->text();
}

QString AddDialog::address() const
{
    return addressText->text();
}

QString AddDialog::email() const
{
    return emailText->text();
}

QString AddDialog::getPicturePath() const
{
    return picturePath;
}
void AddDialog:: editAddress(const QString &name, const QString &address, const QString &email, const QString &picturePath)
{
    nameText->setReadOnly(true);
    nameText->setText(name);
    addressText->setText(address);
    emailText->setText(email);
}

void AddDialog::addPicture()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Choose picture"), "/", tr("Images (*.png *.xpm *.jpg)"), nullptr,  QFileDialog::DontConfirmOverwrite);
    if (!fileName.isEmpty())
    {
        picturePath = fileName;
    }
}
