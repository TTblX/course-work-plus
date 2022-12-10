#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog(QWidget *parent = nullptr);

    QString name() const;
    QString address() const;
    QString email() const;

private:
    QLineEdit *nameText;
    QLineEdit *addressText;
    QLineEdit *emailText;
};

#endif // FINDDIALOG_H
