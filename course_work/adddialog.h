#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE

//! [0]
class AddDialog : public QDialog
{
    Q_OBJECT

public:
    AddDialog(QWidget *parent = nullptr);

    QString name() const;
    QString address() const;
    QString email() const;
    void editAddress(const QString &name, const QString &address, const QString &email);

private:
    QLineEdit *nameText;
    QLineEdit *addressText;
    QLineEdit *emailText;
};
//! [0]

#endif // ADDDIALOG_H
