//
// Created by vanish on 06.10.2022.
//

#ifndef UNTITLED_ADDRESBOOK_H
#define UNTITLED_ADDRESBOOK_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QTextEdit;

class AddressBook : public QWidget
{
    Q_OBJECT

public:
    AddressBook(QWidget *parent = 0);

private:
    QLineEdit *nameLine;
    QTextEdit *addressText;
};

#endif //UNTITLED_ADDRESBOOK_H
