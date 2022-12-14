#include "errordialog.h"

#include <QtWidgets>

ErrorDialog::ErrorDialog(QWidget * parent, Exception ex)
    :QDialog(parent)
{
    setWindowTitle(tr("Error!"));

    QLabel *errorLabel = new QLabel(tr("Error message : ") + ex.what(), this);
    QLabel *codeLabel = new QLabel(tr("Error code : ") + ex.GetErrorCode(), this);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(errorLabel);
    mainLayout->addWidget(codeLabel);
    setLayout(mainLayout);
}
