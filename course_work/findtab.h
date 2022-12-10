#ifndef FINDTAB_H
#define FINDTAB_H

#include <QWidget>
#include <QItemSelection>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QVBoxLayout;
class QItemSelectionModel;
QT_END_NAMESPACE

class FindTab : public QWidget
{
    Q_OBJECT

public:
    explicit FindTab(QWidget *parent = nullptr);

signals:
    void selectionChanged (const QItemSelection &selected);
};

#endif // FINDTAB_H
