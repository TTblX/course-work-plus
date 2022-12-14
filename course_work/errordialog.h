#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include "exception.h"

#include <QDialog>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class ErrorDialog : public QDialog
{
     Q_OBJECT

public:
    ErrorDialog(QWidget * parent, Exception ex);

};

#endif // ERRORDIALOG_H
