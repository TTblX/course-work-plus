#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    AddDialog(QWidget *parent = nullptr);

    QString name() const;
    QString address() const;
    QString email() const;
    QString getPicturePath() const;
    void editAddress(const QString &name, const QString &address, const QString &email, const QString &picturePath);

private:
    QLineEdit *nameText;
    QLineEdit *addressText;
    QLineEdit *emailText;
    QString picturePath;
    QPushButton *pictureButton;

private slots:
    void addPicture();
};

#endif // ADDDIALOG_H
